/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the OAI Public License, Version 1.1  (the "License"); you may not use this file
 * except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.openairinterface.org/?page_id=698
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */

/*! \file gNB_scheduler_srs.c
 * \brief MAC procedures related to SRS
 * \date 2021
 * \version 1.0
 */

#include <softmodem-common.h>
#include "NR_MAC_gNB/nr_mac_gNB.h"
#include "NR_MAC_COMMON/nr_mac_extern.h"
#include "NR_MAC_gNB/mac_proto.h"
#include "common/ran_context.h"
#include "nfapi/oai_integration/vendor_ext.h"
#include "common/utils/nr/nr_common.h"

extern RAN_CONTEXT_t RC;
extern int num_delay;  //add_yjn
int get_future_ul_tti_req_ind(gNB_MAC_INST * gNB, frame_t frame, sub_frame_t slot);//add_yjn
const uint16_t m_SRS[64] = { 4, 8, 12, 16, 16, 20, 24, 24, 28, 32, 36, 40, 48, 48, 52, 56, 60, 64, 72, 72, 76, 80, 88,
                             96, 96, 104, 112, 120, 120, 120, 128, 128, 128, 132, 136, 144, 144, 144, 144, 152, 160,
                             160, 160, 168, 176, 184, 192, 192, 192, 192, 208, 216, 224, 240, 240, 240, 240, 256, 256,
                             256, 264, 272, 272, 272 };

void nr_configure_srs(nfapi_nr_srs_pdu_t *srs_pdu, int module_id, int CC_id,NR_UE_info_t*  UE, NR_SRS_ResourceSet_t *srs_resource_set, NR_SRS_Resource_t *srs_resource) {

  NR_UE_UL_BWP_t *current_BWP = &UE->current_UL_BWP;

  srs_pdu->rnti = UE->rnti;
  srs_pdu->handle = 0;
  srs_pdu->bwp_size = current_BWP->BWPSize;
  srs_pdu->bwp_start = current_BWP->BWPStart;
  srs_pdu->subcarrier_spacing = current_BWP->scs;
  srs_pdu->cyclic_prefix = 0;
  srs_pdu->num_ant_ports = srs_resource->nrofSRS_Ports;
  srs_pdu->num_symbols = srs_resource->resourceMapping.nrofSymbols;
  srs_pdu->num_repetitions = srs_resource->resourceMapping.repetitionFactor;
  srs_pdu->time_start_position = srs_resource->resourceMapping.startPosition;
  srs_pdu->config_index = srs_resource->freqHopping.c_SRS;
  srs_pdu->sequence_id = srs_resource->sequenceId;
  srs_pdu->bandwidth_index = srs_resource->freqHopping.b_SRS;
  srs_pdu->comb_size = srs_resource->transmissionComb.present - 1;

  switch(srs_resource->transmissionComb.present) {
    case NR_SRS_Resource__transmissionComb_PR_n2:
      srs_pdu->comb_offset = srs_resource->transmissionComb.choice.n2->combOffset_n2;
      srs_pdu->cyclic_shift = srs_resource->transmissionComb.choice.n2->cyclicShift_n2;
      break;
    case NR_SRS_Resource__transmissionComb_PR_n4:
      srs_pdu->comb_offset = srs_resource->transmissionComb.choice.n4->combOffset_n4;
      srs_pdu->cyclic_shift = srs_resource->transmissionComb.choice.n4->cyclicShift_n4;
      break;
    default:
      LOG_W(NR_MAC, "Invalid or not implemented comb_size!\n");
  }

  srs_pdu->frequency_position = srs_resource->freqDomainPosition;
  srs_pdu->frequency_shift = srs_resource->freqDomainShift;
  srs_pdu->frequency_hopping = srs_resource->freqHopping.b_hop;
  srs_pdu->group_or_sequence_hopping = srs_resource->groupOrSequenceHopping;
  srs_pdu->resource_type = srs_resource->resourceType.present - 1;
  srs_pdu->t_srs = srs_period[srs_resource->resourceType.choice.periodic->periodicityAndOffset_p.present];
  srs_pdu->t_offset = get_nr_srs_offset(srs_resource->resourceType.choice.periodic->periodicityAndOffset_p);

  // TODO: This should be completed
  srs_pdu->srs_parameters_v4.srs_bandwidth_size = m_SRS[srs_pdu->config_index];
  srs_pdu->srs_parameters_v4.usage = 1<<srs_resource_set->usage;
  srs_pdu->srs_parameters_v4.report_type[0] = 1;
  srs_pdu->srs_parameters_v4.iq_representation = 1;
  srs_pdu->srs_parameters_v4.prg_size = 1;
  srs_pdu->srs_parameters_v4.num_total_ue_antennas = 1<<srs_pdu->num_ant_ports;
  if (srs_resource_set->usage == NR_SRS_ResourceSet__usage_beamManagement) {
    srs_pdu->beamforming.trp_scheme = 0;
    srs_pdu->beamforming.num_prgs = m_SRS[srs_pdu->config_index];
    srs_pdu->beamforming.prg_size = 1;
  }
}

void nr_fill_nfapi_srs(int module_id, int CC_id, NR_UE_info_t* UE, sub_frame_t slot, NR_SRS_ResourceSet_t *srs_resource_set, NR_SRS_Resource_t *srs_resource) {

  nfapi_nr_ul_tti_request_t *future_ul_tti_req = &RC.nrmac[module_id]->UL_tti_req_ahead[0][slot];
  AssertFatal(future_ul_tti_req->n_pdus <
              sizeof(future_ul_tti_req->pdus_list) / sizeof(future_ul_tti_req->pdus_list[0]),
              "Invalid future_ul_tti_req->n_pdus %d\n", future_ul_tti_req->n_pdus);
  future_ul_tti_req->pdus_list[future_ul_tti_req->n_pdus].pdu_type = NFAPI_NR_UL_CONFIG_SRS_PDU_TYPE;
  future_ul_tti_req->pdus_list[future_ul_tti_req->n_pdus].pdu_size = sizeof(nfapi_nr_srs_pdu_t);
  nfapi_nr_srs_pdu_t *srs_pdu = &future_ul_tti_req->pdus_list[future_ul_tti_req->n_pdus].srs_pdu;
  memset(srs_pdu, 0, sizeof(nfapi_nr_srs_pdu_t));
  future_ul_tti_req->n_pdus += 1;

  nr_configure_srs(srs_pdu, module_id, CC_id, UE, srs_resource_set, srs_resource);
}

/*******************************************************************
*
* NAME :         nr_schedule_srs
*
* PARAMETERS :   module id
*                frame number for possible SRS reception
*
* DESCRIPTION :  It informs the PHY layer that has an SRS to receive.
*                Only for periodic scheduling yet.
*
*********************************************************************/
void nr_schedule_srs(int module_id, frame_t frame) {

  gNB_MAC_INST *nrmac = RC.nrmac[module_id];
  NR_UEs_t *UE_info = &nrmac->UE_info;

  UE_iterator(UE_info->list, UE) {
    const int CC_id = 0;
    NR_UE_sched_ctrl_t *sched_ctrl = &UE->UE_sched_ctrl;
    NR_UE_UL_BWP_t *current_BWP = &UE->current_UL_BWP;

    sched_ctrl->sched_srs.frame = -1;
    sched_ctrl->sched_srs.slot = -1;
    sched_ctrl->sched_srs.srs_scheduled = false;

    if((sched_ctrl->ul_failure == 1 && get_softmodem_params()->phy_test==0) ||
       sched_ctrl->rrc_processing_timer > 0) {
      continue;
    }

    NR_SRS_Config_t *srs_config = current_BWP->srs_Config;
    if (!srs_config)
      continue;

    for(int rs = 0; rs < srs_config->srs_ResourceSetToAddModList->list.count; rs++) {

      // Find periodic resource set
      NR_SRS_ResourceSet_t *srs_resource_set = srs_config->srs_ResourceSetToAddModList->list.array[rs];
      if (srs_resource_set->resourceType.present != NR_SRS_ResourceSet__resourceType_PR_periodic) {
        continue;
      }

      // Find the corresponding srs resource
      NR_SRS_Resource_t *srs_resource = NULL;
      for (int r1 = 0; r1 < srs_resource_set->srs_ResourceIdList->list.count; r1++) {
        for (int r2 = 0; r2 < srs_config->srs_ResourceToAddModList->list.count; r2++) {
          if ((*srs_resource_set->srs_ResourceIdList->list.array[r1] ==
               srs_config->srs_ResourceToAddModList->list.array[r2]->srs_ResourceId) &&
              (srs_config->srs_ResourceToAddModList->list.array[r2]->resourceType.present ==
               NR_SRS_Resource__resourceType_PR_periodic)) {
            srs_resource = srs_config->srs_ResourceToAddModList->list.array[r2];
            break;
          }
        }
      }

      if (srs_resource == NULL) {
        continue;
      }

      uint16_t period = srs_period[srs_resource->resourceType.choice.periodic->periodicityAndOffset_p.present];
      uint16_t offset = get_nr_srs_offset(srs_resource->resourceType.choice.periodic->periodicityAndOffset_p);
      int n_slots_frame = nr_slots_per_frame[current_BWP->scs];

      // Check if UE will transmit the SRS in this frame
      if ( ((frame - offset/n_slots_frame)*n_slots_frame)%period == 0) {
        LOG_D(NR_MAC,"Scheduling SRS reception for %d.%d\n", frame, offset%n_slots_frame);
        sub_frame_t srs_slot = (offset + num_delay)%n_slots_frame;//add_yjn
        frame_t srs_frame = (frame + (offset + num_delay)/n_slots_frame)%1024;//add_yjn
         LOG_D(NR_MAC,"srs_frame = %d, srs_slot = %d\n",srs_frame, srs_slot);
        int future_index = get_future_ul_tti_req_ind(nrmac, srs_frame, srs_slot);//add_yjn
        nr_fill_nfapi_srs(module_id, CC_id, UE, future_index, srs_resource_set, srs_resource);
        sched_ctrl->sched_srs.frame = frame;
        sched_ctrl->sched_srs.slot = offset%n_slots_frame;
        sched_ctrl->sched_srs.srs_scheduled = true;
      }
    }
  }
}
