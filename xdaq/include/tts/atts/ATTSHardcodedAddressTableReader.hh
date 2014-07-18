#ifndef _ATTSHARDCODEDADDRESSTABLEREADER_H
#define _ATTSHARDCODEDADDRESSTABLEREADER_H

/**
 *     @class ATTSHardcodedAddressTableReader
 *
 *     @short a hard-coded address table for the ATTS Interface Card
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:24 $
 *
 *
 **/

#include "hal/PCIAddressTableDynamicReader.hh"

namespace tts {
  
  class ATTSHardcodedAddressTableReader : public HAL::PCIAddressTableDynamicReader {

  public:
    ATTSHardcodedAddressTableReader();
  };

}


#endif
