#ifndef FMMWEBINTERFACE_H
#define FMMWEBINTERFACE_H

/**
 *     @class FMMWebInterface
 *
 *     @short Web Interface for XDAQ Web Application
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.3 $
 *     $Date: 2008/09/02 15:21:21 $
 *
 *
 **/

#include "tts/fmmcontroller/FMMParameters.hh"

#include "tts/ttsbase/TTSState.hh"

// to repesent data as XDATA
#include "xdata/Vector.h"

// for XGI
#include "xgi/Input.h"
#include "xgi/Output.h"
#include "xgi/exception/Exception.h"

// for logging
#include "log4cplus/logger.h"

#include <vector>
#include <string>
#include <stdint.h>

// base class
#include "xdaq/Object.h"

namespace xdaq {
  class Application;
}

namespace tts {

  // to control the hardware
  class FMMCrate;
  class FMMDeadTimeMonitor;

  class FMMWebInterface : xdaq::Object {

  public:
    FMMWebInterface( xdaq::Application* owner,
    		 xdata::Vector<xdata::Bag<tts::FMMParameters> >& config, 
		     tts::FMMCrate* fmmcrate,
		     std::map<std::string, tts::FMMDeadTimeMonitor*>& dtmons,		   
		     log4cplus::Logger& logger);
    ~FMMWebInterface();

    /// display the default web page
    void displayDefaultWebPage(xgi::Input * in, xgi::Output * out, std::string const& statename ) 
      throw (xgi::exception::Exception);


  private:
    std::string formatTableEntries(std::vector<std::string> entries, std::vector<tts::TTSState> states, uint32_t mask, bool in_config)
      throw (xgi::exception::Exception);

    std::string formatStates(std::vector<tts::TTSState> states, uint32_t mask, bool in_config)
      throw (xgi::exception::Exception);

    std::string formatLabelsSubRow(std::string const& label,
				   std::string const& inputLabels,
				   std::string const& outputLabels,
				   std::vector<tts::TTSState> istates,
				   std::vector<tts::TTSState> ostates,
				   uint32_t mask, bool in_config,
				   uint32_t igeoslot)
      throw (xgi::exception::Exception);

    xdata::Vector<xdata::Bag<tts::FMMParameters> >& _config;
    tts::FMMCrate* _fmmcrate;
    std::map<std::string, tts::FMMDeadTimeMonitor*>& _dtmons;
  
    log4cplus::Logger& _logger;
    bool _autoupdate;
  };

}
#endif
