#ifndef _FMMHARDCODEDADDRESSTABLEREADER_H
#define _FMMHARDCODEDADDRESSTABLEREADER_H

/**
 *     @class FMMHardcodedAddressTableReader
 *
 *     @short a hard-coded address table for the FMM
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:27 $
 *
 *
 **/

#include "hal/PCIAddressTableDynamicReader.hh"

namespace tts {
  
  class FMMHardcodedAddressTableReader : public HAL::PCIAddressTableDynamicReader {

  public:
    FMMHardcodedAddressTableReader();
  };

}


#endif
