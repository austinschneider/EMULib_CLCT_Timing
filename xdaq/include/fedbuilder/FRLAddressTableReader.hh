#ifndef __FRLAddressTableReader
#define __FRLAddressTableReader

#include <string>

#include "hal/PCIAddressTableDynamicReader.hh"

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
 * $Revision: 1.3 $
 *     $Date: 2008/11/27 17:01:32 $
 *
 *
 **/

namespace fedbuilder {

    class FRLAddressTableReader : public HAL::PCIAddressTableDynamicReader {

    public:
        FRLAddressTableReader();
    };

} /* namespace fedbuilder */

#endif /* __FRLAddressTableReader */
