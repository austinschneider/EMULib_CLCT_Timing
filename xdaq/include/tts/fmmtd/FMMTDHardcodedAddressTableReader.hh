#ifndef _FMMTDHARDCODEDADDRESSTABLEREADER_H
#define _FMMTDHARDCODEDADDRESSTABLEREADER_H

/**
 *     @class FMMTDHardcodedAddressTableReader
 *
 *     @short a hard-coded address table for the FMMTD
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:32 $
 *
 *
 **/

#include "hal/PCIAddressTableDynamicReader.hh"

namespace tts {
  
  class FMMTDHardcodedAddressTableReader : public HAL::PCIAddressTableDynamicReader {

  public:
    FMMTDHardcodedAddressTableReader();
  };

}


#endif
