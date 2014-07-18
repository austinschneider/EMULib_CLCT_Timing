/**
*     @class HALScanPSC100Adapter
*
*     @short Implementation of Adapter for ScanPSC 100 JTAG Controller using HAL
*
*            An adapter that provides access to the registers of a ScanPSC100
*            (or a similar JATG controller) using the Hardware Access Library (HAL).
*            It is used by the ScanPSC100JTAGController class.
*
*       @see ---
*    @author Hannes Sakulin
* $Revision: 1.1 $
*     $Date: 2007/03/27 07:59:07 $
*
*
**/

#ifndef jal_HALSCANPSC100ADAPTER_H
#define jal_HALSCANPSC100ADAPTER_H

#include "jal/jtagController/ScanPSC100Adapter.h"

#include <stdint.h>

namespace HAL {
  class HardwareDeviceInterface;
}

namespace jal {

  class HALScanPSC100Adapter : public ScanPSC100Adapter {
  public:
    /**
     * constructor 
     *
     * the constructor needs to be passed a reference to a HAL Hardware Device
     * through which the ScanPSC100 is accessed. The HardwareDevice has to exist 
     * as long as the HALScanPSC100Adapter. 
     *
     *
     * @param device       is the reference to the HAL HardwareDevice
     * @param pscbase_name is the symbolic name of the base address of the ScanPSC100
     *                     in the address table of the HAL Hardware Device.
     *                     This address table item has to be read/write!
     *                     This address abd the following 7 addresses have to be defined
     *                     in the HAL address table.
     *
     * @param address_shift is the number of bits by which the offset has to be left-shifted
     *                      for VME this is usually 1, since A0 is not used (ScanPSC-chip 
     *                      connected to lines A1, A2, A3)
     */
    HALScanPSC100Adapter(HAL::HardwareDeviceInterface& device, 
			 const char* pscbase_name, 
			 uint8_t address_shift=1);


    /// d-tor
    virtual ~HALScanPSC100Adapter();
   
    /// write a byte to a register of the ScanPSC100
    ///
    /// @param offset is the offset of the ScanPSC register (0..7)
    /// @param data is the data to write
    virtual void writePSC(uint8_t offset, uint8_t data)
      throw (jal::OutOfRangeException,
	     jal::HardwareException);

    /// write multiple bytes to a register of the ScanPSC100
    ///
    /// @param offset is the offset of the ScanPSC register (0..7)
    /// @param num_bytes is the number of bytes to write
    /// @param data is the data to write
    virtual void writeBlockPSC(uint8_t offset, uint32_t num_bytes, const uint8_t* data)
      throw (jal::OutOfRangeException,
	     jal::HardwareException);

    /// read a byte from a register of the ScanPSC100
    ///
    /// @param offset is the offset of the ScanPSC register (0..7)
    virtual uint8_t readPSC (uint8_t offset)
      throw (jal::OutOfRangeException,
	     jal::HardwareException);

  private:
    HAL::HardwareDeviceInterface& _device;
    const char* _pscbase_name;
    uint8_t _address_shift;
  };

}
#endif //jal_HALSCANPSC100ADAPTER_H
