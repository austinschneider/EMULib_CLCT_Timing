#ifndef _interface_shared_GlobalEventNumber_icc_
#define _interface_shared_GlobalEventNumber_icc_

#include "interface/shared/GlobalEventNumber.h"


namespace evtn{
    
    unsigned int EVM_GTFE_BLOCK;    
    unsigned int EVM_FDL_NOBX;


    void evm_board_setformat(size_t size)
    {
      switch(size){
      case BST32_3BX:
	EVM_GTFE_BLOCK = EVM_GTFE_BLOCK_V0000;
	EVM_FDL_NOBX = 3;
	break;
      case BST32_5BX:
	EVM_GTFE_BLOCK = EVM_GTFE_BLOCK_V0000;
	EVM_FDL_NOBX = 5;
	break;
      case BST52_3BX:
	EVM_GTFE_BLOCK = EVM_GTFE_BLOCK_V0011;
	EVM_FDL_NOBX = 3;
	break;
      case BST52_5BX:
	EVM_GTFE_BLOCK = EVM_GTFE_BLOCK_V0011;
	EVM_FDL_NOBX = 5;
	break;
      default:
	EVM_GTFE_BLOCK = EVM_GTFE_BLOCK_V0000;
	EVM_FDL_NOBX = 3;	    
      }
    }
}

#endif // _interface_shared_GlobalEventNumber_icc_
