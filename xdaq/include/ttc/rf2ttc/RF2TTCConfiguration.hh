#ifndef _ttc_rf2ttc_RF2TTCConfiguration_hh_
#define _ttc_rf2ttc_RF2TTCConfiguration_hh_


#include "ttc/utils/GenericTTCModuleConfiguration.hh"


namespace ttc
{

class RF2TTC;

// RF2TTC config keywords
namespace RF2TTCConfigWords
{
const std::string WORD_INPUTDAC = "INPUTDAC";
const std::string WORD_CHANNEL = "CHANNEL";
const std::string WORD_COUNTS = "COUNTS";

const std::string WORD_SOURCE = "SOURCE";
const std::string WORD_INTERNAL = "INTERNAL";
const std::string WORD_EXTERNAL = "EXTERNAL";

const std::string WORD_SIGNAL_SELECT = "SIGNAL_SELECT";
const std::string WORD_MODE = "MODE";

// operating modes
const std::string WORD_OPMODE_MANUAL = "MANUAL";
const std::string WORD_OPMODE_BEAM = "BEAM";
const std::string WORD_OPMODE_NOBEAM = "NOBEAM";

// delay25
const std::string WORD_DELAY25 = "DELAY25";
const std::string WORD_DELAY25_CHANNEL = "CHANNEL";
const std::string WORD_DELAY25_ENABLE = "ENABLE";
const std::string WORD_DELAY25_YES = "YES";
const std::string WORD_DELAY25_NO = "YES";
const std::string WORD_DELAY25_STEPS = "STEPS";
const std::string WORD_DELAY25_IN = "IN"; // for orbit input or output
const std::string WORD_DELAY25_OUT = "OUT"; // for orbit input or output

// QPLL
const std::string WORD_QPLLMODE = "QPLLMODE";
const std::string WORD_QPLLMODE_CHANNEL = "CHANNEL";
const std::string WORD_QPLLMODE_RELOCKMODE = "RELOCKMODE";
const std::string WORD_QPLLMODE_AUTO = "AUTO";
const std::string WORD_QPLLMODE_MANUAL = "MANUAL";

// working mode
const std::string WORD_WORKING_MODE = "WORKING_MODE";
const std::string WORD_WORKING_MODE_MODE = "MODE";
const std::string WORD_WORKING_MODE_MANUAL = "MANUAL";
const std::string WORD_WORKING_MODE_AUTO = "AUTO";
const std::string WORD_WORKING_MODE_CHANNEL = "CHANNEL";

// internal orbit
const std::string WORD_INTERNAL_ORBIT = "INTERNAL_ORBIT";
const std::string WORD_INTERNAL_ORBIT_ENABLE = "ENABLE";
const std::string WORD_INTERNAL_ORBIT_YES = "YES";
const std::string WORD_INTERNAL_ORBIT_NO = "NO";
const std::string WORD_INTERNAL_ORBIT_CHANNEL = "CHANNEL";
const std::string WORD_INTERNAL_ORBIT_PERIOD = "PERIOD";

// orbit coarse delay
const std::string WORD_ORBIT_COARSE_DELAY = "ORBIT_COARSE_DELAY";
const std::string WORD_ORBIT_COARSE_DELAY_CHANNEL = "CHANNEL";
const std::string WORD_ORBIT_COARSE_DELAY_NUMBX = "NUMBX";

// beam/nobeam definitions
const std::string WORD_BEAM_NO_BEAM_DEF = "BEAM_NO_BEAM_DEF";
const std::string WORD_BEAM_NO_BEAM_DEF_MODE = "MODE";
const std::string WORD_BEAM_NO_BEAM_DEF_CONFIG = "CONFIG";
const std::string WORD_BEAM_NO_BEAM_DEF_BEAM = "BEAM";
const std::string WORD_BEAM_NO_BEAM_DEF_NOBEAM = "NOBEAM";
}

//! Class representing the RF2TTC configuration.
class RF2TTCConfiguration : public GenericTTCModuleConfiguration
{
public:

  RF2TTCConfiguration(ttc::RF2TTC& _rf2ttc);

  virtual void Configure(std::istream& in);

protected:

  virtual void registerConfigurationCommands();

  //! reference to the RF2TTC object
  RF2TTC& rf2ttc;

};

}


#endif
