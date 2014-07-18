#ifndef _rubuilder_ru_SuperFragmentTracker_h_
#define _rubuilder_ru_SuperFragmentTracker_h_

#include <ostream>

namespace rubuilder { namespace ru { // namespace rubuilder::ru

class SuperFragmentTracker
{
public:

    /**
     * Constructor.
     */
    SuperFragmentTracker();

    /**
     * The types of the components of FED data.
     */
    enum FedComponent
    {
        FED_HEADER,
        FED_PAYLOAD,
        FED_TRAILER
    };

    /**
     * Gives the size and type a component of FED data.
     */
    struct FedComponentDescriptor
    {
        /**
         * The size of the FED data component in bytes.
         */
        unsigned int size;

        /**
         * The type of the FED data component.
         */
        FedComponent type;

        /**
         * The index of the FED to which the FED data component belongs.
         *
         * For a given super-fragment, FED indices range from 0 to
         * (nbFeds - 1).
         */
        unsigned int fedIndex;
    };

    /**
     * Starts a new super-fragment with the specified dimensions.
     */
    void startSuperFragment
    (
        const unsigned int fedPayloadSize,
        const unsigned int nbFeds
    );

    /**
     * Returns true if the end of the super-fragment has been reached.
     */
    bool reachedEndOfSuperFragment();

    /**
     * Returns the size and type of the next component.  If the component
     * cannot fit within the specified number of bytes available, then the
     * minimum size of the component is returned.
     */
    FedComponentDescriptor getNextComponent
    (
        const unsigned int nbBytesAvailable
    );

    /**
     * Moves the tracker to the next component.
     */
    void moveToNextComponent
    (
        const unsigned int nbBytesAvailable
    );


private:

    /**
     * The size of payload per FED in bytes.
     */
    unsigned int fedPayloadSize_;

    /**
     * The number of FEDs that supply data to make a single super-fragment.
     */
    unsigned int nbFeds_;

    /**
     * The index of the current FED.
     *
     * FED indices range from 0 to (nbFeds - 1).
     */
    unsigned int fedIndex_;

    /**
     * The type of the next super-fragment component.
     */
    FedComponent typeOfNextComponent_;

    /**
     * The number of FED payload bytes still remaining.
     */
    unsigned int remainingFedPayload_;
};

} } // namespace rubuilder::ru


/**
 * Prints the specified type of FED data component.
 */
std::ostream& operator<<
(
    std::ostream &s,
    rubuilder::ru::SuperFragmentTracker::FedComponent &c
);

#endif
