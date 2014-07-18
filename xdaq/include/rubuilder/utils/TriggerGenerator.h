#ifndef _rubuilder_utils_TriggerGenerator_h_
#define _rubuilder_utils_TriggerGenerator_h_

#include "i2o/i2oDdmLib.h"
#include "toolbox/mem/MemoryPoolFactory.h"
#include "toolbox/mem/Pool.h"

#include "rubuilder/utils/Constants.h"
#include "rubuilder/utils/EventUtils.h"


namespace rubuilder { namespace utils { // namespace rubuilder::utils

/**
 * Generates dummy triggers.
 */
class TriggerGenerator
{
public:

    /**
     * Generates and returns a single dummy I2O_EVM_TRIGGER message.
     *
     * The FED payload size is in bytes and must be a multiple of 8 bytes.
     */
    toolbox::mem::Reference *generate
    (
        toolbox::mem::Pool              *pool,
        const I2O_TID                   initiatorAddress,
        const I2O_TID                   targetAddress,
        const uint32_t                  triggerSourceId,
        const uint32_t                  eventNumber,
        const size_t                    fedPayloadSize
    ) const;


    /**
     * Generates and returns a single I2O_EVM_TRIGGER message with fake
     * L1 trigger information.
     *
     * The level 1 trigger bits are defined by the patternScheme:
     * -2=allbits; -1=built-in patterns; [0,191]=set ONE specific bit; 256=L1Information struct
     */
    toolbox::mem::Reference *generate
    (
        toolbox::mem::Pool               *pool,
        const I2O_TID                    initiatorAddress,
        const I2O_TID                    targetAddress,
        const uint32_t                   triggerSourceId,
        const uint32_t                   eventNumber,
        const uint32_t                   bx,
        const uint32_t                   eventType,
        const uint32_t                   orbit,
        const uint32_t                   lumiSection,
        const int32_t                    patternScheme,
        rubuilder::utils::L1Information& pattern,
        const evtn::EvmRecordScheme      recordScheme = evtn::BST52_5BX
    ) const;

private:
    
    void fillPayload
    (
        char*                            ptr,
        const uint32_t                   eventNumber,
        const uint32_t                   eventType,
        const uint32_t                   bx,
        const uint32_t                   orbit,
        const uint32_t                   lumiSection,
        const int32_t                    patternScheme,
        rubuilder::utils::L1Information& pattern
    ) const;

    void updateCRC(char* fedPtr, const size_t& fedSize) const;

};

} } // namespace rubuilder::utils

#endif
