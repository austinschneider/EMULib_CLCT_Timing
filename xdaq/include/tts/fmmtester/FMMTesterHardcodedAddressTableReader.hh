#ifndef _FMMTESTERHARDCODEDADDRESSTABLEREADER_H
#define _FMMTESTERHARDCODEDADDRESSTABLEREADER_H

/**
 *     @class FMMTesterHardcodedAddressTableReader
 *
 *     @short a hard-coded address table for the FMMTester
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:34 $
 *
 *
 **/

#include "hal/PCIAddressTableDynamicReader.hh"

namespace tts {
  
  class FMMTesterHardcodedAddressTableReader : public HAL::PCIAddressTableDynamicReader {

  public:
    FMMTesterHardcodedAddressTableReader();
  };

}


#endif
