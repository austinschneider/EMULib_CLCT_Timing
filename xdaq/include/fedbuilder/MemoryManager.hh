#ifndef __fedbuilder_MemoryManager_h_
#define __fedbuilder_MemoryManager_h_

#include <string>
#include <list>

#include "xdaq/Application.h"
#include "toolbox/mem/Pool.h"
#include "fedbuilder/LendBuffer.hh"
#include "fedbuilder/FedbuilderExceptions.hh"

namespace fedbuilder
{
    class MemoryManager {

    public:

        MemoryManager( xdaq::Application *appl,
                       std::string poolName )
	  throw( xcept::Exception );
        
        const std::list< LendBuffer_t * > &
        initialize( unsigned int blockSize,
                    unsigned int maxInputBlocks,
                    unsigned int highThreshold,
                    unsigned int reservedSize,
                    const std::list< void* > &userPtrs )
	  throw( fedbuilder::exception::SoftwareProblem,
                 fedbuilder::exception::MemorypoolInitializationError );

        const std::list< LendBuffer_t * > &simpleBlocks(int blocks)
            throw( xcept::Exception ); 

        void blockReturn( LendBuffer_t* );

        void flushBlocks();

    private:
        
        LendBuffer_t *lendBlock() throw (xcept::Exception); 
            
        Logger logger_;

        toolbox::mem::Pool * pheapsPool_;
        unsigned int blockSize_;
        unsigned int maxAllowedBlocks_;
        unsigned int provideRequests_;
        unsigned int lended_;
        unsigned int reservedSize_;

        toolbox::rlist< LendBuffer_t* >  availableLendBuffers_; 
      unsigned int albcnt_;
        toolbox::rlist< LendBuffer_t* >  allLendBuffers_;

        std::list< LendBuffer_t * >    lendBufferList_;
    };
}

#endif /* __fedbuilder_MemoryManager_h_ */
