#ifndef __fedbuilder_LendBuffer_hh_
#define __fedbuilder_LendBuffer_hh_

#include "myrfb.h"
#include "myrfb_api.h"
#include "toolbox/mem/Reference.h"

namespace fedbuilder
{
    typedef struct LendBuffer 
    {
        toolbox::mem::Reference* bufRef_p;
        bool                     lended;
        void*                    user_ptr;
        void*                    bufferAddr;
        void*                    payloadAddr;
        void*                    physicalPayloadAddr;
    } LendBuffer_t;
}

#endif
