#ifndef _ttc_ltc_LTCAddresses_hh_
#define _ttc_ltc_LTCAddresses_hh_


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

#ifndef MAKE_REGCOPY
#define MAKE_REGCOPY(name, reg) extern const Address name
#endif


namespace LTCAdd
{

#include "ttc/ltc/LTCAddDefs.hh"

MAKE_SUBREG(CHIHB, STA_BCH, 0x00, 16, 16);
MAKE_SUBREG(CHPRESC, STA_BCH, 0x04, 16, 16);
MAKE_SUBREG(CHPOSTSC, STA_BCH, 0x08, 16, 16);
MAKE_SUBREG(CHRMC, STA_BCH, 0x0c, 16, 16);

MAKE_SUBREG(CTBG_INH, STA_CTG, 0x00, 14, 32);
MAKE_SUBREG(CTBG_IPRESC, STA_CTG, 0x04, 14, 32);
MAKE_SUBREG(CTBG_PRESC, STA_CTG, 0x08, 14, 32);
MAKE_SUBREG(CTBG_POSTSC, STA_CTG, 0x0c, 14, 32);
MAKE_SUBREG(CTBG_PAUSE, STA_CTG, 0x10, 14, 32);
MAKE_SUBREG(CTBG_TYPE, STA_CTG, 0x14, 14, 32);

}

#undef MAKE_ADDRESS

}


#endif
