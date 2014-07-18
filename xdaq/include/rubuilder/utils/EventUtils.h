#ifndef _rubuilder_utils_EventUtils_h_
#define _rubuilder_utils_EventUtils_h_

#include "i2o/i2o.h"
#include "interface/evb/i2oEVBMsgs.h"
#include "interface/shared/GlobalEventNumber.h"
#include "rubuilder/utils/Constants.h"
#include "toolbox/mem/Reference.h"

#include "xdaq/Application.h"


namespace rubuilder { namespace utils { // namespace rubuilder::utils

/**
 * struct for lumi section and L1 trigger bit information
 */
struct L1Information
{
    bool isValid;
    char reason[100];
    unsigned int runnumber;
    unsigned int lsnumber;
    unsigned short eventtype;
    unsigned long long l1technical;
    unsigned long long l1decision_0_63;
    unsigned long long l1decision_64_127;

    L1Information();
    void reset();
    const L1Information& operator=(const L1Information&);
};


/**
 * Sets the L1 trigger bits to fake patterns using the patternScheme.
 * -2=allbits; -1=built-in patterns; [0,191]=set ONE specific bit; 256=do not modify
 */
void setFakeTriggerBits(int32_t patternScheme, L1Information&);

} } // namespace rubuilder::utils

#endif // _rubuilder_utils_EventUtils_h_
