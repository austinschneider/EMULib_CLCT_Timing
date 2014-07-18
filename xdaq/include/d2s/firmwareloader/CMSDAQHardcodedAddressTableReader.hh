#ifndef _CMSDAQHARDCODEDADDRESSTABLEREADER_H
#define _CMSDAQHARDCODEDADDRESSTABLEREADER_H

/**
 *     @class CMSDAQHardcodedAddressTableReader
 *
 *     @short a hard-coded address table for the CMSDAQ
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 08:02:32 $
 *
 *
 **/

#include "hal/PCIAddressTableDynamicReader.hh"

namespace d2s {
  
  class CMSDAQHardcodedAddressTableReader : public HAL::PCIAddressTableDynamicReader {

  public:
    CMSDAQHardcodedAddressTableReader();
  };

}


#endif
