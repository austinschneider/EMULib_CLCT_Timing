#ifndef _ttc_rf2ttc_RF2TTCAddresses_hh_
#define _ttc_rf2ttc_RF2TTCAddresses_hh_


#include "ttc/utils/Address.hh"

#include <stdint.h>


namespace ttc
{

#ifndef MAKE_REGISTER
#define MAKE_REGISTER(name, add, write) extern const Address name
#endif

namespace RF2TTCAdd
{
// Define the basic registers and RAM.
#include "ttc/rf2ttc/RF2TTCAddDefs.hh"
}

#undef MAKE_REGISTER
#undef MAKE_RAM
#undef MAKE_SUBREG

}


#endif
