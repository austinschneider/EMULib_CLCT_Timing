#ifndef _CFEBData_h_
#define _CFEBData_h_

#include <stdio.h>

namespace emu{
namespace pc{

class CFEBData  
{
 public:
  CFEBData(int icfeb);
  ~CFEBData();
 void  Fill(int offset,short int *data,int nsample);
 int CFEB;
 int inuse;
 int rawadc[6][16][100];
 float adc[6][16][100];
 int blk[6][100];
 int trg[6][100];
 int phs[6][100];
 int l1a[100];
 int ovrlp[100];
 int passed_crc;
 int NSAMPLE;
 private:
};

}
}

#endif
