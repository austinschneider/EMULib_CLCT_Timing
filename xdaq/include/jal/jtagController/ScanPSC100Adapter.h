/**
*     @class ScanPSC100Adapter
*
*     @short Abstract base class for adapter for ScanPSC 100
*
*            An adapter for a ScanPSC100 provides a means of accessing the registers of 
*            a ScanPSC 100 chip (or a similar JATG controller). It is needed by the JTAGController  
*            class.
* 
*       @see ---
*    @author Hannes Sakulin
* $Revision: 1.1 $
*     $Date: 2007/03/27 07:59:07 $
*
*
**/


#ifndef jal_SCANPSC100ADAPTER_H
#define jal_SCANPSC100ADAPTER_H

#include "jal/jtagController/HardwareException.h"
#include "jal/jtagController/OutOfRangeException.h"

#include <stdint.h>

namespace jal {

  class ScanPSC100Adapter {
  public:
    ScanPSC100Adapter() {}; 
    virtual ~ScanPSC100Adapter() {};

    /// write a byte to a ScanPSC100 register
    /// @param offset is in the range (0..7)
    /// @param data is the data byte to write
    virtual void writePSC(uint8_t offset, uint8_t data)
      throw (jal::OutOfRangeException,
	     jal::HardwareException) = 0;

    /// write a number of bytes to a ScanPSC100 register
    /// @param offset is in the range (0..7)
    /// @param num_bytes is the number of data bytes to write
    /// @param data is the array of data bytes.
    virtual void writeBlockPSC(uint8_t offset, uint32_t num_bytes, const uint8_t* data)
      throw (jal::OutOfRangeException,
	     jal::HardwareException) = 0;

    /// read a byte from a ScanPSC100 register
    /// @param offset is in the range (0..7)
    virtual uint8_t readPSC (uint8_t offset)
      throw (jal::OutOfRangeException,
	     jal::HardwareException) = 0;

  };

}

#endif //jal_SCANPSC100ADAPTER_H
