/**
 * this file is used two times: Once included from a .hh file where
 * the macros are defined such that they declare the variables
 * (i.e. that they exists) and once from a .cc file where the
 *  macros are defined such that they initialize the variables
 *  (i.e. call the corresponding constructors).
 */

#ifndef BOBR_BASE_ADDR_BLOCK_0 
#define BOBR_BASE_ADDR_BLOCK_0 0xB000
#endif

#ifndef BOBR_BASE_ADDR_BLOCK_1
#define BOBR_BASE_ADDR_BLOCK_1 0xB00000
#endif

#ifndef BOBR_BASE_ADDR_BLOCK_2
#define BOBR_BASE_ADDR_BLOCK_2 0xB10000
#endif

// difference between block 1 and block 2 base address
#ifndef BOBR_BASE_ADDR_DIFF_BLOCKS
#define BOBR_BASE_ADDR_DIFF_BLOCKS (BOBR_BASE_ADDR_BLOCK_2 - BOBR_BASE_ADDR_BLOCK_1)
#endif


// block 0
MAKE_BLOCK0_REGISTER(IDENTIFICATION,BOBR_BASE_ADDR_BLOCK_0 + 0x01    , 1);
MAKE_BLOCK0_REGISTER(GLOBAL_CONTROL,BOBR_BASE_ADDR_BLOCK_0 + 0x03    , 1);
MAKE_BLOCK0_REGISTER(GLOBAL_STATUS, BOBR_BASE_ADDR_BLOCK_0 + 0x05    , 1);

// block 1 and 2
//            Name           Offset    R/W 
//                           (hex)     (0 = readonly, 1 = read/write)
// MAKE_SUBREG(  CONTROL,       BOBR_BASE_ADDR_BLOCK_1, 0x10, 2, BOBR_BASE_ADDR_DIFF_BLOCKS); 
// note that this register is acually write only, don't try to read from it
MAKE_REGISTER(BASE_CONFIG_VERSION,     BOBR_BASE_ADDR_BLOCK_1 + 0x00    , 1);
MAKE_SUBREG  (CONFIG_VERSION,          BASE_CONFIG_VERSION,     0, 2, BOBR_BASE_ADDR_DIFF_BLOCKS); 

MAKE_REGISTER(BASE_CONTROL_AND_STATUS, BOBR_BASE_ADDR_BLOCK_1 + 0x10    , 1);
MAKE_SUBREG  (CONTROL_AND_STATUS,      BASE_CONTROL_AND_STATUS, 0, 2, BOBR_BASE_ADDR_DIFF_BLOCKS); 

// the Main DP RAM for receiving messages
MAKE_RAM(MESSAGE_INPUT_BLOCK1, BOBR_BASE_ADDR_BLOCK_1 + 0x800, 1, 0x100);
MAKE_RAM(MESSAGE_INPUT_BLOCK2, BOBR_BASE_ADDR_BLOCK_2 + 0x800, 1, 0x100);
