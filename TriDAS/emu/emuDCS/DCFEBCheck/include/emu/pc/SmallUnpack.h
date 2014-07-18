#ifndef _SmallUnpack_h_
#define _SmallUnpack_h_

#include <stdio.h>
#include "emu/pc/DMBHead.h"
#include "emu/pc/CFEBData.h"
#include "emu/pc/TMBData.h"

namespace emu{
  namespace pc{

 class DMBHead;
 class CFEBData;
 class TMBData;

class SmallUnpack  
{
 public:
  SmallUnpack();
  ~SmallUnpack();
  void getEvent(int tlength,short int *data,int nsample);
  int length;
  short int *rawdata;
  int NSAMPLE;
  TMBData *tmb;
  DMBHead *dmbh;
  CFEBData *cfeb[5];
  int CFEBOffset[5];
  int tmbdatapresent(){int i=1;if(TMBHead==-99)i=0;return i;}
 private:
  int DMB1Head;
  int DMB2Head;
  int DMB1Tail;
  int DMB2Tail;
  int TMBHead;
  int TMBTail;
  int ALCTHead;
  int ALCTTail;
};

}
}

#endif

