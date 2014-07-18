#ifndef _rubuilder_utils_DumpUtility_h_
#define _rubuilder_utils_DumpUtility_h_

#include "toolbox/mem/Reference.h"

#include <iostream>


namespace rubuilder { namespace utils { // namespace rubuilder::utils

class DumpUtility
{
public:

    static void dump
    (
        std::ostream            &s,
        toolbox::mem::Reference *head
    );


private:

    static void dumpBlock
    (
        std::ostream            &s,
        toolbox::mem::Reference *bufRef,
        const uint32_t          bufferCnt
    );

    static void dumpBlockData
    (
        std::ostream &s,
        void         *data,
        int          len
    );

}; // class DumpUtility

} } // namespace rubuilder::utils

#endif
