#include "emu/pc/CFEBData.h"

namespace emu{
  namespace pc{

class SmallUnpack;

CFEBData::CFEBData(int icfeb){
  CFEB=icfeb; 
  inuse=0;
  passed_crc=0;
  //  printf(" CFEBData NSAMPLE %d \n",nsample);
}

void CFEBData::Fill(int offset,short int *data,int nsample){
  int bit13[6];
  int calcCRC;
  int ovr;
  int word99;
  NSAMPLE=nsample;
  inuse=1;
  for(int time=0;time<NSAMPLE;time++){
    for(int i=0;i<6;i++)bit13[i]=0x0000;
    calcCRC=0;
    for(int adc=0;adc<96;adc++){ 
       int adc2=adc+time*100+offset;
       calcCRC=(data[adc2]&0x1fff)^((data[adc2]&0x1fff)<<1)^(((calcCRC&0x7ffc)>>2)|((0x0003&calcCRC)<<13))^((calcCRC&0x7ffc)>>1);
       int mod=adc%6;
       int bit=adc/6;     
       rawadc[mod][bit][time]=data[adc2]&0x1fff;
       ovr=0;
       if((data[adc2]&0x4000)!=0)ovr=1;
       ovrlp[time]=ovr;
       //     printf(" %d %d %d %d %04x %04x \n",adc,adc2,mod,bit,data[adc2],bit13[mod]);
       if((data[adc2]&0x2000)!=0)bit13[mod]=(bit13[mod]|(0x0001<<bit));
    } 
    if(calcCRC!=data[96+time*100+offset]){printf(" CRC ERROR ! %04x %04x  \n",calcCRC,data[96+time*100+offset]);}else{passed_crc=1;}
    //     printf(" %d %04x \n",98+time*100+8,data[98+time*100+8]);
    word99=(data[98+time*100+offset]&0x0fc0)>>6;
    l1a[time]=word99;
    //   printf(" %d ",time);
    for(int i=0;i<6;i++){
      trg[i][time]=bit13[i]&0x00ff;
      blk[i][time]=(bit13[i]&0x0f00)>>8;
      phs[i][time]=(bit13[i]&0x1000)>>12; 
      //  printf("%04x ",bit13[i]);
    }
    //  printf("| %02d %02x %1d %03d %1d",blk[0][time],trg[0][time],phs[0][time],word99,ovr);printf("\n");
  }
  // reorder strip by greycode
  // int grycd[16]={0,1,3,2,6,7,5,4,12,13,15,14,10,11,9,8};
  int grycd[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};   // no greycode for dcfeb
  for(int pln=0;pln<6;pln++){
    for(int k=0;k<16;k++){
      for(int time=0;time<8;time++){
        adc[pln][grycd[k]][time]=rawadc[pln][k][time]&0x1fff;
      }
      float ped=(adc[pln][grycd[k]][0]+adc[pln][grycd[k]][1])/2.;
      //  for(int t=0;t<8;t++)printf(" %f",adc[pln][grycd[k]][t]);printf("\n");
      for(int time=0;time<8;time++){
        adc[pln][grycd[k]][time]=adc[pln][grycd[k]][time]-ped;
      }
      // for(int t=0;t<8;t++)printf(" %f",adc[pln][grycd[k]][t]);printf("\n");
    }
  }

  return;
}

CFEBData::~CFEBData(){
}

}
}
