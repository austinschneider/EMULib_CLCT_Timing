#ifndef _GTPEHARDCODEDADDRESSTABLEREADER_H
#define _GTPEHARDCODEDADDRESSTABLEREADER_H

/**
 *     @class GTPeHardcodedAddressTableReader
 *
 *     @short a hard-coded address table for the GTPe
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 08:02:33 $
 *
 *
 **/

#include "hal/PCIAddressTableDynamicReader.hh"

namespace d2s {
  
  class GTPeHardcodedAddressTableReader : public HAL::PCIAddressTableDynamicReader {

  public:
    GTPeHardcodedAddressTableReader();
  };

}


#endif
