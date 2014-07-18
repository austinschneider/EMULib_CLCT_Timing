#ifndef _ttc_ltc_LTCConfiguration_hh_
#define _ttc_ltc_LTCConfiguration_hh_


#include "ttc/utils/GenericTTCModuleConfiguration.hh"


namespace ttc
{

// forward declarations

class LTC;

// configuration keywords

const std::string WORD_QPLL = "QPLL";
const std::string WORD_QPLLEXTERNAL = "EXTERN";
const std::string WORD_QPLLINTERNAL = "INTERN";
const std::string WORD_QPLLRESET = "Reset=";
const std::string WORD_QPLLAUTORESTART = "AutoRestart=";
const std::string WORD_QPLLFREQBITS = "FreqBits=";
const std::string WORD_BXGAP = "BXGAP";
const std::string WORD_TRIGGERS = "TRIGGERS";
const std::string WORD_TRIGGERS_RAM = "RAM";
const std::string WORD_TRIGGERS_CYCLIC = "CYCLIC";
const std::string WORD_TRIGGER_DELAY = "TRIGGERDELAY";
const std::string WORD_TRIGGER_INTERVAL = "TRIGGER_INTERVAL";
const std::string WORD_TRIGGER_FREQUENCY = "TRIGGER_FREQUENCY_HZ";
const std::string WORD_TRIGGER_FREQUENCY_MODE = "MODE=";
const std::string WORD_CYCLICGEN_TRIGGER = "CYCLICTRIGGER";
const std::string WORD_CYCLICGEN_BGO = "CYCLICBGO";
const std::string WORD_CYCLICGEN_STARTBX = "STARTBX=";
const std::string WORD_CYCLICGEN_PRESCALE = "PRES=";
const std::string WORD_CYCLICGEN_POSTSCALE = "POST=";
const std::string WORD_CYCLICGEN_INITPRECALE = "INITWAIT=";
const std::string WORD_CYCLICGEN_PAUSE = "PAUSE=";
const std::string WORD_CYCLICGEN_REPETITIVE = "REPETITIVE=";
const std::string WORD_CYCLICGEN_PERMANENT = "PERMANENT=";
const std::string WORD_CYCLICGEN_CHANNEL = "CH=";
const std::string WORD_VMEBX = "VMEBGOBX";
const std::string WORD_TRIGRULE = "TRIGGERRULE";
const std::string WORD_TRIGTICKET = "L1ATICKET";
const std::string WORD_TTS_ENABLE = "ENABLETTS";
const std::string WORD_TTS_WARNINT = "WARNING_INTERVAL";
const std::string WORD_MONITORING = "MONITORING";
const std::string WORD_MONITORING_INTERVAL = "INTERVAL=";
const std::string WORD_BSTVME = "VMEGPSTIME";
const std::string WORD_SLINKBACKPRESSURE = "IGNORESLINKBACKPRESSURE";
const std::string WORD_TRIGGERNAME = "HWTRIGGERNAME";
const std::string WORD_RUNLOG = "RUNLOG";
const std::string WORD_FIFODUMP = "SPYFIFODUMP";

//! A class to hold the LTC configuration info.
class LTCConfiguration : public GenericTTCModuleConfiguration
{

public:

  LTCConfiguration(ttc::LTC &_ltc);

  /**
   * Configures the LTC with the given stream.
   * If a BX conflict is detected, a warning will be logged after the fact.
   */
  void Configure(std::istream &in);

protected:

  virtual void registerConfigurationCommands();

  LTC &ltc;

  std::vector<float> extdelays;
};

}


#endif
