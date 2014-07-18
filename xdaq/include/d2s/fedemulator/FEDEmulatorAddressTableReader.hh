#ifndef __FEDEmulatorAddressTableReader
#define __FEDEmulatorAddressTableReader

#include <string>

#include "hal/PCIAddressTableDynamicReader.hh"

namespace d2s {

/**
*
*
*     @short A reader which generated the VME64x configuration space
*
*            This class is a hardcoded implementation of the address-
*            items of the VME64x specification.
*
*       @see
*    @author Christoph Schwick
* $Revision: 1.1 $
*     $Date: 2007/04/27 18:05:48 $
*
*
**/

class FEDEmulatorAddressTableReader : public HAL::PCIAddressTableDynamicReader {

public:
  FEDEmulatorAddressTableReader();
};

} /* namespace d2s */

#endif /* __FEDEmulatorAddressTableReader */
