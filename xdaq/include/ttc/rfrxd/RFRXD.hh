#ifndef _ttc_rfrxd_RFRXD_hh_
#define _ttc_rfrxd_RFRXD_hh_


#include <iostream>

#include "ttc/utils/GenericTTCModule.hh"
#include "ttc/utils/VME64xPNP.hh"
#include "ttc/rfrxd/RFRXDAddresses.hh"

namespace HAL
{
class VMEBusAdapterInterface;
}

namespace ttc
{

//! Represents an TTCci card, and all the operations that may be performed on it.
class RFRXD : public GenericTTCModule
{

public:

  static const unsigned FIRST_CHANNEL = 1;

  static const unsigned LAST_CHANNEL = 3;

  static const unsigned long FREQ_COUNTER_MAX_VALUE = 0xFFFFFFFFL;

  //! Clock signals (0.5-400 MHz).
  static const unsigned DAC_VALUE_CLOCK = 0x09;

  //! 'Pulse' signals.
  static const unsigned DAC_VALUE_PULSE = 0xA0;

  /**
   * Value which should work with 'any' signal which is however not optimal
   * (not there any more in new register description ?)
   */
  static const unsigned DAC_VALUE_GENERAL = 0x0A;

  //! There is also a minimum value. Below this one just measures the frequency of the noise.
  static const unsigned DAC_VALUE_MIN = 0x05;

  //! The maximum value is just determined by the width of the DAC.
  static const unsigned DAC_VALUE_MAX = 0xFF;

  static bool isValidDacValue(unsigned dac_value);

public:

  /**
   * constructor:
   * @param bus a reference to a bus adapter to communicate with the RFRXD.
   */
  RFRXD(
      HAL::VMEBusAdapterInterface& bus,
      int location);

  //! return firmware version (YYYYMMDD as a decimal number) as a string
  virtual std::string firmwareVersionString();

  uint32_t GetBoardID() const;

  uint32_t GetEdaID() const;

  /**
   * Note that the corresponding register only has meaningful
   * values if an OCP diode is installed. Otherwise, do not use this function.
   * @param channel goes from FIRST_CHANNEL to LAST_CHANNEL
   */
  bool SignalPresentOCP(unsigned channel);

  /**
   * This can be used for other diodes: This simply checks whether
   * the frequency counter on the corresponding channel has reached
   * its maximum value (trying to measure the period of the incoming signal)
   */
  bool SignalPresent(unsigned channel);

  unsigned long GetFrequencyCounterRawValue(unsigned channel);

  double ConvertRawFrequencyMeasurementToMHz(double raw_value);

  double ConvertRawFrequencyMeasurementToKHZ(double raw_value);

  /**
   * Returns the converted value (in kHz) for the given channel.
   * Conversion is done according to the formual given in the RFRXD user manual.
   */
  double GetMeasuredFrequencyInKHZ(
      unsigned channel,
      double *lower_bound = NULL,
      double *upper_bound = NULL);

  double GetMeasuredFrequencyLowerBoundInKHZ(unsigned long raw_value);

  double GetMeasuredFrequencyUpperBoundInKHZ(unsigned long raw_value);

  void PrintFrequencies(std::ostream &out = std::cout);

  //! Obtain the DAC threshold value from the hardware from the specified channel.
  unsigned GetDACvalue(unsigned channel);

  /*
   * These are recommended values for DAC Vref settings with
   * truelight optical receivers given on page eight of the simplified RFRXD user manual:
   * http://ttc-upgrade.web.cern.ch/ttc-upgrade/New_system/RF_Rx_D_simplified_user_manual_2008.pdf
   *
   * NOTE: There is a discrepancy between the recommended DAC values
   * reported in the simplified and (some versions of) the full user manuals.
   * The ones below are correct, as checked with Sophie Baron.
   */

  /**
   * Set the DAC Vref value used to set the voltage offset on one
   * of the comparator inputs after the laser diode.
   * @param dac_value can be in [5, 255].
   */
  void SetDACvalue(unsigned channel, unsigned dac_value);
};

}


#endif
