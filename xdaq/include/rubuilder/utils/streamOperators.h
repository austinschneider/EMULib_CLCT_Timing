#ifndef _rubuilder_utils_streamOperators_h_
#define _rubuilder_utils_streamOperators_h_

#include "interface/evb/i2oEVBMsgs.h"

#include <iostream>


std::ostream& operator<<
(
    std::ostream        &s,
    const EvtIdTrigPair &pair
);

std::ostream& operator<<
(
    std::ostream      &s,
    const RqstForFrag &rqst
);

std::ostream& operator<<
(
     std::ostream                &s,
     const EvtIdRqstAndOrRelease &rqstAndOrRelease
);

std::ostream& operator<<
(
    std::ostream      &s,
    EvtIdTrigPairsMsg *msg
);

std::ostream& operator<<
(
    std::ostream                       &s,
    I2O_EVENT_DATA_BLOCK_MESSAGE_FRAME *b
);

std::ostream& operator<<
(
    std::ostream               &s,
    EvtIdRqstsAndOrReleasesMsg *msg
);

std::ostream& operator<<
(
    std::ostream    &s,
    RqstForFragsMsg *msg
);

std::ostream& operator<<
(
    std::ostream                &s,
    I2O_TA_CREDIT_MESSAGE_FRAME *msg
);


#endif
