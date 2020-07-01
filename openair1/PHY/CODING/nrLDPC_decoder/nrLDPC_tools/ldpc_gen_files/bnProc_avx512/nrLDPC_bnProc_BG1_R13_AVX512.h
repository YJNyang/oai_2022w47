static inline void nrLDPC_bnProc_BG1_R13_AVX512(int8_t* bnProcBuf,int8_t* bnProcBufRes,  int8_t* llrRes, uint16_t Z ) {
        __m512i* p_bnProcBuf; 
        __m512i* p_bnProcBufRes; 
        __m512i* p_llrRes; 
        __m512i* p_res; 
        uint32_t M, i; 
// Process group with 2 CNs 
// Process group with 3 CNs 
// Process group with 4 CNs 
       M = (1*Z + 63)>>6;
    p_bnProcBuf     = (__m512i*) &bnProcBuf    [16128];
   p_bnProcBufRes    = (__m512i*) &bnProcBufRes   [16128];
            p_res = &p_bnProcBufRes[0];
            p_llrRes = (__m512i*) &llrRes  [16128];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[0 + i]);
}
            p_res = &p_bnProcBufRes[6];
            p_llrRes = (__m512i*) &llrRes  [16128];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[6 + i]);
}
            p_res = &p_bnProcBufRes[12];
            p_llrRes = (__m512i*) &llrRes  [16128];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[12 + i]);
}
            p_res = &p_bnProcBufRes[18];
            p_llrRes = (__m512i*) &llrRes  [16128];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[18 + i]);
}
// Process group with 5 CNs 
       M = (1*Z + 63)>>6;
    p_bnProcBuf     = (__m512i*) &bnProcBuf    [17664];
   p_bnProcBufRes    = (__m512i*) &bnProcBufRes   [17664];
            p_res = &p_bnProcBufRes[0];
            p_llrRes = (__m512i*) &llrRes  [16512];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[0 + i]);
}
            p_res = &p_bnProcBufRes[6];
            p_llrRes = (__m512i*) &llrRes  [16512];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[6 + i]);
}
            p_res = &p_bnProcBufRes[12];
            p_llrRes = (__m512i*) &llrRes  [16512];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[12 + i]);
}
            p_res = &p_bnProcBufRes[18];
            p_llrRes = (__m512i*) &llrRes  [16512];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[18 + i]);
}
            p_res = &p_bnProcBufRes[24];
            p_llrRes = (__m512i*) &llrRes  [16512];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[24 + i]);
}
// Process group with 6 CNs 
       M = (2*Z + 63)>>6;
    p_bnProcBuf     = (__m512i*) &bnProcBuf    [19584];
   p_bnProcBufRes    = (__m512i*) &bnProcBufRes   [19584];
            p_res = &p_bnProcBufRes[0];
            p_llrRes = (__m512i*) &llrRes  [16896];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[0 + i]);
}
            p_res = &p_bnProcBufRes[12];
            p_llrRes = (__m512i*) &llrRes  [16896];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[12 + i]);
}
            p_res = &p_bnProcBufRes[24];
            p_llrRes = (__m512i*) &llrRes  [16896];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[24 + i]);
}
            p_res = &p_bnProcBufRes[36];
            p_llrRes = (__m512i*) &llrRes  [16896];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[36 + i]);
}
            p_res = &p_bnProcBufRes[48];
            p_llrRes = (__m512i*) &llrRes  [16896];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[48 + i]);
}
            p_res = &p_bnProcBufRes[60];
            p_llrRes = (__m512i*) &llrRes  [16896];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[60 + i]);
}
// Process group with 7 CNs 
       M = (4*Z + 63)>>6;
    p_bnProcBuf     = (__m512i*) &bnProcBuf    [24192];
   p_bnProcBufRes    = (__m512i*) &bnProcBufRes   [24192];
            p_res = &p_bnProcBufRes[0];
            p_llrRes = (__m512i*) &llrRes  [17664];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[0 + i]);
}
            p_res = &p_bnProcBufRes[24];
            p_llrRes = (__m512i*) &llrRes  [17664];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[24 + i]);
}
            p_res = &p_bnProcBufRes[48];
            p_llrRes = (__m512i*) &llrRes  [17664];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[48 + i]);
}
            p_res = &p_bnProcBufRes[72];
            p_llrRes = (__m512i*) &llrRes  [17664];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[72 + i]);
}
            p_res = &p_bnProcBufRes[96];
            p_llrRes = (__m512i*) &llrRes  [17664];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[96 + i]);
}
            p_res = &p_bnProcBufRes[120];
            p_llrRes = (__m512i*) &llrRes  [17664];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[120 + i]);
}
            p_res = &p_bnProcBufRes[144];
            p_llrRes = (__m512i*) &llrRes  [17664];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[144 + i]);
}
// Process group with 8 CNs 
       M = (3*Z + 63)>>6;
    p_bnProcBuf     = (__m512i*) &bnProcBuf    [34944];
   p_bnProcBufRes    = (__m512i*) &bnProcBufRes   [34944];
            p_res = &p_bnProcBufRes[0];
            p_llrRes = (__m512i*) &llrRes  [19200];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[0 + i]);
}
            p_res = &p_bnProcBufRes[18];
            p_llrRes = (__m512i*) &llrRes  [19200];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[18 + i]);
}
            p_res = &p_bnProcBufRes[36];
            p_llrRes = (__m512i*) &llrRes  [19200];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[36 + i]);
}
            p_res = &p_bnProcBufRes[54];
            p_llrRes = (__m512i*) &llrRes  [19200];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[54 + i]);
}
            p_res = &p_bnProcBufRes[72];
            p_llrRes = (__m512i*) &llrRes  [19200];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[72 + i]);
}
            p_res = &p_bnProcBufRes[90];
            p_llrRes = (__m512i*) &llrRes  [19200];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[90 + i]);
}
            p_res = &p_bnProcBufRes[108];
            p_llrRes = (__m512i*) &llrRes  [19200];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[108 + i]);
}
            p_res = &p_bnProcBufRes[126];
            p_llrRes = (__m512i*) &llrRes  [19200];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[126 + i]);
}
// Process group with 9 CNs 
       M = (1*Z + 63)>>6;
    p_bnProcBuf     = (__m512i*) &bnProcBuf    [44160];
   p_bnProcBufRes    = (__m512i*) &bnProcBufRes   [44160];
            p_res = &p_bnProcBufRes[0];
            p_llrRes = (__m512i*) &llrRes  [20352];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[0 + i]);
}
            p_res = &p_bnProcBufRes[6];
            p_llrRes = (__m512i*) &llrRes  [20352];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[6 + i]);
}
            p_res = &p_bnProcBufRes[12];
            p_llrRes = (__m512i*) &llrRes  [20352];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[12 + i]);
}
            p_res = &p_bnProcBufRes[18];
            p_llrRes = (__m512i*) &llrRes  [20352];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[18 + i]);
}
            p_res = &p_bnProcBufRes[24];
            p_llrRes = (__m512i*) &llrRes  [20352];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[24 + i]);
}
            p_res = &p_bnProcBufRes[30];
            p_llrRes = (__m512i*) &llrRes  [20352];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[30 + i]);
}
            p_res = &p_bnProcBufRes[36];
            p_llrRes = (__m512i*) &llrRes  [20352];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[36 + i]);
}
            p_res = &p_bnProcBufRes[42];
            p_llrRes = (__m512i*) &llrRes  [20352];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[42 + i]);
}
            p_res = &p_bnProcBufRes[48];
            p_llrRes = (__m512i*) &llrRes  [20352];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[48 + i]);
}
// Process group with 10 CNs 
       M = (4*Z + 63)>>6;
    p_bnProcBuf     = (__m512i*) &bnProcBuf    [47616];
   p_bnProcBufRes    = (__m512i*) &bnProcBufRes   [47616];
            p_res = &p_bnProcBufRes[0];
            p_llrRes = (__m512i*) &llrRes  [20736];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[0 + i]);
}
            p_res = &p_bnProcBufRes[24];
            p_llrRes = (__m512i*) &llrRes  [20736];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[24 + i]);
}
            p_res = &p_bnProcBufRes[48];
            p_llrRes = (__m512i*) &llrRes  [20736];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[48 + i]);
}
            p_res = &p_bnProcBufRes[72];
            p_llrRes = (__m512i*) &llrRes  [20736];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[72 + i]);
}
            p_res = &p_bnProcBufRes[96];
            p_llrRes = (__m512i*) &llrRes  [20736];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[96 + i]);
}
            p_res = &p_bnProcBufRes[120];
            p_llrRes = (__m512i*) &llrRes  [20736];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[120 + i]);
}
            p_res = &p_bnProcBufRes[144];
            p_llrRes = (__m512i*) &llrRes  [20736];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[144 + i]);
}
            p_res = &p_bnProcBufRes[168];
            p_llrRes = (__m512i*) &llrRes  [20736];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[168 + i]);
}
            p_res = &p_bnProcBufRes[192];
            p_llrRes = (__m512i*) &llrRes  [20736];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[192 + i]);
}
            p_res = &p_bnProcBufRes[216];
            p_llrRes = (__m512i*) &llrRes  [20736];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[216 + i]);
}
// Process group with 11 CNs 
       M = (3*Z + 63)>>6;
    p_bnProcBuf     = (__m512i*) &bnProcBuf    [62976];
   p_bnProcBufRes    = (__m512i*) &bnProcBufRes   [62976];
            p_res = &p_bnProcBufRes[0];
            p_llrRes = (__m512i*) &llrRes  [22272];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[0 + i]);
}
            p_res = &p_bnProcBufRes[18];
            p_llrRes = (__m512i*) &llrRes  [22272];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[18 + i]);
}
            p_res = &p_bnProcBufRes[36];
            p_llrRes = (__m512i*) &llrRes  [22272];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[36 + i]);
}
            p_res = &p_bnProcBufRes[54];
            p_llrRes = (__m512i*) &llrRes  [22272];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[54 + i]);
}
            p_res = &p_bnProcBufRes[72];
            p_llrRes = (__m512i*) &llrRes  [22272];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[72 + i]);
}
            p_res = &p_bnProcBufRes[90];
            p_llrRes = (__m512i*) &llrRes  [22272];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[90 + i]);
}
            p_res = &p_bnProcBufRes[108];
            p_llrRes = (__m512i*) &llrRes  [22272];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[108 + i]);
}
            p_res = &p_bnProcBufRes[126];
            p_llrRes = (__m512i*) &llrRes  [22272];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[126 + i]);
}
            p_res = &p_bnProcBufRes[144];
            p_llrRes = (__m512i*) &llrRes  [22272];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[144 + i]);
}
            p_res = &p_bnProcBufRes[162];
            p_llrRes = (__m512i*) &llrRes  [22272];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[162 + i]);
}
            p_res = &p_bnProcBufRes[180];
            p_llrRes = (__m512i*) &llrRes  [22272];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[180 + i]);
}
// Process group with 12 CNs 
       M = (4*Z + 63)>>6;
    p_bnProcBuf     = (__m512i*) &bnProcBuf    [75648];
   p_bnProcBufRes    = (__m512i*) &bnProcBufRes   [75648];
            p_res = &p_bnProcBufRes[0];
            p_llrRes = (__m512i*) &llrRes  [23424];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[0 + i]);
}
            p_res = &p_bnProcBufRes[24];
            p_llrRes = (__m512i*) &llrRes  [23424];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[24 + i]);
}
            p_res = &p_bnProcBufRes[48];
            p_llrRes = (__m512i*) &llrRes  [23424];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[48 + i]);
}
            p_res = &p_bnProcBufRes[72];
            p_llrRes = (__m512i*) &llrRes  [23424];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[72 + i]);
}
            p_res = &p_bnProcBufRes[96];
            p_llrRes = (__m512i*) &llrRes  [23424];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[96 + i]);
}
            p_res = &p_bnProcBufRes[120];
            p_llrRes = (__m512i*) &llrRes  [23424];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[120 + i]);
}
            p_res = &p_bnProcBufRes[144];
            p_llrRes = (__m512i*) &llrRes  [23424];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[144 + i]);
}
            p_res = &p_bnProcBufRes[168];
            p_llrRes = (__m512i*) &llrRes  [23424];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[168 + i]);
}
            p_res = &p_bnProcBufRes[192];
            p_llrRes = (__m512i*) &llrRes  [23424];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[192 + i]);
}
            p_res = &p_bnProcBufRes[216];
            p_llrRes = (__m512i*) &llrRes  [23424];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[216 + i]);
}
            p_res = &p_bnProcBufRes[240];
            p_llrRes = (__m512i*) &llrRes  [23424];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[240 + i]);
}
            p_res = &p_bnProcBufRes[264];
            p_llrRes = (__m512i*) &llrRes  [23424];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[264 + i]);
}
// Process group with 13 CNs 
       M = (1*Z + 63)>>6;
    p_bnProcBuf     = (__m512i*) &bnProcBuf    [94080];
   p_bnProcBufRes    = (__m512i*) &bnProcBufRes   [94080];
            p_res = &p_bnProcBufRes[0];
            p_llrRes = (__m512i*) &llrRes  [24960];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[0 + i]);
}
            p_res = &p_bnProcBufRes[6];
            p_llrRes = (__m512i*) &llrRes  [24960];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[6 + i]);
}
            p_res = &p_bnProcBufRes[12];
            p_llrRes = (__m512i*) &llrRes  [24960];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[12 + i]);
}
            p_res = &p_bnProcBufRes[18];
            p_llrRes = (__m512i*) &llrRes  [24960];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[18 + i]);
}
            p_res = &p_bnProcBufRes[24];
            p_llrRes = (__m512i*) &llrRes  [24960];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[24 + i]);
}
            p_res = &p_bnProcBufRes[30];
            p_llrRes = (__m512i*) &llrRes  [24960];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[30 + i]);
}
            p_res = &p_bnProcBufRes[36];
            p_llrRes = (__m512i*) &llrRes  [24960];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[36 + i]);
}
            p_res = &p_bnProcBufRes[42];
            p_llrRes = (__m512i*) &llrRes  [24960];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[42 + i]);
}
            p_res = &p_bnProcBufRes[48];
            p_llrRes = (__m512i*) &llrRes  [24960];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[48 + i]);
}
            p_res = &p_bnProcBufRes[54];
            p_llrRes = (__m512i*) &llrRes  [24960];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[54 + i]);
}
            p_res = &p_bnProcBufRes[60];
            p_llrRes = (__m512i*) &llrRes  [24960];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[60 + i]);
}
            p_res = &p_bnProcBufRes[66];
            p_llrRes = (__m512i*) &llrRes  [24960];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[66 + i]);
}
            p_res = &p_bnProcBufRes[72];
            p_llrRes = (__m512i*) &llrRes  [24960];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[72 + i]);
}
// Process group with 14 CNs 
// Process group with 15 CNs 
// Process group with 16 CNs 
// Process group with 17 CNs 
// Process group with 18 CNs 
// Process group with 19 CNs 
// Process group with 20 CNs 
// Process group with 21 CNs 
// Process group with 22 CNs 
// Process group with <23 CNs 
// Process group with 24 CNs 
// Process group with 25 CNs 
// Process group with 26 CNs 
// Process group with 27 CNs 
// Process group with 28 CNs 
       M = (1*Z + 63)>>6;
    p_bnProcBuf     = (__m512i*) &bnProcBuf    [99072];
   p_bnProcBufRes    = (__m512i*) &bnProcBufRes   [99072];
            p_res = &p_bnProcBufRes[0];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[0 + i]);
}
            p_res = &p_bnProcBufRes[6];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[6 + i]);
}
            p_res = &p_bnProcBufRes[12];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[12 + i]);
}
            p_res = &p_bnProcBufRes[18];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[18 + i]);
}
            p_res = &p_bnProcBufRes[24];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[24 + i]);
}
            p_res = &p_bnProcBufRes[30];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[30 + i]);
}
            p_res = &p_bnProcBufRes[36];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[36 + i]);
}
            p_res = &p_bnProcBufRes[42];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[42 + i]);
}
            p_res = &p_bnProcBufRes[48];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[48 + i]);
}
            p_res = &p_bnProcBufRes[54];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[54 + i]);
}
            p_res = &p_bnProcBufRes[60];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[60 + i]);
}
            p_res = &p_bnProcBufRes[66];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[66 + i]);
}
            p_res = &p_bnProcBufRes[72];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[72 + i]);
}
            p_res = &p_bnProcBufRes[78];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[78 + i]);
}
            p_res = &p_bnProcBufRes[84];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[84 + i]);
}
            p_res = &p_bnProcBufRes[90];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[90 + i]);
}
            p_res = &p_bnProcBufRes[96];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[96 + i]);
}
            p_res = &p_bnProcBufRes[102];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[102 + i]);
}
            p_res = &p_bnProcBufRes[108];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[108 + i]);
}
            p_res = &p_bnProcBufRes[114];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[114 + i]);
}
            p_res = &p_bnProcBufRes[120];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[120 + i]);
}
            p_res = &p_bnProcBufRes[126];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[126 + i]);
}
            p_res = &p_bnProcBufRes[132];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[132 + i]);
}
            p_res = &p_bnProcBufRes[138];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[138 + i]);
}
            p_res = &p_bnProcBufRes[144];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[144 + i]);
}
            p_res = &p_bnProcBufRes[150];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[150 + i]);
}
            p_res = &p_bnProcBufRes[156];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[156 + i]);
}
            p_res = &p_bnProcBufRes[162];
            p_llrRes = (__m512i*) &llrRes  [25344];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[162 + i]);
}
// Process group with 29 CNs 
// Process group with 30 CNs 
       M = (1*Z + 63)>>6;
    p_bnProcBuf     = (__m512i*) &bnProcBuf    [109824];
   p_bnProcBufRes    = (__m512i*) &bnProcBufRes   [109824];
            p_res = &p_bnProcBufRes[0];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[0 + i]);
}
            p_res = &p_bnProcBufRes[6];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[6 + i]);
}
            p_res = &p_bnProcBufRes[12];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[12 + i]);
}
            p_res = &p_bnProcBufRes[18];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[18 + i]);
}
            p_res = &p_bnProcBufRes[24];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[24 + i]);
}
            p_res = &p_bnProcBufRes[30];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[30 + i]);
}
            p_res = &p_bnProcBufRes[36];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[36 + i]);
}
            p_res = &p_bnProcBufRes[42];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[42 + i]);
}
            p_res = &p_bnProcBufRes[48];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[48 + i]);
}
            p_res = &p_bnProcBufRes[54];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[54 + i]);
}
            p_res = &p_bnProcBufRes[60];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[60 + i]);
}
            p_res = &p_bnProcBufRes[66];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[66 + i]);
}
            p_res = &p_bnProcBufRes[72];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[72 + i]);
}
            p_res = &p_bnProcBufRes[78];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[78 + i]);
}
            p_res = &p_bnProcBufRes[84];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[84 + i]);
}
            p_res = &p_bnProcBufRes[90];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[90 + i]);
}
            p_res = &p_bnProcBufRes[96];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[96 + i]);
}
            p_res = &p_bnProcBufRes[102];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[102 + i]);
}
            p_res = &p_bnProcBufRes[108];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[108 + i]);
}
            p_res = &p_bnProcBufRes[114];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[114 + i]);
}
            p_res = &p_bnProcBufRes[120];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[120 + i]);
}
            p_res = &p_bnProcBufRes[126];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[126 + i]);
}
            p_res = &p_bnProcBufRes[132];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[132 + i]);
}
            p_res = &p_bnProcBufRes[138];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[138 + i]);
}
            p_res = &p_bnProcBufRes[144];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[144 + i]);
}
            p_res = &p_bnProcBufRes[150];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[150 + i]);
}
            p_res = &p_bnProcBufRes[156];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[156 + i]);
}
            p_res = &p_bnProcBufRes[162];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[162 + i]);
}
            p_res = &p_bnProcBufRes[168];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[168 + i]);
}
            p_res = &p_bnProcBufRes[174];
            p_llrRes = (__m512i*) &llrRes  [25728];
            for (i=0;i<M;i++) {
            p_res[i] = _mm512_subs_epi8(p_llrRes[i], p_bnProcBuf[174 + i]);
}
}
