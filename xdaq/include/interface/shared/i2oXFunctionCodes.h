/*
 * i2oXFunctionCodes.h
 *
 * mods:
 * 26-Sep-2007 S. Murray: Replaced integer types with those from stdint.h
 */

#ifndef _i2oXFunctionCodes_h_
#define _i2oXFunctionCodes_h_


/////////////////////////////////////////////////////////////
// External EVB I2O function codes                         //
/////////////////////////////////////////////////////////////

const uint16_t I2O_BU_ALLOCATE   = 0x0001;
const uint16_t I2O_BU_COLLECT    = 0x0002;
const uint16_t I2O_BU_DISCARD    = 0x0003;
const uint16_t I2O_EVM_TRIGGER   = 0x0004;
const uint16_t I2O_EVM_LUMISECTION = 0x0011;
const uint16_t I2O_FU_TAKE       = 0x0005;
const uint16_t I2O_RU_DATA_READY = 0x0006;
const uint16_t I2O_EVMRU_DATA_READY = 0x0006; // New name
const uint16_t I2O_TA_CREDIT     = 0x0007;


/////////////////////////////////////////////////////////////
// Internal EVB I2O function codes                         //
/////////////////////////////////////////////////////////////

const uint16_t I2O_EVM_ALLOCATE_CLEAR = 0x0008;
const uint16_t I2O_BU_CONFIRM         = 0x0009;
const uint16_t I2O_RU_READOUT         = 0x000a;
const uint16_t I2O_RU_SEND            = 0x000b;
const uint16_t I2O_BU_CACHE           = 0x000c;


/////////////////////////////////////////////////////////////
// External DFC I2O function codes                         //
/////////////////////////////////////////////////////////////

const uint16_t I2O_RUI_CREDIT       = 0x000d;


/////////////////////////////////////////////////////////////
// Interinal DFC I2O function codes                        //
/////////////////////////////////////////////////////////////

const uint16_t I2O_DFC_HIGH    = 0x000e;
const uint16_t I2O_DFC_LOW     = 0x000f;
const uint16_t I2O_DFC_DISABLE = 0x0010;


/////////////////////////////////////////////////////////////
// Filter farm I2O function codes                          //
/////////////////////////////////////////////////////////////

// Filter farm reserves 0x001a to 0x0020 //


#endif
