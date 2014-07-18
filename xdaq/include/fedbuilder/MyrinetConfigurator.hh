#ifndef _MyrinetConfigurator_hh_
#define _MyrinetConfigurator_hh_

#include <stdint.h>
#include <string>

#include "myrfb_api.h"
#include "FEDBuilderConfigReaderInterface.hh"
#include "xdaq/Application.h"
#include "toolbox/fsm/FiniteStateMachine.h"
#include "fedbuilder/FedbuilderExceptions.hh"

// some error codes
#define OK 0
#define NoValidConfiguraionRead -1
#define MYRFB_MAX_CHARS 100

namespace fedbuilder 
{  
    class MyrinetConfigurator
    {

    public:
    
        MyrinetConfigurator( xdaq::Application *appl );
        MyrinetConfigurator( Logger &logger );

        /**
         * Checks the api version and opens the myrinet driver.
         */
        int32_t openMyrinetByUnit( int32_t unitNumber )
            throw (fedbuilder::exception::MyrinetOpenError);
 
        int32_t openMyrinetBySlot( int32_t slotNumber,
                                   myrfb_unit_t **myrinetUnitPtr )
            throw (fedbuilder::exception::MyrinetOpenError);


        int32_t close( )
            throw ( fedbuilder::exception::MyrinetCloseError );

        bool isOpen() { return myrfb_unit_ != NULL; };

        /**
         * Read in the configuration from the configurationReader.
         * This function can be called more than one time if desired.
         * The unit must be given to the reader since in general the
         * reader filters out the relevant configurationparameters
         * for the specific myrinet card. This is done by using the 
         * myrfb library which in turn reads another configuration 
         * file which defines the hardware layout of the Fedbuilder.
         * This second configuration file is located in "/etc". 
         */
        int32_t readConfiguration( FEDBuilderConfigReaderInterface &reader )
            throw( fedbuilder::exception::MyrinetConfigurationReadError );


        void setFbiMask    ( uint32_t fbi_mask );
        void setFboMask    ( uint32_t fbo_mask );
        void setOptionMask ( uint32_t option_mask );
        void setDestinationTable( myrfb_dest_table_t destination_table ); //< in case you want to do sophisticated things
        int32_t  setRoundRobin(std::string &errorString);                                             //< this is the default


        /**
         * Some getter functions for debugging:
         */
        uint32_t getFbiMask()    { return fbi_mask_; };
        uint32_t getFboMask()    { return fbo_mask_; };
        uint32_t getOptionMask() { return option_mask_; };
        myrfb_dest_table_t getDestinationTable() { return destination_table_; };
        int32_t getMonitoringStructure( myrfb_fb_monitor_t &myrfb_mon ) throw( fedbuilder::exception::MyrinetError );
        int32_t getDiagnosisStructure( myrfb_diag_t &myrfb_diag ) throw( fedbuilder::exception::MyrinetError );
    

        /**
         * Creates a Fedbuilder configuration with information from the
         * configuration read in with the getConfiguration method and 
         * with the information contained in the parameters of the 
         */
        int32_t fillMyrinetConfig( uint32_t receive_block_size,
                                   myrfb_fb_config_t &myrfb_config )
            throw( fedbuilder::exception::MyrinetConfigurationError );

        /** 
	 * Fills the destination table in the fedbuilder according to relative weights given in the argument.
	 * Every entry in the array (32 entries long) corresponds to the relative weight this the associated
	 * slice will get. This allows to do "static loadbalancing" i.e. load slices differently.
	 **/ 
        int32_t fillDestinationTable( float weights[] ) 
	    throw (fedbuilder::exception::MyrinetConfigurationError);
  
        /**
         * Load the calculated configuration into myrfb and issue the
         * configure command.
         */
        int32_t configureMyrinet( myrfb_fb_config_t &myrfb_config )
            throw( fedbuilder::exception::MyrinetConfigureError );

        /**
         * Enable the myrinet driver.
         * This command includes the enable and the run command for the myrfb.
         */
        int32_t enableMyrinet() throw( fedbuilder::exception::MyrinetEnableError ); 

    
        /**
         * Retrieve the status of the driver.
         */
        int32_t getStatus( std::string &stateStr ) throw( fedbuilder::exception::MyrinetError );

        int32_t getStatusCode( int32_t &statusCode ) throw( fedbuilder::exception::MyrinetError );

        int32_t getNetAdr() { return myrfbo_netid_.net_adr; };

        /**
         * Set a delay before discarding a fragment.
         * This feature can be used to slow down the FBI if backpressure
         * should be investigated.
         */
        void setDiscardDelay( uint32_t myrDelay )
            throw( fedbuilder::exception::MyrinetSettingError );


        /**
         * Get the next block of the superfragment.
         * A function only relevant for the fbo.
         */
        int32_t getNextBlock( myrfb_handle_t **p_recv_handle )
            throw( xcept::Exception );

        /**
         * Post an empty block to the library so that it can be 
         * filled with superfragment data.
         * A function only relevant for the fbo.
         */
        int32_t postBlock( myrfb_handle_t* blockHandle )
            throw( fedbuilder::exception::MyrinetError );

        /**
         * Halt the myrinet driver.
         */
        int32_t haltMyrinet() throw( fedbuilder::exception::MyrinetHaltError );


    private:
        void init();
        int32_t checkAPI( std::string &errorString );
        std::string getMyrinetErrorString( myrfb_return_t rt, std::string prefix = "" );

        Logger logger_;
        uint32_t fbi_mask_;
        uint32_t fbo_mask_;
        uint32_t option_mask_;
    
        bool validConfiguration_;  //< indicates if a valid configuration has been read.

        myrfb_unit_t *myrfb_unit_;
        myrfb_uts_fedbld_config_t reader_conf_;
        myrfb_dest_table_t  destination_table_;
        myrfb_netid_t myrfbo_netid_;
    };
}

#endif 
