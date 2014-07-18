#ifndef _TMBData_h_
#define _TMBData_h_

#include <stdio.h>

namespace emu{
  namespace pc{

class TMBData  
{
 public:
  TMBData();
  ~TMBData();
 void  Fill(int offset,short int *data);
 int inuse;
 int ctbins; 
 int cncfebs;
 int rawtriad[5][6][32];
 int    triad[5][6][32][8]; /* board,layer,time bin,triad pair */
 int    chits[5][6][32];
 private:
};

}
}

#endif
