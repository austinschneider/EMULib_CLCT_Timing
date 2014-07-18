#ifndef _CMSDAQConfigHARDCODEDADDRESSTABLEREADER_H
#define _CMSDAQConfigHARDCODEDADDRESSTABLEREADER_H

/**
 *     @class CMSDAQConfigHardcodedAddressTableReader
 *
 *     @short a hard-coded address table for the CMSDAQConfig
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
  
  class CMSDAQConfigHardcodedAddressTableReader : public HAL::PCIAddressTableDynamicReader {

  public:
    CMSDAQConfigHardcodedAddressTableReader();
  };

}


#endif
