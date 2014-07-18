// -*- c++ -*-
/** this file is used two times: Once included from a .hh file where
    the macros are defined such that they declare the variables
    (i.e. that they exists) and once from a .cc file where the
    macros are defined such that they initialize the variables
    (i.e. call the corresponding constructors).
*/

//            Name           Offset    R/W 
//                           (hex)     (0 = readonly, 1 = read/write)
MAKE_REGISTER(EDA_ID       , 0x24    , 0);
MAKE_REGISTER(SIG_DETEC    , 0x0C    , 0);
MAKE_REGISTER(CH1_REF      , 0x12    , 1);
MAKE_REGISTER(CH2_REF      , 0x14    , 1);
MAKE_REGISTER(CH3_REF      , 0x16    , 1);


MAKE_REGISTER(CH1_FREQ_LOW , 0x18    , 0);
MAKE_REGISTER(CH1_FREQ_HIGH, 0x1A    , 0);
MAKE_REGISTER(CH2_FREQ_LOW , 0x1C    , 0);
MAKE_REGISTER(CH2_FREQ_HIGH, 0x1E    , 0);
MAKE_REGISTER(CH3_FREQ_LOW , 0x20    , 0);
MAKE_REGISTER(CH3_FREQ_HIGH, 0x22    , 0);



MAKE_REGISTER(BOARD_ID,      0x3A    , 0);

// note that the higher value register has lower address (i.e.
// Motorola Endianness)
MAKE_REGISTER(FIRMWARE_VER_LO,      0xF2    , 0);
MAKE_REGISTER(FIRMWARE_VER_HI,      0xF0    , 0);
