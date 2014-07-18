#ifndef _ttc_rf2ttc_RF2TTCStatusPrinter_h_
#define _ttc_rf2ttc_RF2TTCStatusPrinter_h_


#include "ttc/rf2ttc/RF2TTC.hh"

#include <iostream>
#include <string>


namespace ttc
{
//! class for printing verbose info on RF2TTC registers
class RF2TTCStatusPrinter
{

friend class RF2TTC;

// static
public:

  static const std::string UNUSED_BITS_NONZERO_WARNING;

  static std::string GetMachineModeName(uint32_t mode);

  /**
   * This returns the name of the state of a multiplexer in the
   * BC1, BC2 or BCREF channel (whether it's internal or external).
   */
  static std::string GetBCInputSelectionStateName(bool isExternal);

  /**
   * Similar to GetBCInputSelectionStateName(..) but for BCREF
   * (which can have four different switch positions).
   */
  static std::string GetBCMainInputSelectionStateName(RF2TTC::BCChannel channel);

  //! Converts a number of bunch crossing ticks into some more verbose information.
  static std::string ClockTicksVerboseInformation(unsigned num_ticks);

  static std::string VerboseInputDACStatusFromRegister(uint32_t reg_content);

// members
private:

  //! CTOR. Does not print anything by default.
  RF2TTCStatusPrinter(RF2TTC&_rf2ttc, std::ostream &_os);

  //! Defines format with which a register content is printed out.
  void PrintLine(const std::string &description, uint32_t register_content, const std::string &interpretation) const;

  void PrintSeparator();

  void PrintBCLinesInfo();

  void PrintOrbitLinesInfo();

  //! this is used twice: for ORB_COUNTER_ENABLE and ORB_INT_ENABLE.
  std::string VerboseOrbitEnableInfo(uint32_t reg_content);

  /**
   * Returns the name of the machine mode as defined in the LHCStatus class
   * (which has the definitions from the BST people).
   */
  void PrintAllDelay25Status();

  void Print();

  void PrintTTCrxStatus();

  /**
   * Returns a verbose description of the register contents
   * which must reflect the status of a delay25 signal path.
   */
  std::string VerboseDelay25Status(uint32_t reg_content);

  void PrintBCChainStatus(RF2TTC::BCChannel channel);

  /**
   * Prints which source (input or internal) is taken
   * in which operating mode for a given bunch clock signal path.
   */
  void PrintBCSelectStatus(RF2TTC::BCChannel channel);

  void PrintDelay25GCR(const std::string &name, const Address &reg);

  //! Reads the register and returns a verbose string.
  std::string VerboseInputDACStatus(RF2TTC::OrbitChannel channel) const;

  std::string VerboseInputDACStatus(RF2TTC::BCChannel channel) const;

  //! Returns description of status of the orbit period measurement fifo.
  std::string VerboseOrbitPeriodFifoStatus(RF2TTC::OrbitChannel channel);

  //! Prints information about one orbit signal chain.
  void PrintOrbitChainStatus(RF2TTC::OrbitChannel channel);

  void PrintAllDACStatus();

  /**
   * print which source (input or internal) is taken
   * in which operating mode for the Orbit switches (multiplexers).
   */
  void PrintOrbitSelectRegisters(RF2TTC::OrbitChannel channel) const;

  //! Prints the status of all source selector switches.
  void PrintAllSelectStatus();

  //! Prints the working mode for all the multiplexers.
  void PrintWorkingMode() const;

  /**
   * @param register_content if not NULL,
   * this is set to the register content (in case somebody wants to print it etc.)
   */
  std::string GetVerboseQPLLStatus(RF2TTC::BCChannel channel, uint32_t *register_content = NULL);

  std::string GetVerboseQPLLMode(RF2TTC::BCChannel channel, uint32_t *register_content = NULL);

  std::string GetVerboseLastOrbitLength(RF2TTC::OrbitChannel channel);

  std::string GetVerboseOrbitPeriodLength(RF2TTC::OrbitChannel channel);

  std::string GetVerboseOrbitSource(
      RF2TTC::OrbitChannel channel,
      RF2TTC::OperatingMode opmode,
      uint32_t *_content = NULL,
      bool *other_bits_nonzero = NULL) const;


  /**
   * Whether to print or not the warning about
   * unused (or undocumented) bits which are nonzero.
   */
  bool print_unused_bits_nonzero_warning;

  RF2TTC &rf2ttc;

  std::ostream &os;
};

}


#endif
