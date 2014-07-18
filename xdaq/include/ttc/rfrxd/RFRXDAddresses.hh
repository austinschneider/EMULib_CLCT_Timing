#ifndef _ttc_rfrxd_RFRXDAddresses_hh_
#define _ttc_rfrxd_RFRXDAddresses_hh_


#include "ttc/utils/Address.hh"

#include <stdint.h>


namespace ttc
{

#ifndef MAKE_REGISTER
#define MAKE_REGISTER(name, add, write) extern const Address name
#endif

#ifndef MAKE_RAM
#define MAKE_RAM(name, add, write, num) extern const Address name
#endif

#ifndef MAKE_SUBREG
#define MAKE_SUBREG(name, reg, offs, num, step) extern const Address name
#endif

namespace RFRXDAdd
{

// define the basic registers and ram
#include "ttc/rfrxd/RFRXDAddDefs.hh"

// define additional subregisters
MAKE_SUBREG(CH_FREQ_LOW, CH1_FREQ_LOW, 0x00, 3, 4);
MAKE_SUBREG(CH_FREQ_HIGH, CH1_FREQ_HIGH, 0x00, 3, 4);
MAKE_SUBREG(CH_REF, CH1_REF, 0x00, 3, 2);

}

#undef MAKE_REGISTER
#undef MAKE_RAM
#undef MAKE_SUBREG

}


#endif
