#ifndef _ttc_bobr_BOBRAddresses_hh_
#define _ttc_bobr_BOBRAddresses_hh_


#include "ttc/utils/Address.hh"
#include <stdint.h>

namespace ttc
{

#ifndef MAKE_REGISTER
#define MAKE_REGISTER(name, add, write) extern const Address name
#endif

// block 0 needs a different address mode
#ifndef MAKE_BLOCK0_REGISTER
#define MAKE_BLOCK0_REGISTER(name, add, write) extern const Address name
#endif

#ifndef MAKE_RAM
#define MAKE_RAM(name, add, write, num) extern const Address name
#endif

#ifndef MAKE_SUBREG
#define MAKE_SUBREG(name, reg, offs, num, step) extern const Address name
#endif


namespace BOBRAdd
{
// define the basic registers and ram
#include "ttc/bobr/BOBRAddDefs.hh"
}

#undef MAKE_REGISTER
#undef MAKE_RAM
#undef MAKE_SUBREG

}


#endif
