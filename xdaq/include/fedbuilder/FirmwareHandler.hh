#include "hal/PCIDevice.hh"
#include <string>

#ifndef __FirmwareHandler
#define __FirmwareHandler

#define DAQ_FIRMWARE_TYPE     0xf020
#define FEDEMU_FIRMWARE_TYPE  0xf220
#define AUTOGEN_FIRMWARE_TYPE 0xf120
#define BRIDGE_FIRMWARE_TYPE  0xfb00

#define DAQ_FIRMWARE_MIN_VERSION      0x0089
#define FEDEMU_FIRMWARE_MIN_VERSION   0x0064
#define AUTOGEN_FIRMWARE_MIN_VERSION  0x0061
#define BRIDGE_FIRMWARE_MIN_VERSION   0x005c

#define FRL_DAQ_MODE 0
#define FRL_GENERATOR_MODE 1
#define FRL_EFED_MODE 2

namespace fedbuilder 
{

    class FirmwareHandler 
    {
    
    public:

        /**
         * Only in the constructor the access to the hardware is done.
         * This makes the life cycle of this object less critical since
         * the pointers to the PCIDevices may go out of scope before 
         * this object disapears.
         */
        FirmwareHandler( HAL::PCIDevice * frlCard,
                         HAL::PCIDevice * spyCard );

        bool checkFirmware( int mode, std::string &errorstr );
        uint32_t getFRLFirmwareVersion() const;
        uint32_t getBridgeFirmwareVersion() const;
        uint32_t getFRLFirmwareType() const;
        uint32_t getBridgeFirmwareType() const;

    private:
        uint32_t frlVersion_;
        uint32_t bridgeVersion_;
        uint32_t frlType_;
        uint32_t bridgeType_;
    };
  
}

#endif /* __FirmwareHandler */
