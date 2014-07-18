#ifndef _ttc_ttcci_TTCciConfiguration_hh_
#define _ttc_ttcci_TTCciConfiguration_hh_


#include "ttc/utils/GenericTTCModuleConfiguration.hh"


namespace ttc
{

class TTCci;

// TTCci configuration key words
namespace TTCciConfigWords
{
const std::string WORD_CLOCKSOURCE = "CLOCK_SOURCE";
const std::string WORD_TRIGGERSOURCE = "TRIGGER_SOURCE";
const std::string WORD_BGOSOURCE = "BGO_SOURCE";
const std::string WORD_ORBITSOURCE = "ORBIT_SOURCE";
const std::string WORD_QPLLRESET = "QPLLReset=";
const std::string WORD_QPLLAUTORESTART = "QPLLAutoRestart=";
const std::string WORD_QPLLFREQBITS = "FreqBits=";
const std::string WORD_TRIGGER_INTERVAL = "TRIGGER_INTERVAL";
const std::string WORD_TRIGGER_FREQUENCY = "TRIGGER_FREQUENCY_HZ";
const std::string WORD_TRIGGER_FREQUENCY_MODE = "MODE=";
const std::string WORD_BGOCHANNEL_SETUP = "BGO_CHANNEL";
const std::string WORD_BGOCHANNEL_SETUP_L = "L=";
const std::string WORD_BGOCHANNEL_SETUP_MODE = "REPETITIVE=";
const std::string WORD_BGOCHANNEL_SETUP_DELAY1 = "DELAY1=";
const std::string WORD_BGOCHANNEL_SETUP_DELAY2 = "DELAY2=";
const std::string WORD_BGOCHANNEL_SETUP_PRESCALE = "PRESCALE=";
const std::string WORD_BGOCHANNEL_SETUP_INITPRESCALE = "STARTAFTER=";
const std::string WORD_BGOCHANNEL_SETUP_POSTSCALE = "POSTSCALE=";
const std::string WORD_BGOCHANNEL_DATA = "ADDBGODATA";
const std::string WORD_BGOCHANNEL_DATA_DATA = "DATA=";
const std::string WORD_BGOCHANNEL_DATA_MODE = "MODE=";
const std::string WORD_BGOCHANNEL_DATA_POSTSCALE = "POSTSCALE=";
const std::string WORD_SEQUENCE_ADDNEW = "ADDSEQUENCE";
const std::string WORD_SEQUENCE_BEGIN = "BEGINSEQUENCE";
const std::string WORD_SEQUENCE_END = "ENDSEQUENCE";
const std::string WORD_BDATA = "SET_BDATA";
const std::string WORD_BDATA_ENABLE = "ENABLE=";
const std::string WORD_BDATA_L = "MODE=";
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
const std::string WORD_TRIGRULE = "TRIGGERRULE";
const std::string WORD_EXTTRIG0DELAY = "EXTTRIG0DELAY";
const std::string WORD_EXTTRIG1DELAY = "EXTTRIG1DELAY";
}

//! A class representing the configuration of a TTCci
class TTCciConfiguration : public GenericTTCModuleConfiguration
{
public:

  //! Returns WORD_EXTTRIG0DELAY or WORD_EXTTRIG1DELAY depending on trig_num.
  static const std::string GetExtTrigDelayKeyWord(unsigned trig_num);

  TTCciConfiguration(ttc::TTCci &_ttcci);

  void Configure(std::istream &in);

protected:

  virtual void registerConfigurationCommands();

  //! Reference to managed TTCci
  TTCci &ttcci;

  std::vector<float> extdelays;
};

}


#endif
