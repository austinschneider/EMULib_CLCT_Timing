#ifndef _rubuilder_ru_SuperFragmentGenerator_h_
#define _rubuilder_ru_SuperFragmentGenerator_h_

#include "rubuilder/ru/SuperFragmentTracker.h"
#include "i2o/i2oDdmLib.h"
#include "toolbox/mem/MemoryPoolFactory.h"
#include "toolbox/mem/Pool.h"
#include "toolbox/mem/Reference.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/Vector.h"

#include <stdint.h>


namespace rubuilder { namespace ru { // namespace rubuilder::ru

/**
 * Generates dummy super-fragments.
 */
class SuperFragmentGenerator
{
public:

    /**
     * Constructor.
     */
    SuperFragmentGenerator();

    /**
     * Returns true if the end of the super-fragment has been reached.
     */
    bool reachedEndOfSuperFragment();

    /**
     * Starts a new super-fragment with the specified dimensions and
     * characteristics.
     *
     * Please note that fedSourceIds is an array whose size must be equal to
     * nbFeds.
     */
    void startSuperFragment
    (
        const uint32_t fedPayloadSize,
        std::vector<uint32_t>* fedSourceIds,
        const I2O_TID targetAddress,
        const uint32_t eventNumber
    );

    /**
     * Fills the specified block of the specified size with super-fragment
     * data.
     *
     * This function sets the data size of the buffer reference, i.e. it calls
     * bufRef->setDataSize().
     */
    void fillBlock
    (
        toolbox::mem::Reference *bufRef,
        const uint32_t          size
    );


private:

    /**
     * Inserts the specified FED component starting at the specified memory
     * address.
     */
    void insertFedComponent
    (
        const ru::SuperFragmentTracker::FedComponentDescriptor component,
        char                                                   *startAddr
    );

    /**
     * Fills the RU builder and FRL headers of the specified block.
     *
     * Please note that i2oMessageSize is in bytes.
     */
    void fillRuAndFrlHeaders
    (
        char           *blockAddr,
        const uint32_t i2oMessageSize,
        const uint32_t nbFedBytesWritten,
        const bool     isLastBlockOfSuperFragment
    );

    /**
     * Throws an exception if the specified block size is not valid.
     */
    void checkBlockSize
    (
        const uint32_t size
    );

    /**
     * Tracks the position within the super-fragment currently under
     * construction.
     */
    SuperFragmentTracker superFragTracker_;

    /**
     * The size of a FED's payload in bytes.
     */
    uint32_t fedPayloadSize_;

    /**
     * FED source ids.
     */
    std::vector<uint32_t>* fedSourceIds_;

    /**
     * The I2O target address of each I2O message.
     *
     * This will most probably be the I2O address of a RU.
     */
    I2O_TID targetAddress_;

    /**
     * The event number of the event to which the super-fragment currently
     * under construction blongs to.
     */
    uint32_t eventNumber_;

    /**
     * The number of the current block.
     *
     * A super-fragment is transported over a network as a series of blocks.
     */
    uint32_t blockNb_;
};

} } // namespace rubuilder::ru

#endif
