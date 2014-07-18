// -*- c++ -*-
/**
   This file is used two times: once included from a .hh file where
   the macros are defined such that they declare the variables (i.e.,
   that they exists) and once from a .cc file where the macros are
   defined such that they initialize the variables (i.e., call the
   corresponding constructors).
*/

//            Name           Offset    R/W
//                           (hex)     (0 = readonly, 1 = read/write)
MAKE_REGISTER(BRD_ID       , 0x00    , 0);
MAKE_REGISTER(FWARE_VER    , 0x04    , 0);
MAKE_REGISTER(TRIG_NUM     , 0x08    , 0);
MAKE_REGISTER(EVNCNT       , 0x10    , 0);
MAKE_REGISTER(ORBCNT       , 0x14    , 0);
MAKE_REGISTER(STRCNT       , 0x18    , 0);
MAKE_REGISTER(STATUS       , 0x1C    , 1);
MAKE_REGISTER(CONTROL      , 0x20    , 1);
MAKE_REGISTER(CNTRST       , 0x40    , 1);
MAKE_REGISTER(BGO_MAP      , 0x44    , 1);
MAKE_REGISTER(INSELECT     , 0x48    , 1);
MAKE_REGISTER(OUTSELECT    , 0x4C    , 1);
MAKE_REGISTER(QPLLCTRL     , 0x50    , 1);
MAKE_REGISTER(ORBOFFS      , 0x54    , 1);
MAKE_REGISTER(ORBOFFS2     , 0x58    , 1);
MAKE_REGISTER(VMEBGO       , 0x60    , 1);
MAKE_REGISTER(VMEDATS      , 0x64    , 1);
MAKE_REGISTER(VMEDATL      , 0x68    , 1);
MAKE_REGISTER(BDAT_CFG     , 0x6C    , 1);
MAKE_REGISTER(SLINK_STAT   , 0x80    , 0);
MAKE_REGISTER(SLINK_CONF   , 0x84    , 1);
MAKE_REGISTER(TTS_DELAY    , 0x88    , 1);
MAKE_REGISTER(TTS_FIFLG    , 0x8C    , 0);
MAKE_REGISTER(TTS_FIFO     , 0x90    , 0);
MAKE_REGISTER(TTS_MASK     , 0x98    , 1);

MAKE_REGISTER(BCH_IHB_OFS  , 0x00    , 1);
MAKE_REGISTER(BCH_PSC_OFS  , 0x04    , 1);
MAKE_REGISTER(BCH_POS_OFS  , 0x08    , 1);
MAKE_REGISTER(BCH_RMC_OFS  , 0x0C    , 0);


MAKE_REGISTER(CTG_IHB_OFS  , 0x00    , 1);
MAKE_REGISTER(CTG_IPSC_OFS , 0x04    , 1);
MAKE_REGISTER(CTG_PSC_OFS  , 0x08    , 1);
MAKE_REGISTER(CTG_POS_OFS  , 0x0C    , 1);
MAKE_REGISTER(CTG_PAS_OFS  , 0x10    , 1);
MAKE_REGISTER(CTG_TGV_OFS  , 0x14    , 1);

MAKE_RAM(STA_BCH           , 0x100   , 1            , 64);
MAKE_RAM(STA_CTG           , 0x200   , 1            , 24);
MAKE_RAM(STA_CBG           , 0x260   , 1            , 40);

MAKE_REGISTER(TRR_CANC     , 0x300   , 0);

MAKE_RAM(TRR_nT            , 0x304   , 1            , 9);
MAKE_RAM(StartTrigDPRAM    , 0x1000  , 1            , 1024);
MAKE_RAM(StartBDPRAM       , 0x20000 , 1            , 32768);
