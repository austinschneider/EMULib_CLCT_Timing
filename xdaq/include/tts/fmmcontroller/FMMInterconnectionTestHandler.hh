#ifndef FMMINTERCONNECTIONTESTHANDLER_H
#define FMMINTERCONNECTIONTESTHANDLER_H

/**
 *     @class FMMInterconnectionTestHandler
 *
 *     @short Interconnection test handler for a crate of FMMs
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:31 $
 *
 *
 **/

#include "tts/fmmcontroller/FMMParameters.hh"

//#include "tts/ttsbase/TTSState.hh"

// to repesent data as XDATA
#include "xdata/Vector.h"

// for logging
#include "log4cplus/logger.h"

#include "xoap/MessageReference.h"

namespace tts {

  // to control the hardware
  class FMMCrate;
  class FMMInterconnectionTestHandler {

  public:
    /// constructor
    FMMInterconnectionTestHandler( xdata::Vector<xdata::Bag<tts::FMMParameters> >& config, 
				   tts::FMMCrate* fmmcrate,
				   log4cplus::Logger& logger);

    
    ~FMMInterconnectionTestHandler();

    /// read the current input states
    xoap::MessageReference  readInputStates(xoap::MessageReference msg) 
      throw (xoap::exception::Exception);

    /// reset the history memory
    xoap::MessageReference  resetHistory(xoap::MessageReference msg) 
      throw (xoap::exception::Exception);

    /// read the current input states
    xoap::MessageReference  checkInputSequence(xoap::MessageReference msg) 
      throw (xoap::exception::Exception);
  private:
    xdata::Vector<xdata::Bag<tts::FMMParameters> >& _config;
    tts::FMMCrate* _fmmcrate;
    log4cplus::Logger& _logger;
  };

}
#endif
