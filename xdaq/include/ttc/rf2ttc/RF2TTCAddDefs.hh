//--------------------------------------------------------------------
// File       : rf2ttcadddefs.dat
// Last change: 20111007
//
// Purpose:
// This file describes and defines all required RF2TTC hardware
// register addresses. It is based on the RF2TTC user manual V5.2
// (PH-ESS-14-07-2009).
// NOTE: The RF2TTC manual lives here:
//       http://ttc-upgrade.web.cern.ch/ttc-upgrade/New_system/RF2TTC_UM5_2.pdf
// NOTE: Anything marked `AM' is the VME address modifier.
// NOTE: `(A24, D32)' Means there are 24 address bits and 32 data
//       bits.
// NOTE: The reset bits are defined in RF2TTC.hh.
//--------------------------------------------------------------------

// -*- c++ -*-
/**
   This file is used two times: Once included from a .hh file where
   the macros are defined such that they declare the variables
   (i.e. that they exists) and once from a .cc file where the macros
   are defined such that they initialize the variables (i.e. call the
   corresponding constructors).
*/

//----------------------------------------

// Board identification read only registers
// (AM=0x09 (A32,D32)).
//             Name                       Offset    R/W
//                                        (hex)     (0 = readonly,
//                                                   1 = read/write)
MAKE_REGISTER(MANUFACTURER_ID        ,   0x00000,    0);
MAKE_REGISTER(BOARD_ID               ,   0x00004,    0);
MAKE_REGISTER(REVISION_ID            ,   0x00008,    0);
MAKE_REGISTER(PROGRAM_ID             ,   0x0000C,    0);

//----------------------------------------

// Reset registers: AM=0x09 (A32,D32).
// NOTE: To reset anything first set BSET, then (presumably after some
//       waiting period) set BCLEAR.
MAKE_REGISTER(BSET                          , 0x00010   ,1);
MAKE_REGISTER(BCLEAR                        , 0x00014   ,1);

//----------------------------------------

// 'Normal' Registers: AM=0x09 (A32,D32).
//
// Note that for some of them, the manual says that they're only
// writeable, we consider these registers as 'R/W' here.

//            Name                        Offset    R/W
//                                        (hex)     (0 = readonly,
//                                                   1 = read/write)

//---------- I2C registers ----------

// According to p. 20 of the manual these I2C registers require a
// special read procedure:

//   1) Read a dummy data word from the address of the TTC or Delay25
//      register that is to be read out.
//   2) Wait at least 2 ms.
//   3) Read the data value from the DELAY25_REG or TTCrx_REG.

MAKE_REGISTER(BC_DELAY25_BC1            , 0x7D000   ,1);
MAKE_REGISTER(BC_DELAY25_BC2            , 0x7D004   ,1);
MAKE_REGISTER(BC_DELAY25_BCREF          , 0x7D008   ,1);
MAKE_REGISTER(BC_DELAY25_BCMAIN         , 0x7D00C   ,1);
// NOTE: The BC_DELAY25_GCR should be set to 40 MHz operation: bits
//       zero and one should be set to zero (manual p. 21).
MAKE_REGISTER(BC_DELAY25_GCR            , 0x7D014   ,1);
MAKE_REGISTER(ORBIN_DELAY25_ORB1        , 0x7D020   ,1);
MAKE_REGISTER(ORBIN_DELAY25_ORB2        , 0x7D024   ,1);
MAKE_REGISTER(ORBIN_DELAY25_GCR         , 0x7D034   ,1);
MAKE_REGISTER(ORBOUT_DELAY25_ORB1       , 0x7D040   ,1);
MAKE_REGISTER(ORBOUT_DELAY25_ORB2       , 0x7D044   ,1);
MAKE_REGISTER(ORBOUT_DELAY25_ORBMAIN    , 0x7D048   ,1);
MAKE_REGISTER(ORBOUT_DELAY25_GCR        , 0x7D054   ,1);

MAKE_REGISTER(TTCRX_POINTER             , 0x7E000   ,1);
MAKE_REGISTER(TTCRX_DATA                , 0x7E004   ,1);

MAKE_REGISTER(DELAY25_REG               , 0x7D200   ,0);
MAKE_REGISTER(TTCRX_REG                 , 0x7E200   ,0);

//---------- End of I2C registers ----------

// From Markus' code, it looks like the following reset registers are writeable (but never used anywhere).
// They can be read using the DebugVME.exe tool though.
// MAKE_REGISTER(BOARD_RESET               , 0xFA38   ,1); // not in the doc
// MAKE_REGISTER(DELAY25_RESET             , 0xFA3C   ,1); // not in the doc
// MAKE_REGISTER(QPLL_RESET                , 0xFA40   ,1);

// The following registers are all 3-bit. Where the bit mapping
// corresponds to the three orbits:
//   bit 0 -> orbit 1
//   bit 1 -> orbit 2
//   bit 2 -> orbit main
MAKE_REGISTER(ORB_COUNTER_RESET         , 0x7FA44   ,1);
MAKE_REGISTER(PERIOD_COUNTER_RESET      , 0x7FA48   ,1);
MAKE_REGISTER(ORB_INT_RESET             , 0x7FA4C   ,1);
MAKE_REGISTER(PERIOD_COUNTER_ENABLE     , 0x7FA64   ,1);
MAKE_REGISTER(ORB_COUNTER_ENABLE        , 0x7FA68   ,1);
MAKE_REGISTER(ORB_INT_ENABLE            , 0x7FA6C   ,1);

//----------------------------------

MAKE_REGISTER(WORKING_MODE              , 0x7FA78   ,1);
MAKE_REGISTER(BEAM_NO_BEAM_DEF          , 0x7FA7C   ,1);
MAKE_REGISTER(BST_MACHINE_MODE          , 0x7FA9C   ,0);
MAKE_REGISTER(TTCRX_STATUS              , 0x7FAA0   ,0);

//----------------------------------

// NOTE: According to p. 13 of the manual the ORBX_INT_PERIOD_SET
// registers contain the period of the internally generated orbit
// signal in units of 25 ns. This means they should always be set to
// 0xDEC = 3564.

MAKE_REGISTER(ORBMAIN_PERIOD_FIFO_RD    , 0x7FAC0   ,0);
MAKE_REGISTER(ORBMAIN_PERIOD_FIFO_STATUS, 0x7FAC4   ,0);
MAKE_REGISTER(ORBMAIN_PERIOD_RD         , 0x7FAC8   ,0);
MAKE_REGISTER(ORBMAIN_COUNTER           , 0x7FACC   ,0);
MAKE_REGISTER(ORBMAIN_INT_PERIOD_COUNTER, 0x7FAD0   ,0);
MAKE_REGISTER(ORBMAIN_INT_PERIOD_SET    , 0x7FAD4   ,1);
MAKE_REGISTER(ORBMAIN_LENGTH            , 0x7FAD8   ,1);
MAKE_REGISTER(ORBMAIN_COARSE_DELAY      , 0x7FADC   ,1);
MAKE_REGISTER(ORBMAIN_POLARITY          , 0x7FAE0   ,1);
MAKE_REGISTER(ORBMAIN_NOBEAM_SELECT     , 0x7FAE4   ,1);
MAKE_REGISTER(ORBMAIN_BEAM_SELECT       , 0x7FAE8   ,1);
MAKE_REGISTER(ORBMAIN_MAN_SELECT        , 0x7FAEC   ,1);

//--------------------

MAKE_REGISTER(ORB2_DAC                  , 0x7FAFC   ,1);
MAKE_REGISTER(ORB2_PERIOD_FIFO_RD       , 0x7FB00   ,0);
MAKE_REGISTER(ORB2_PERIOD_FIFO_STATUS   , 0x7FB04   ,0);
MAKE_REGISTER(ORB2_PERIOD_RD            , 0x7FB08   ,0);
MAKE_REGISTER(ORB2_COUNTER              , 0x7FB0C   ,0);
MAKE_REGISTER(ORB2_INT_PERIOD_COUNTER   , 0x7FB10   ,0);
MAKE_REGISTER(ORB2_INT_PERIOD_SET       , 0x7FB14   ,1);
MAKE_REGISTER(ORB2_LENGTH               , 0x7FB18   ,1);
MAKE_REGISTER(ORB2_COARSE_DELAY         , 0x7FB1C   ,1);
MAKE_REGISTER(ORB2_POLARITY             , 0x7FB20   ,1);
MAKE_REGISTER(ORB2_NOBEAM_SELECT        , 0x7FB24   ,1);
MAKE_REGISTER(ORB2_BEAM_SELECT          , 0x7FB28   ,1);
MAKE_REGISTER(ORB2_MAN_SELECT           , 0x7FB2C   ,1);

//--------------------

MAKE_REGISTER(ORB1_DAC                  , 0x7FB3C   ,1);
MAKE_REGISTER(ORB1_PERIOD_FIFO_RD       , 0x7FB40   ,0);
MAKE_REGISTER(ORB1_PERIOD_FIFO_STATUS   , 0x7FB44   ,0);
MAKE_REGISTER(ORB1_PERIOD_RD            , 0x7FB48   ,0);
MAKE_REGISTER(ORB1_COUNTER              , 0x7FB4C   ,0);
MAKE_REGISTER(ORB1_INT_PERIOD_COUNTER   , 0x7FB50   ,0);
MAKE_REGISTER(ORB1_INT_PERIOD_SET       , 0x7FB54   ,1);
MAKE_REGISTER(ORB1_LENGTH               , 0x7FB58   ,1);
MAKE_REGISTER(ORB1_COARSE_DELAY         , 0x7FB5C   ,1);
MAKE_REGISTER(ORB1_POLARITY             , 0x7FB60   ,1);
MAKE_REGISTER(ORB1_NOBEAM_SELECT        , 0x7FB64   ,1);
MAKE_REGISTER(ORB1_BEAM_SELECT          , 0x7FB68   ,1);
MAKE_REGISTER(ORB1_MAN_SELECT           , 0x7FB6C   ,1);

//----------------------------------

MAKE_REGISTER(BCMAIN_QPLL_STATUS        , 0x7FB7C   ,0);
MAKE_REGISTER(BCMAIN_QPLL_MODE          , 0x7FB80   ,1);
MAKE_REGISTER(BCMAIN_NOBEAM_SELECT      , 0x7FB84   ,1);
MAKE_REGISTER(BCMAIN_BEAM_SELECT        , 0x7FB88   ,1);
MAKE_REGISTER(BCMAIN_MAN_SELECT         , 0x7FB8C   ,1);

//--------------------

MAKE_REGISTER(BCREF_QPLL_STATUS         , 0x7FB98   ,0);
MAKE_REGISTER(BCREF_DAQ                 , 0x7FB9C   ,1);
MAKE_REGISTER(BCREF_QPLL_MODE           , 0x7FBA0   ,1);
MAKE_REGISTER(BCREF_NOBEAM_SELECT       , 0x7FBA4   ,1);
MAKE_REGISTER(BCREF_BEAM_SELECT         , 0x7FBA8   ,1);
MAKE_REGISTER(BCREF_MAN_SELECT          , 0x7FBAC   ,1);

//--------------------

MAKE_REGISTER(BC2_QPLL_STATUS           , 0x7FBB8   ,0);
MAKE_REGISTER(BC2_DAQ                   , 0x7FBBC   ,1);
MAKE_REGISTER(BC2_QPLL_MODE             , 0x7FBC0   ,1);
MAKE_REGISTER(BC2_NOBEAM_SELECT         , 0x7FBC4   ,1);
MAKE_REGISTER(BC2_BEAM_SELECT           , 0x7FBC8   ,1);
MAKE_REGISTER(BC2_MAN_SELECT            , 0x7FBCC   ,1);

//--------------------

MAKE_REGISTER(BC1_QPLL_STATUS           , 0x7FBE8   ,0);
MAKE_REGISTER(BC1_DAQ                   , 0x7FBEC   ,1);
MAKE_REGISTER(BC1_QPLL_MODE             , 0x7FBF0   ,1);
MAKE_REGISTER(BC1_NOBEAM_SELECT         , 0x7FBF4   ,1);
MAKE_REGISTER(BC1_BEAM_SELECT           , 0x7FBF8   ,1);
MAKE_REGISTER(BC1_MAN_SELECT            , 0x7FBFC   ,1);

//--------------------------------------------------------------------
