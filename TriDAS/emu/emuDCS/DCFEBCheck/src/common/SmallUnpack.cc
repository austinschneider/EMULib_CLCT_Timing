#include "emu/pc/SmallUnpack.h"

namespace emu{
  namespace pc{

SmallUnpack::SmallUnpack(){
  printf(" Instantiate SmallUnpack \n");
  dmbh=new DMBHead();
  tmb=new TMBData();
  for(int k=0;k<5;k++)cfeb[k]=new CFEBData(k);
}

SmallUnpack::~SmallUnpack(){
  printf(" destroy SmallUnpack \n");
  dmbh->~DMBHead();
  tmb->~TMBData();
  for(int k=0;k<5;k++)cfeb[k]->~CFEBData();
}


void SmallUnpack::getEvent(int tlength,short int *tdata,int nsample){
  //  printf(" entered getEvent \n");
  unsigned short keywd[6];
  keywd[0]=0x9000;keywd[1]=0xa000;keywd[2]=0xd000;keywd[3]=0x8000;keywd[4]=0xf000;keywd[5]=0xe000;
  NSAMPLE=nsample;
  printf(" SmallUnpack NSAMPLE %d \n",NSAMPLE);
  rawdata=tdata;
  length=tlength;
  int eof=0; 
  int itmp;
  int data;
  for(int i=0;i<5;i++)CFEBOffset[i]=-99;
  DMB1Head=-99;
  DMB2Head=-99;
  DMB1Tail=-99;
  DMB2Tail=-99;
  TMBHead=-99;
  TMBTail=-99;
  ALCTHead=-99;
  ALCTTail=-99;
  printf(" length %d \n",length);
  fflush(stdout);

  /* kludge to fix bens trailer offset */
  /* length=length+4;
  int shift=0;
  unsigned short int temp;
  unsigned short int temp2;
  for(int i=0;i<length;i++){
    //    printf(" kludge %d %04x %04x \n",i,rawdata[i]&0xf000,rawdata[i+1]&0xf000);  
    if(shift==1){
      temp2=rawdata[i+1];
      rawdata[i+1]=temp;
      temp=temp2;
    }
    if(shift==0&&((rawdata[i]&0xf000)==0x7000)&&((rawdata[i+1]&0xf000)==0xf000)){
      printf(" set shift %d \n",i);
      shift=1;
      temp=rawdata[i+1];
      rawdata[i+1]=0x7fff;
    }
    } */ 
  /* end kludge to fix bens trailder offset */
 
 for(int i=0;i<length/4;i++){
   //  printf(" %d %04x %04x %04x %04x \n",i,rawdata[i*4+0]&0xf000,rawdata[i*4+1]&0xf000,rawdata[i*4+2]&0xf000,rawdata[i*4+3]&0xf000);
     for(int j=0;j<6;j++){
       if(((rawdata[i*4+0]&0xf000)==keywd[j])&&((rawdata[i*4+1]&0xf000)==keywd[j])&&((rawdata[i*4+2]&0xf000)==keywd[j])&&((rawdata[i*4+3]&0xf000)==keywd[j])){
	 // printf(" entered i %d j %d \n",i,j);
       if(j==0)DMB1Head=i*4;
       if(j==1)DMB2Head=i*4;
       if(j==2){
	 // printf(" got a match i %d %04x \n",i,rawdata[i*4+0]&0xffff);
         if((rawdata[i*4+0]&0xffff)==0xdb0c)TMBHead=i*4;
         if((rawdata[i*4+0]&0xffff)==0xdb0a)ALCTHead=i*4;
         if((rawdata[i*4+0]&0xffff)==0xde0f){
	   //  printf(" found eof \n"); 
           if(TMBHead>0&&TMBTail<0)TMBTail=i*4;
           if(ALCTHead>0&&ALCTTail<0)ALCTTail=i*4;
         }
       }
       if(j==4)DMB1Tail=i*4;
       if(j==5){DMB2Tail=i*4;eof=1;}
     }
     }
     if(eof==1)goto GOTIT;
  }
 GOTIT:
 //printf(" DMB1Head %d \n",DMB1Head);
 //printf(" DMB2Head %d \n",DMB2Head);
 //printf(" DMB1Tail %d \n",DMB1Tail);
 //printf(" DMB2Tail %d \n",DMB2Tail);
 //printf(" TMBHead %d \n",TMBHead);
 //printf(" TMBTail %d \n",TMBTail);
 //printf(" ALCTHead %d \n",ALCTHead);
 //printf(" ALCTTail %d \n",ALCTTail); 
   dmbh->Fill(DMB1Head,rawdata);
  int offset=DMB2Head+4;
  if(TMBHead>0&&TMBTail>0){
    if(dmbh->nclct==0)printf(" TMB unpack problem \n");
    tmb->Fill(TMBHead,rawdata);
  }
  if(ALCTTail>0)offset=ALCTTail+4;
  if(TMBTail>0)offset=TMBTail+4;
  int FEBwrds=DMB1Tail-offset;
  if(dmbh->nfeb*NSAMPLE*100==FEBwrds){
    for(int j=0;j<5;j++){
      if(dmbh->use_cfeb[j]==1){
         CFEBOffset[j]=offset;
	 // printf(" %d CFEBOffset %d \n",j,offset);
         offset=offset+800;
	 // printf(" ******** CFEB NUMBER %d j %d \n",cfeb[j]->CFEB,j);
         fflush(stdout);
         cfeb[j]->Fill(CFEBOffset[j],rawdata,NSAMPLE);
      }
    }
  }else{
     printf(" Unpack mismatch %d %d \n",dmbh->nfeb*NSAMPLE*100,FEBwrds);
  }
  fflush(stdout);
}

}
}
