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
 * Author and copyright: Laurent Thomas, open-cells.com
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

/* Form definition file generated by fdesign */

#include <stdlib.h>
#include "nr_phy_scope.h"
#include "executables/softmodem-common.h"
#include "executables/nr-softmodem-common.h"
#include <forms.h>

#define TPUT_WINDOW_LENGTH 100
#define ScaleZone 4
#define localBuff(NaMe,SiZe) float NaMe[SiZe]; memset(NaMe,0,sizeof(NaMe));

int otg_enabled;

const FL_COLOR rx_antenna_colors[4] = {FL_RED,FL_BLUE,FL_GREEN,FL_YELLOW};
const FL_COLOR water_colors[4] = {FL_BLUE,FL_GREEN,FL_YELLOW,FL_RED};

typedef struct complex16 scopeSample_t;
#define SquaredNorm(VaR) ((VaR).r*(VaR).r+(VaR).i*(VaR).i)

typedef struct OAIgraph {
  FL_OBJECT *graph;
  FL_OBJECT *text;
  float maxX;
  float maxY;
  float minX;
  float minY;
  int x;
  int y;
  int w;
  int h;
  int waterFallh;
  double *waterFallAvg;
  boolean_t initDone;
  int iteration;
  void (*gNBfunct) (struct OAIgraph *graph, scopeData_t *p, int UE_id);
  void (*nrUEfunct)(struct OAIgraph *graph, PHY_VARS_NR_UE *phy_vars_ue, int eNB_id, int UE_id);
} OAIgraph_t;

/* Forms and Objects */
typedef struct {
  FL_FORM    *phy_scope;
  OAIgraph_t graph[20];
  FL_OBJECT *button_0;
} OAI_phy_scope_t;

typedef struct {
  FL_FORM    *stats_form;
  void       *vdata;
  char       *cdata;
  long        ldata;
  FL_OBJECT *stats_text;
  FL_OBJECT *stats_button;
} FD_stats_form;

static void drawsymbol(FL_OBJECT *obj, int id,
                       FL_POINT *p, int n, int w, int h) {
  fl_points( p, n, FL_YELLOW);
}

// button callback example
#if 0
static void dl_traffic_on_off( FL_OBJECT *button, long arg) {
  if (fl_get_button(button)) {
    fl_set_object_label(button, "DL Traffic ON");
    otg_enabled = 1;
    fl_set_object_color(button, FL_GREEN, FL_GREEN);
  } else {
    fl_set_object_label(button, "DL Traffic OFF");
    otg_enabled = 0;
    fl_set_object_color(button, FL_RED, FL_RED);
  }
}
#endif

#define WATERFALL 10000

static void commonGraph(OAIgraph_t *graph, int type, FL_Coord x, FL_Coord y, FL_Coord w, FL_Coord h, const char *label, FL_COLOR pointColor) {
  if (type==WATERFALL) {
    graph->waterFallh=h-15;
    graph->waterFallAvg=malloc(sizeof(*graph->waterFallAvg) * graph->waterFallh);

    for (int i=0; i< graph->waterFallh; i++)
      graph->waterFallAvg[i]=0;

    graph->graph=fl_add_canvas(FL_NORMAL_CANVAS, x, y, w, graph->waterFallh, label);
    graph->text=fl_add_text(FL_NORMAL_TEXT, x, y+graph->waterFallh, w, 15, label);
    fl_set_object_lcolor(graph->text,FL_WHITE);
    fl_set_object_color(graph->text, FL_BLACK, FL_BLACK);
    fl_set_object_lalign(graph->text, FL_ALIGN_CENTER );
  } else {
    graph->graph=fl_add_xyplot(type, x, y, w, h, label);
    fl_set_object_lcolor(graph->graph, FL_WHITE ); // Label color
    fl_set_object_color(graph->graph, FL_BLACK, pointColor);

    for (int i=0; i< FL_MAX_XYPLOTOVERLAY; i++)
      fl_set_xyplot_symbol(graph->graph, i, drawsymbol);
  }

  graph->x=x;
  graph->y=y;
  graph->w=w;
  graph->h=h;
  graph->maxX=0;
  graph->maxY=0;
  graph->minX=0;
  graph->minY=0;
  graph->initDone=false;
  graph->iteration=0;
}

static OAIgraph_t gNBcommonGraph( void (*funct) (OAIgraph_t *graph, scopeData_t *p, int UE_id),
                                  int type, FL_Coord x, FL_Coord y, FL_Coord w, FL_Coord h, const char *label, FL_COLOR pointColor) {
  OAIgraph_t graph;
  commonGraph(&graph, type, x, y, w, h, label, pointColor);
  graph.gNBfunct=funct;
  graph.nrUEfunct=NULL;
  return graph;
}

static OAIgraph_t nrUEcommonGraph( void (*funct) (OAIgraph_t *graph, PHY_VARS_NR_UE *phy_vars_ue, int eNB_id, int UE_id),
                                   int type, FL_Coord x, FL_Coord y, FL_Coord w, FL_Coord h, const char *label, FL_COLOR pointColor) {
  OAIgraph_t graph;
  commonGraph(&graph, type, x, y, w, h, label, pointColor);
  graph.gNBfunct=NULL;
  graph.nrUEfunct=funct;
  return graph;
}

static void setRange(OAIgraph_t *graph, float minX, float maxX, float minY, float maxY) {
  if ( maxX > graph->maxX ||  minX < graph->minX ||
       abs(maxX-graph->maxX)>abs(graph->maxX)/2 ||
       abs(maxX-graph->maxX)>abs(graph->maxX)/2 ) {
    graph->maxX/=2;
    graph->minX/=2;
    graph->maxX=max(graph->maxX,maxX);
    graph->minX=min(graph->minX,minX);
    fl_set_xyplot_xbounds(graph->graph, graph->minX*1.2, graph->maxX*1.2);
  }

  if ( maxY > graph->maxY || minY < graph->minY ||
       abs(maxY-graph->maxY)>abs(graph->maxY)/2 ||
       abs(maxY-graph->maxY)>abs(graph->maxY)/2 ) {
    graph->maxY/=2;
    graph->minY/=2;
    graph->maxY=max(graph->maxY,maxY);
    graph->minY=min(graph->minY,minY);
    fl_set_xyplot_ybounds(graph->graph, graph->minY*1.2, graph->maxY*1.2);
  }
}

static void oai_xygraph_getbuff(OAIgraph_t *graph, float **x, float **y, int len, int layer) {
  float *old_x;
  float *old_y;
  int old_len=-1;

  if (graph->iteration >1)
    fl_get_xyplot_data_pointer(graph->graph, layer, &old_x, &old_y, &old_len);

  if (old_len != len) {
    LOG_W(HW,"allocating graph of %d scope\n", len);
    float values[len];
    float time[len];

    // make time in case we will use it
    for (int i=0; i<len; i++)
      time[i] = values[i] = i;

    if (layer==0)
      fl_set_xyplot_data(graph->graph,time,values,len,"","","");
    else
      fl_add_xyplot_overlay(graph->graph,layer,time,values,len,rx_antenna_colors[layer]);

    fl_get_xyplot_data_pointer(graph->graph, layer, &old_x, &old_y, &old_len);
    AssertFatal(old_len==len,"");
  }

  *x=old_x;
  *y=old_y;
}

static void oai_xygraph(OAIgraph_t *graph, float *x, float *y, int len, int layer, boolean_t NoAutoScale) {
  fl_redraw_object(graph->graph);

  if ( NoAutoScale && graph->iteration%NoAutoScale == 0) {
    float maxX=0, maxY=0, minX=0, minY=0;

    for (int k=0; k<len; k++) {
      maxX=max(maxX,x[k]);
      minX=min(minX,x[k]);
      maxY=max(maxY,y[k]);
      minY=min(minY,y[k]);
    }

    setRange(graph, minX-5, maxX+5, minY-5, maxY+5);
  }

  graph->iteration++;
}

static void genericWaterFall (OAIgraph_t *graph, scopeSample_t *values, const int datasize, const int divisions, const char *label) {
  if ( values == NULL )
    return;

  fl_winset(FL_ObjWin(graph->graph));
  const int samplesPerPixel=datasize/graph->w;
  int displayPart=graph->waterFallh-ScaleZone;
  int row=graph->iteration%displayPart;
  double avg=0;

  for (int i=0; i < displayPart; i++)
    avg+=graph->waterFallAvg[i];

  avg/=displayPart;
  graph->waterFallAvg[row]=0;

  for (int pix=0; pix<graph->w; pix++) {
    scopeSample_t *end=values+(pix+1)*samplesPerPixel;
    end-=2;
    AssertFatal(end <= values+datasize,"diff : %ld", end-values+datasize);
    double val=0;

    for (scopeSample_t *s=values+(pix)*samplesPerPixel;
         s <end;
         s++)
      val += SquaredNorm(*s);

    val/=samplesPerPixel;
    graph->waterFallAvg[row]+=val/graph->w;
    int col=0;

    if (val > avg*2 )
      col=1;

    if (val > avg*10 )
      col=2;

    if (val > avg*100 )
      col=3;

    fl_point(pix, graph->iteration%displayPart, water_colors[col]);
  }

  if (graph->initDone==false) {
    for ( int i=0; i < graph->waterFallh; i++ )
      for ( int j = 0 ; j < graph->w ; j++ )
        fl_point(j, i, FL_BLACK);

    for ( int i=1; i<divisions; i++)
      for (int j= displayPart; j<graph->waterFallh; j++)
        fl_point(i*(graph->w/divisions),j, FL_WHITE);

    graph->initDone=true;
  }

  fl_set_object_label_f(graph->text, "%s, avg I/Q pow: %4.1f", label, sqrt(avg));
  graph->iteration++;
}

static void genericPowerPerAntena(OAIgraph_t  *graph, const int nb_ant, const scopeSample_t **data, const int len) {
  float *values, *time;
  oai_xygraph_getbuff(graph, &time, &values, len, 0);

  for (int ant=0; ant<nb_ant; ant++) {
    if (data[ant] != NULL) {
      for (int i=0; i<len; i++) {
        values[i] = SquaredNorm(data[ant][i]);
      }

      oai_xygraph(graph,time,values, len, ant, 10);
    }
  }
}

static void gNBWaterFall (OAIgraph_t *graph, scopeData_t *p, int nb_UEs) {
  NR_DL_FRAME_PARMS *frame_parms=&p->gNB->frame_parms;
  //use 1st antenna
  genericWaterFall(graph, (scopeSample_t *)p->ru->common.rxdata[0],
                   frame_parms->samples_per_frame,  frame_parms->slots_per_frame,
                   "X axis:one frame in time");
}

/* replaced by waterfall
static void timeSignal (OAIgraph_t *graph, PHY_VARS_gNB *phy_vars_gnb, RU_t *phy_vars_ru, const int nb_UEs) {
  // Received signal in time domain of receive antenna 0
  if (!phy_vars_ru->common.rxdata)
    return;

  NR_DL_FRAME_PARMS *frame_parms=&phy_vars_gnb->frame_parms;
  genericLogPowerPerAntena(graph, frame_parms->nb_antennas_rx,
                           (const scopeSample_t **)phy_vars_ru->common.rxdata,
                           frame_parms->samples_per_frame);
}
*/

static void timeResponse (OAIgraph_t *graph, scopeData_t *p, int nb_UEs) {
  const int len=2*p->gNB->frame_parms.ofdm_symbol_size;
  float *values, *time;
  oai_xygraph_getbuff(graph, &time, &values, len, 0);
  const int ant=0; // display antenna 0 for each UE

  for (int ue=0; ue<nb_UEs; ue++) {
    if ( p->gNB->pusch_vars && p->gNB->pusch_vars[ue] &&
         p->gNB->pusch_vars[ue]->ul_ch_estimates_time &&
         p->gNB->pusch_vars[ue]->ul_ch_estimates_time[ant] ) {
      scopeSample_t *data= (scopeSample_t *)p->gNB->pusch_vars[ue]->ul_ch_estimates_time[ant];

      if (data != NULL) {
        for (int i=0; i<len; i++) {
          values[i] = SquaredNorm(data[i]);
        }

        oai_xygraph(graph,time,values, len, ue, 10);
      }
    }
  }
}

static void gNBfreqWaterFall (OAIgraph_t *graph, scopeData_t *p, int nb_UEs) {
  NR_DL_FRAME_PARMS *frame_parms=&p->gNB->frame_parms;
  //use 1st antenna
  genericWaterFall(graph, (scopeSample_t *)p->rxdataF, frame_parms->samples_per_frame_wCP,
                   frame_parms->slots_per_frame,
                   "X axis: Frequency domain, one subframe");
}

/*
static void frequencyResponse (OAIgraph_t *graph, PHY_VARS_gNB *phy_vars_gnb, RU_t *phy_vars_ru, int nb_UEs) {
  NR_DL_FRAME_PARMS *frame_parms=&phy_vars_gnb->frame_parms;
  genericLogPowerPerAntena(graph, frame_parms->nb_antennas_rx,
                           (const scopeSample_t **)phy_vars_ru->common.rxdataF,
                           frame_parms->samples_per_slot_wCP);
}
*/

static void puschLLR (OAIgraph_t *graph, scopeData_t *p, int nb_UEs) {
  //int Qm = 2;
  int coded_bits_per_codeword =3*8*6144+12; // (8*((3*8*6144)+12)); // frame_parms->N_RB_UL*12*Qm*frame_parms->symbols_per_tti;

  for (int ue=0; ue<nb_UEs; ue++) {
    if ( p->gNB->pusch_vars &&
         p->gNB->pusch_vars[ue] &&
         p->gNB->pusch_vars[ue]->llr ) {
      int16_t *pusch_llr = (int16_t *)p->gNB->pusch_vars[ue]->llr;
      float *llr, *bit;
      oai_xygraph_getbuff(graph, &bit, &llr, coded_bits_per_codeword, ue);

      for (int i=0; i<coded_bits_per_codeword; i++) {
        llr[i] = (float) pusch_llr[i];
      }

      oai_xygraph(graph,bit,llr,coded_bits_per_codeword,ue,10);
    }
  }
}

static void puschIQ (OAIgraph_t *graph, scopeData_t *p, int nb_UEs) {
  NR_DL_FRAME_PARMS *frame_parms=&p->gNB->frame_parms;
  int sz=frame_parms->N_RB_UL*12*frame_parms->symbols_per_slot;

  for (int ue=0; ue<nb_UEs; ue++) {
    if ( p->gNB->pusch_vars &&
         p->gNB->pusch_vars[ue] &&
         p->gNB->pusch_vars[ue]->rxdataF_comp &&
         p->gNB->pusch_vars[ue]->rxdataF_comp[0] ) {
      scopeSample_t *pusch_comp = (scopeSample_t *) p->gNB->pusch_vars[ue]->rxdataF_comp[0];
      float *I, *Q;
      oai_xygraph_getbuff(graph, &I, &Q, sz, ue);

      for (int k=0; k<sz; k++ ) {
        I[k] = pusch_comp[k].r;
        Q[k] = pusch_comp[k].i;
      }

      oai_xygraph(graph,I,Q,sz,ue,10);
    }
  }
}

static void pucchEnergy (OAIgraph_t *graph, scopeData_t *p, int nb_UEs) {
  // PUSCH I/Q of MF Output
  /*
    int32_t *pucch1ab_comp = (int32_t *) NULL; //phy_vars_gnb->pucch1ab_stats[UE_id];
    int32_t *pucch1_comp = (int32_t *) NULL; //phy_vars_gnb->pucch1_stats[UE_id];
    float I_pucch[10240],Q_pucch[10240],A_pucch[10240],B_pucch[10240],C_pucch[10240];

    for (int ind=0; ind<10240; ind++) {
      I_pucch[ind] = (float)pucch1ab_comp[2*(ind)];
      Q_pucch[ind] = (float)pucch1ab_comp[2*(ind)+1];
      A_pucch[ind] = pucch1_comp?(10*log10(pucch1_comp[ind])):0;
      B_pucch[ind] = ind;
      int32_t *pucch1_thres = (int32_t *) NULL; // phy_vars_gnb->pucch1_stats_thres[UE_id];
      C_pucch[ind] = pucch1_thres?(float)pucch1_thres[ind]:0;
    }

    fl_set_xyplot_data(graph,I_pucch,Q_pucch,10240,"","","");
    fl_set_xyplot_data(graph,B_pucch,A_pucch,1024,"","","");
    fl_add_xyplot_overlay(graph,1,B_pucch,C_pucch,1024,FL_RED);
    fl_set_xyplot_ybounds(graph,-5000,5000);
    fl_set_xyplot_xbounds(graph,-5000,5000);
    fl_set_xyplot_ybounds(graph,0,80);
  }
  */
}
static void pucchIQ (OAIgraph_t *graph, scopeData_t *p, int nb_UEs) {
}
static void puschThroughtput (OAIgraph_t *graph, scopeData_t *p, int nb_UEs) {
  // PUSCH Throughput
  /*
  float tput_time_enb[NUMBER_OF_UE_MAX][TPUT_WINDOW_LENGTH] = {{0}};
  float tput_enb[NUMBER_OF_UE_MAX][TPUT_WINDOW_LENGTH] = {{0}};

  memmove( tput_time_enb[UE_id], &tput_time_enb[UE_id][1], (TPUT_WINDOW_LENGTH-1)*sizeof(float) );
  memmove( tput_enb[UE_id], &tput_enb[UE_id][1], (TPUT_WINDOW_LENGTH-1)*sizeof(float) );
  tput_time_enb[UE_id][TPUT_WINDOW_LENGTH-1]  = (float) 0;
  //  tput_enb[UE_id][TPUT_WINDOW_LENGTH-1] = ((float) total_dlsch_bitrate)/1000.0;
  fl_set_xyplot_data(graph,tput_time_enb[UE_id],tput_enb[UE_id],TPUT_WINDOW_LENGTH,"","","");
  //    fl_get_xyplot_ybounds(form->pusch_tput,&ymin,&ymax);
  //    fl_set_xyplot_ybounds(form->pusch_tput,0,ymax);
  */
}
static OAI_phy_scope_t *create_phy_scope_gnb(void) {
  FL_OBJECT *obj;
  OAI_phy_scope_t *fdui = calloc(( sizeof *fdui ),1);
  // Define form
  fdui->phy_scope = fl_bgn_form( FL_NO_BOX, 800, 800 );
  // This the whole UI box
  obj = fl_add_box( FL_BORDER_BOX, 0, 0, 800, 800, "" );
  fl_set_object_color( obj, FL_BLACK, FL_WHITE );
  int curY=0,x,y,w,h;
  // Received signal
  fdui->graph[0] = gNBcommonGraph( gNBWaterFall, WATERFALL, 0, curY, 400, 100,
                                   "Received Signal (Time-Domain, one frame)", FL_RED );
  // Time-domain channel response
  fdui->graph[1] = gNBcommonGraph( timeResponse, FL_NORMAL_XYPLOT, 410, curY, 400, 100,
                                   "SRS Frequency Response (samples, abs)", FL_RED );
  fl_get_object_bbox(fdui->graph[1].graph,&x, &y,&w, &h);
  curY+=h;
  // Frequency-domain channel response
  fdui->graph[2] = gNBcommonGraph( gNBfreqWaterFall, WATERFALL, 0, curY, 800, 100,
                                   "Channel Frequency domain (RE, one frame)", FL_RED );
  fl_get_object_bbox(fdui->graph[2].graph,&x, &y,&w, &h);
  curY+=h+20;
  // LLR of PUSCH
  fdui->graph[3] = gNBcommonGraph( puschLLR, FL_POINTS_XYPLOT, 0, curY, 500, 200,
                                   "PUSCH Log-Likelihood Ratios (LLR, mag)", FL_YELLOW );
  // I/Q PUSCH comp
  fdui->graph[4] = gNBcommonGraph( puschIQ, FL_POINTS_XYPLOT, 500, curY, 300, 200,
                                   "PUSCH I/Q of MF Output", FL_YELLOW );
  fl_get_object_bbox(fdui->graph[3].graph,&x, &y,&w, &h);
  curY+=h;
  // I/Q PUCCH comp (format 1)
  fdui->graph[5] = gNBcommonGraph( pucchEnergy, FL_POINTS_XYPLOT, 0, curY, 300, 100,
                                   "PUCCH1 Energy (SR)", FL_YELLOW );
  //  fl_set_xyplot_xgrid( fdui->pusch_llr,FL_GRID_MAJOR);
  // I/Q PUCCH comp (fromat 1a/b)
  fdui->graph[6] = gNBcommonGraph( pucchIQ, FL_POINTS_XYPLOT, 500, curY, 300, 100,
                                   "PUCCH I/Q of MF Output", FL_YELLOW );
  fl_get_object_bbox(fdui->graph[6].graph,&x, &y,&w, &h);
  curY+=h;
  // Throughput on PUSCH
  fdui->graph[7] = gNBcommonGraph( puschThroughtput, FL_NORMAL_XYPLOT, 0, curY, 500, 100,
                                   "PUSCH Throughput [frame]/[kbit/s]", FL_WHITE );
  fdui->graph[8].graph=NULL;
  fl_end_form( );
  fdui->phy_scope->fdui = fdui;
  fl_show_form (fdui->phy_scope, FL_PLACE_HOTSPOT, FL_FULLBORDER, "LTE UL SCOPE gNB");
  return fdui;
}
static const int scope_enb_num_ue = 1;
void phy_scope_gNB(OAI_phy_scope_t *form,
                   scopeData_t *p,
                   int UE_id) {
  static OAI_phy_scope_t *rememberForm=NULL;

  if (form==NULL)
    form=rememberForm;
  else
    rememberForm=form;

  if (form==NULL)
    return;

  int i=0;

  while (form->graph[i].graph) {
    form->graph[i].gNBfunct(form->graph+i, p, UE_id);
    i++;
  }

  //fl_check_forms();
}
static void *scope_thread_gNB(void *arg) {
  scopeData_t *p=(scopeData_t *) arg;
  //# ifdef ENABLE_XFORMS_WRITE_STATS
  //  FILE *gNB_stats = fopen("gNB_stats.txt", "w");
  //#endif
  size_t stksize=0;
  pthread_attr_t atr;
  pthread_attr_init(&atr);
  pthread_attr_getstacksize(&atr, &stksize);
  pthread_attr_setstacksize(&atr,32*1024*1024 );
  sleep(3); // no clean interthread barriers
  int fl_argc=1;
  char *name="5G-gNB-scope";
  fl_initialize (&fl_argc, &name, NULL, 0, 0);
  int nb_ue=min(NUMBER_OF_UE_MAX, scope_enb_num_ue);
  OAI_phy_scope_t  *form_gnb = create_phy_scope_gnb();

  while (!oai_exit) {
    phy_scope_gNB(form_gnb, p, nb_ue);
    usleep(99*1000);
  }

  return NULL;
}
static void copyRxdataF(int32_t *data, int slot,  void *scopeData) {
  scopeData_t *scope=(scopeData_t *)scopeData;
  memcpy(scope->rxdataF + slot*scope->gNB->frame_parms.samples_per_slot_wCP,
         data,
         scope->gNB->frame_parms.samples_per_slot_wCP);
}
void gNBinitScope(scopeParms_t *p) {
  p->gNB->scopeData=malloc(sizeof(scopeData_t));
  AssertFatal(p->gNB->scopeData,"");
  scopeData_t *scope=(scopeData_t *) p->gNB->scopeData;
  scope->argc=p->argc;
  scope->argv=p->argv;
  scope->ru=p->ru;
  scope->gNB=p->gNB;
  scope->slotFunc=copyRxdataF;
  scope->rxdataF=(int32_t *) calloc(p->gNB->frame_parms.samples_per_frame_wCP*sizeof(int32_t),1);
  AssertFatal(scope->rxdataF,"");
  pthread_t forms_thread;
  threadCreate(&forms_thread, scope_thread_gNB, p->gNB->scopeData, "scope", -1, OAI_PRIORITY_RT_LOW);
}
static void ueWaterFall  (OAIgraph_t *graph, PHY_VARS_NR_UE *phy_vars_ue, int eNB_id, int UE_id) {
  // Received signal in time domain of receive antenna 0
  genericWaterFall(graph,
                   (scopeSample_t *) phy_vars_ue->common_vars.rxdata[0],
                   phy_vars_ue->frame_parms.samples_per_frame,
                   phy_vars_ue->frame_parms.slots_per_frame,
                   "X axis: one frame time");
}
/* replaced by waterfall
static void ueTimeResponse  (OAIgraph_t *graph, PHY_VARS_NR_UE *phy_vars_ue, int eNB_id, int UE_id) {
  // Received signal in time domain of receive antenna 0
  genericLogPowerPerAntena(graph, phy_vars_ue->frame_parms.nb_antennas_rx,
                           (const scopeSample_t **) phy_vars_ue->common_vars.rxdata,
                           phy_vars_ue->frame_parms.samples_per_frame);
}
*/
static void ueChannelResponse  (OAIgraph_t *graph, PHY_VARS_NR_UE *phy_vars_ue, int eNB_id, int UE_id) {
  // Channel Impulse Response
  genericPowerPerAntena(graph, phy_vars_ue->frame_parms.nb_antennas_rx,
                        (const scopeSample_t **) phy_vars_ue->pbch_vars[eNB_id]->dl_ch_estimates_time,
                        phy_vars_ue->frame_parms.ofdm_symbol_size>>3);
}
static void ueFreqWaterFall (OAIgraph_t *graph,PHY_VARS_NR_UE *phy_vars_ue, int eNB_id, int UE_id ) {
  NR_DL_FRAME_PARMS *frame_parms=&phy_vars_ue->frame_parms;
  //use 1st antenna
  genericWaterFall(graph,
                   (scopeSample_t *)phy_vars_ue->common_vars.common_vars_rx_data_per_thread[0].rxdataF[0],
                   frame_parms->samples_per_slot_wCP,
                   phy_vars_ue->frame_parms.slots_per_frame,
                   "X axis: one frame frequency" );
}
/*
static void uePbchFrequencyResp  (OAIgraph_t *graph, PHY_VARS_NR_UE *phy_vars_ue, int eNB_id, int UE_id) {
  // Channel Frequency Response (includes 5 complex sample for filter)
  if (!phy_vars_ue->pbch_vars[eNB_id]->dl_ch_estimates)
    return;

  NR_DL_FRAME_PARMS *frame_parms = &phy_vars_ue->frame_parms;
  uint8_t nb_antennas_rx = frame_parms->nb_antennas_rx;
  uint8_t nb_antennas_tx = frame_parms->nb_antenna_ports_gNB;
  scopeSample_t   **chest_f = (scopeSample_t **) phy_vars_ue->pbch_vars[eNB_id]->dl_ch_estimates;
  int ind = 0;
  float *freq, *chest_f_abs;
  oai_xygraph_getbuff(graph, &freq, &chest_f_abs, frame_parms->ofdm_symbol_size, 0);

  for (int atx=0; atx<nb_antennas_tx; atx++) {
    for (int arx=0; arx<nb_antennas_rx; arx++) {
      if (chest_f[(atx<<1)+arx] != NULL) {

        for (int k=0; k<frame_parms->ofdm_symbol_size; k++) {
          freq[ind] = (float)ind;
          chest_f_abs[ind] = (short)10*log10(1.0+SquaredNorm(chest_f[(atx<<1)+arx][6144+k]));
          ind++;
        }
      }
    }
  }

  // tx antenna 0
  //fl_set_xyplot_xbounds(form->chest_f,0,nb_antennas_rx*nb_antennas_tx*nsymb_ce);
  //fl_set_xyplot_xtics(form->chest_f,nb_antennas_rx*nb_antennas_tx*frame_parms->symbols_per_tti,2);
  //        fl_set_xyplot_xtics(form->chest_f,nb_antennas_rx*nb_antennas_tx*2,2);
  //fl_set_xyplot_xgrid(form->chest_f,FL_GRID_MAJOR);
  oai_xygraph(graph,freq,chest_f_abs,frame_parms->ofdm_symbol_size,0,10);
}
*/
static void uePbchLLR  (OAIgraph_t *graph, PHY_VARS_NR_UE *phy_vars_ue, int eNB_id, int UE_id) {
  // PBCH LLRs
  if ( !phy_vars_ue->pbch_vars[eNB_id]->llr)
    return;

  int16_t *pbch_llr = (int16_t *) phy_vars_ue->pbch_vars[eNB_id]->llr;
  float *llr_pbch, *bit_pbch;
  oai_xygraph_getbuff(graph, &bit_pbch, &llr_pbch, 864, 0);

  for (int i=0; i<864; i++) {
    llr_pbch[i] = (float) pbch_llr[i];
  }

  oai_xygraph(graph,bit_pbch,llr_pbch,864,0,10);
}
static void uePbchIQ  (OAIgraph_t *graph, PHY_VARS_NR_UE *phy_vars_ue, int eNB_id, int UE_id) {
  // PBCH I/Q of MF Output
  if (!phy_vars_ue->pbch_vars[eNB_id]->rxdataF_comp[0])
    return;

  scopeSample_t *pbch_comp = (scopeSample_t *) phy_vars_ue->pbch_vars[eNB_id]->rxdataF_comp[0];
  float *I, *Q;
  oai_xygraph_getbuff(graph, &I, &Q, 180*3, 0);
  memset(I,0,180*3*sizeof(*I));
  memset(Q,0,180*3*sizeof(*Q));
  int first_symbol=1;
  int base=0;

  for (int symbol=first_symbol; symbol<(first_symbol+3); symbol++) {
    int nb_re;

    if (symbol == 2 || symbol == 6)
      nb_re = 72;
    else
      nb_re = 180;

    AssertFatal(base+nb_re<180*3,"");

    for (int i=0; i<nb_re; i++) {
      I[base+i] = pbch_comp[symbol*20*12+i].r;
      Q[base+i] = pbch_comp[symbol*20*12+i].i;
    }

    base+=nb_re;
  }

  AssertFatal(base <= 180*3,"");
  oai_xygraph(graph,I,Q,base,0, 10);
}
static void uePcchLLR  (OAIgraph_t *graph, PHY_VARS_NR_UE *phy_vars_ue, int eNB_id, int UE_id) {
  // PDCCH LLRs
  if (!phy_vars_ue->pdcch_vars[0][eNB_id]->llr)
    return;

  //int num_re = 4*273*12; // 12*frame_parms->N_RB_DL*num_pdcch_symbols
  //int Qm = 2;
  int coded_bits_per_codeword = 2*4*100*12; //num_re*Qm;
  float *llr, *bit;
  oai_xygraph_getbuff(graph, &bit, &llr, coded_bits_per_codeword*RX_NB_TH_MAX, 0);
  int base=0;

  for (int thr=0 ; thr < RX_NB_TH_MAX ; thr ++ ) {
    int16_t *pdcch_llr = (int16_t *) phy_vars_ue->pdcch_vars[thr][eNB_id]->llr;

    for (int i=0; i<coded_bits_per_codeword; i++) {
      llr[base+i] = (float) pdcch_llr[i];
    }

    base+=coded_bits_per_codeword;
  }

  AssertFatal(base <= coded_bits_per_codeword*RX_NB_TH_MAX, "");
  oai_xygraph(graph,bit,llr,base,0,10);
}
static void uePcchIQ  (OAIgraph_t *graph, PHY_VARS_NR_UE *phy_vars_ue, int eNB_id, int UE_id) {
  // PDCCH I/Q of MF Output
  if (!phy_vars_ue->pdcch_vars[0][eNB_id]->rxdataF_comp[0])
    return;

  int nb=4*273*12; // 12*frame_parms->N_RB_DL*num_pdcch_symbols
  float *I, *Q;
  oai_xygraph_getbuff(graph, &I, &Q, nb*RX_NB_TH_MAX, 0);
  int base=0;

  for (int thr=0 ; thr < RX_NB_TH_MAX ; thr ++ ) {
    scopeSample_t *pdcch_comp = (scopeSample_t *) phy_vars_ue->pdcch_vars[thr][eNB_id]->rxdataF_comp[0];

    for (int i=0; i< nb; i++) {
      I[base+i] = pdcch_comp[i].r;
      Q[base+i] = pdcch_comp[i].i;
    }

    base+=nb;
  }

  AssertFatal(base <= nb*RX_NB_TH_MAX, "");
  oai_xygraph(graph,I,Q,base,0,10);
}
static void uePdschLLR  (OAIgraph_t *graph, PHY_VARS_NR_UE *phy_vars_ue, int eNB_id, int UE_id) {
  // PDSCH LLRs
  if (!phy_vars_ue->pdsch_vars[0][eNB_id]->llr[0])
    return;

  int num_re = 4500;
  int Qm = 2;
  int coded_bits_per_codeword = num_re*Qm;
  float *llr, *bit;
  oai_xygraph_getbuff(graph, &bit, &llr, coded_bits_per_codeword*RX_NB_TH_MAX, 0);
  int base=0;

  for (int thr=0 ; thr < RX_NB_TH_MAX ; thr ++ ) {
    int16_t *pdsch_llr = (int16_t *) phy_vars_ue->pdsch_vars[thr][eNB_id]->llr[0]; // stream 0

    for (int i=0; i<coded_bits_per_codeword; i++) {
      llr[base+i] = (float) pdsch_llr[i];
      bit[base+i] = (float) base+i;
    }

    base+=coded_bits_per_codeword;
  }

  AssertFatal(base <= coded_bits_per_codeword*RX_NB_TH_MAX, "");
  //fl_set_xyplot_xbounds(form->pdsch_llr,0,coded_bits_per_codeword);
  oai_xygraph(graph,bit,llr,base,0,10);
}
static void uePdschIQ  (OAIgraph_t *graph, PHY_VARS_NR_UE *phy_vars_ue, int eNB_id, int UE_id) {
  // PDSCH I/Q of MF Output
  if (!phy_vars_ue->pdsch_vars[0][eNB_id]->rxdataF_comp0[0])
    return;

  NR_DL_FRAME_PARMS *frame_parms = &phy_vars_ue->frame_parms;
  int sz=7*2*frame_parms->N_RB_DL*12; // size of the malloced buffer
  float *I, *Q;
  oai_xygraph_getbuff(graph, &I, &Q, sz*RX_NB_TH_MAX, 0);
  int base=0;
  memset(I+base, 0, sz*RX_NB_TH_MAX * sizeof(*I));
  memset(Q+base, 0, sz*RX_NB_TH_MAX * sizeof(*Q));

  for (int thr=0 ; thr < RX_NB_TH_MAX ; thr ++ ) {
    scopeSample_t *pdsch_comp = (scopeSample_t *) phy_vars_ue->pdsch_vars[thr][eNB_id]->rxdataF_comp0[0];

    for (int s=0; s<sz; s++) {
      I[s+base] += pdsch_comp[s].r;
      Q[s+base] += pdsch_comp[s].i;
    }

    base+=sz;
  }

  AssertFatal(base <= sz*RX_NB_TH_MAX, "");
  oai_xygraph(graph,I,Q,sz*RX_NB_TH_MAX,0,10);
}
static void uePdschThroughput  (OAIgraph_t *graph, PHY_VARS_NR_UE *phy_vars_ue, int eNB_id, int UE_id) {
  /*
  float tput_time_ue[NUMBER_OF_UE_MAX][TPUT_WINDOW_LENGTH] = {{0}};
  float tput_ue[NUMBER_OF_UE_MAX][TPUT_WINDOW_LENGTH] = {{0}};
  float tput_ue_max[NUMBER_OF_UE_MAX] = {0};


  // PDSCH Throughput
  memmove( tput_time_ue[UE_id], &tput_time_ue[UE_id][1], (TPUT_WINDOW_LENGTH-1)*sizeof(float) );
  memmove( tput_ue[UE_id],      &tput_ue[UE_id][1],      (TPUT_WINDOW_LENGTH-1)*sizeof(float) );

  tput_time_ue[UE_id][TPUT_WINDOW_LENGTH-1]  = (float) frame;
  tput_ue[UE_id][TPUT_WINDOW_LENGTH-1] = ((float) total_dlsch_bitrate)/1000.0;

  if (tput_ue[UE_id][TPUT_WINDOW_LENGTH-1] > tput_ue_max[UE_id]) {
  tput_ue_max[UE_id] = tput_ue[UE_id][TPUT_WINDOW_LENGTH-1];
  }

  fl_set_xyplot_data(form->pdsch_tput,tput_time_ue[UE_id],tput_ue[UE_id],TPUT_WINDOW_LENGTH,"","","");

  fl_set_xyplot_ybounds(form->pdsch_tput,0,tput_ue_max[UE_id]);
  */
}
static OAI_phy_scope_t *create_phy_scope_nrue( int ID ) {
  FL_OBJECT *obj;
  OAI_phy_scope_t *fdui = calloc(( sizeof *fdui ),1);
  // Define form
  fdui->phy_scope = fl_bgn_form( FL_NO_BOX, 800, 900 );
  // This the whole UI box
  obj = fl_add_box( FL_BORDER_BOX, 0, 0, 800, 900, "" );
  fl_set_object_color( obj, FL_BLACK, FL_BLACK );
  int curY=0,x,y,w,h;
  // Received signal
  fdui->graph[0] = nrUEcommonGraph(ueWaterFall,
                                   WATERFALL, 0, curY, 400, 100, "Received Signal (Time-Domain, one frame)", FL_RED );
  // Time-domain channel response
  fdui->graph[1] = nrUEcommonGraph(ueChannelResponse,
                                   FL_NORMAL_XYPLOT, 400, curY, 400, 100, "Channel Impulse Response (samples, abs)", FL_RED );
  fl_get_object_bbox(fdui->graph[1].graph,&x, &y,&w, &h);
  curY+=h;
  // Frequency-domain channel response
  fdui->graph[2] = nrUEcommonGraph(ueFreqWaterFall,
                                   WATERFALL, 0, curY, 800, 100, "Channel Frequency (RE, one slot)", FL_RED );
  fl_get_object_bbox(fdui->graph[2].graph,&x, &y,&w, &h);
  curY+=h+20;
  // LLR of PBCH
  fdui->graph[3] = nrUEcommonGraph(uePbchLLR,
                                   FL_POINTS_XYPLOT, 0, curY, 500, 100, "PBCH Log-Likelihood Ratios (LLR, mag)", FL_GREEN );
  fl_set_xyplot_xgrid(fdui->graph[3].graph,FL_GRID_MAJOR);
  // I/Q PBCH comp
  fdui->graph[4] = nrUEcommonGraph(uePbchIQ,
                                   FL_POINTS_XYPLOT, 500, curY, 300, 100, "PBCH I/Q of MF Output", FL_GREEN );
  fl_get_object_bbox(fdui->graph[3].graph,&x, &y,&w, &h);
  curY+=h;
  // LLR of PDCCH
  fdui->graph[5] = nrUEcommonGraph(uePcchLLR,
                                   FL_POINTS_XYPLOT, 0, curY, 500, 100, "PDCCH Log-Likelihood Ratios (LLR, mag)", FL_CYAN );
  // I/Q PDCCH comp
  fdui->graph[6] = nrUEcommonGraph(uePcchIQ,
                                   FL_POINTS_XYPLOT, 500, curY, 300, 100, "PDCCH I/Q of MF Output", FL_CYAN );
  fl_get_object_bbox(fdui->graph[5].graph,&x, &y,&w, &h);
  curY+=h;
  // LLR of PDSCH
  fdui->graph[7] = nrUEcommonGraph(uePdschLLR,
                                   FL_POINTS_XYPLOT, 0, curY, 500, 200, "PDSCH Log-Likelihood Ratios (LLR, mag)", FL_YELLOW );
  // I/Q PDSCH comp
  fdui->graph[8] = nrUEcommonGraph(uePdschIQ,
                                   FL_POINTS_XYPLOT, 500, curY, 300, 200, "PDSCH I/Q of MF Output", FL_YELLOW );
  fl_get_object_bbox(fdui->graph[8].graph,&x, &y,&w, &h);
  curY+=h;
  // Throughput on PDSCH
  fdui->graph[9] = nrUEcommonGraph(uePdschThroughput,
                                   FL_NORMAL_XYPLOT, 0, curY, 500, 100, "PDSCH Throughput [frame]/[kbit/s]", FL_WHITE );
  fdui->graph[10].graph=NULL;
  // Generic UE Button
#if 0
  fdui->button_0 = fl_add_button( FL_PUSH_BUTTON, 540, 720, 240, 40, "" );
  fl_set_object_lalign(fdui->button_0, FL_ALIGN_CENTER );
  //openair_daq_vars.use_ia_receiver = 0;
  fl_set_button(fdui->button_0,0);
  fl_set_object_label(fdui->button_0, "IA Receiver OFF");
  fl_set_object_color(fdui->button_0, FL_RED, FL_RED);
  fl_set_object_callback(fdui->button_0, ia_receiver_on_off, 0 );
  fl_hide_object(fdui->button_0);
#endif
  fl_end_form( );
  fdui->phy_scope->fdui = fdui;
  char buf[100];
  sprintf(buf,"NR DL SCOPE UE %d", ID);
  fl_show_form (fdui->phy_scope, FL_PLACE_HOTSPOT, FL_FULLBORDER, buf);
  return fdui;
}
void phy_scope_nrUE(OAI_phy_scope_t *form,
                    PHY_VARS_NR_UE *phy_vars_ue,
                    int eNB_id,
                    int UE_id) {
  static OAI_phy_scope_t *remeberForm=NULL;

  if (form==NULL)
    form=remeberForm;
  else
    remeberForm=form;

  if (form==NULL)
    return;

  int i=0;

  while (form->graph[i].graph) {
    form->graph[i].nrUEfunct(form->graph+i, phy_vars_ue, eNB_id, UE_id);
    i++;
  }

  //fl_check_forms();
}
static void *nrUEscopeThread(void *arg) {
  PHY_VARS_NR_UE *ue=(PHY_VARS_NR_UE *)arg;
  size_t stksize;
  pthread_attr_t atr;
  pthread_attr_getstacksize(&atr, &stksize);
  pthread_attr_setstacksize(&atr,32*1024*1024 );
  int fl_argc=1;
  char *name="5G-UE-scope";
  fl_initialize (&fl_argc, &name, NULL, 0, 0);
  OAI_phy_scope_t  *form_nrue=create_phy_scope_nrue(0);

  while (!oai_exit) {
    fl_freeze_form(form_nrue->phy_scope);
    phy_scope_nrUE(form_nrue,
                   ue,
                   0,0);
    fl_unfreeze_form(form_nrue->phy_scope);
    fl_redraw_form(form_nrue->phy_scope);
    usleep(99*1000);
  }

  pthread_exit((void *)arg);
}
void nrUEinitScope(PHY_VARS_NR_UE *ue) {
  pthread_t forms_thread;
  threadCreate(&forms_thread, nrUEscopeThread, ue, "scope", -1, OAI_PRIORITY_RT_LOW);
}
void nrscope_autoinit(void *dataptr) {
  AssertFatal( (IS_SOFTMODEM_GNB_BIT||IS_SOFTMODEM_5GUE_BIT),"Scope cannot find NRUE or GNB context");

  if (IS_SOFTMODEM_GNB_BIT)
    gNBinitScope(dataptr);
  else
    nrUEinitScope(dataptr);
}
// Kept to put back the functionality soon
#if 0
//FD_stats_form                  *form_stats=NULL,*form_stats_l2=NULL;
//char                            title[255];
//static pthread_t                forms_thread; //xforms
static void reset_stats_gNB(FL_OBJECT *button,
                            long arg) {
  int i,k;
  //PHY_VARS_gNB *phy_vars_gNB = RC.gNB[0][0];

  for (i=0; i<NUMBER_OF_UE_MAX; i++) {
    for (k=0; k<8; k++) { //harq_processes
      /*      for (j=0; j<phy_vars_gNB->dlsch[i][0]->Mlimit; j++) {
              phy_vars_gNB->UE_stats[i].dlsch_NAK[k][j]=0;
              phy_vars_gNB->UE_stats[i].dlsch_ACK[k][j]=0;
              phy_vars_gNB->UE_stats[i].dlsch_trials[k][j]=0;
        }
        phy_vars_gNB->UE_stats[i].dlsch_l2_errors[k]=0;
        phy_vars_gNB->UE_stats[i].ulsch_errors[k]=0;
        phy_vars_gNB->UE_stats[i].ulsch_consecutive_errors=0;
        phy_vars_gNB->UE_stats[i].dlsch_sliding_cnt=0;
        phy_vars_gNB->UE_stats[i].dlsch_NAK_round0=0;
        phy_vars_gNB->UE_stats[i].dlsch_mcs_offset=0;*/
    }
  }
}
static FD_stats_form *create_form_stats_form(int ID) {
  FL_OBJECT *obj;
  FD_stats_form *fdui = calloc(( sizeof *fdui ),1);
  fdui->vdata = fdui->cdata = NULL;
  fdui->ldata = 0;
  fdui->stats_form = fl_bgn_form( FL_NO_BOX, 1115, 900 );
  obj = fl_add_box( FL_UP_BOX, 0, 0, 1115, 900, "" );
  //fdui->stats_text = obj = fl_add_text( FL_NORMAL_TEXT, 60, 50, 1000, 810, "test" );
  //fl_set_object_lsize( obj, FL_TINY_SIZE );
  fdui->stats_text = obj = fl_add_browser( FL_NORMAL_BROWSER, 60, 50, 1000, 810, "test" );
  fl_set_browser_fontsize(obj,FL_TINY_SIZE);
  fdui->stats_button = obj = fl_add_button( FL_PUSH_BUTTON, 60, 10, 130, 30, "Reset Stats" );
  fl_set_object_lalign( obj, FL_ALIGN_CENTER );
  fl_set_object_color( obj, FL_GREEN, FL_GREEN);
  fl_end_form( );
  fdui->stats_form->fdui = fdui;
  return fdui;
}
#endif
