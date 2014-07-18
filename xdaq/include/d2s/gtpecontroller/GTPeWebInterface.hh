#ifndef GTPEWEBINTERFACE_H
#define GTPEWEBINTERFACE_H

/**
 *     @class GTPeWebInterface
 *
 *     @short Web Interface for XDAQ Web Application
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.2 $
 *     $Date: 2008/05/26 09:43:48 $
 *
 *
 **/

#include "d2s/gtpecontroller/GTPeParameters.hh"

// to repesent data as XDATA
#include "xdata/Vector.h"

// for XGI
#include "xgi/Input.h"
#include "xgi/Output.h"
#include "xgi/exception/Exception.h"

// for logging
#include "log4cplus/logger.h"

// base class
#include "xdaq/Object.h"

#include <vector>
#include <string>
#include <stdint.h>

namespace tts {
  class TTSState;
}

namespace xdaq {
  class Application;
}

namespace d2s {
  // to control the hardware
  class GTPeCrate;
  class GTPeMonitor;

  class GTPeWebInterface : xdaq::Object {

  public:
    GTPeWebInterface( xdaq::Application* owner,
		      GTPeParameters& config, 
		      xdata::UnsignedShort& daqPartitionId,
		      GTPeCrate* gtpecrate, 
		      GTPeMonitor* gtpeM,
		      GTPeMonitor* gtpePartitionM,
		      log4cplus::Logger& logger);
    ~GTPeWebInterface();

    /// display the default web page
    void displayDefaultWebPage(xgi::Input * in, xgi::Output * out, std::string const& statename ) 
      throw (xgi::exception::Exception);


  private:
    std::string stateWebTableEntry(tts::TTSState const& state, bool selected = true, bool masked=false) const;

    GTPeParameters& _config;
    xdata::UnsignedShort& _daqPartitionId;
    GTPeCrate* _gtpecrate;
    GTPeMonitor* _gtpeM;
    GTPeMonitor* _gtpePartitionM;
    log4cplus::Logger& _logger;
    bool _autoupdate;
    uint32_t _resyncCount;
  };


}
#endif
