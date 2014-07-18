#ifndef _ttc_rf2ttc_RF2TTC_hh_
#define _ttc_rf2ttc_RF2TTC_hh_


#include "ttc/utils/GenericTTCModule.hh"
#include "ttc/utils/Utils.hh"

#include "ttc/rf2ttc/RF2TTCAddresses.hh"

#include <vector>
#include <map>
#include <string>

#include <unistd.h>
#include <time.h>


namespace HAL
{
class VMEBusAdapterInterface;
}


namespace ttc
{

/**
 * Class representing and RF2TTC card (RF to TTC VMEbus Interface Card).
 * More info: http://ttc-upgrade.web.cern.ch/ttc-upgrade/New_system/RF2TTC_UM5_2.pdf
 */
class RF2TTC : public GenericTTCModule
{

// types

public:

  //! Sources of BC signals.
  enum BCChannel
  {
    BC_UNDEF = 0, BC1, BC2, BCREF, BCINTERNAL, BCMAIN
  };

  //! Sources and signal paths of orbit signals.
  enum OrbitChannel
  {
    ORBIT_UNDEF = 0, ORBIT1, ORBIT2, ORBIT_MAIN, ORBIT_INTERNAL
  };

  //! Operating modes.
  enum OperatingMode
  {
    OPMODE_UNDEF = 0, OPMODE_MANUAL = 1, OPMODE_BEAM = 2, OPMODE_NOBEAM = 3,
    // These are needed for 'for' loops.
    OPMODE_FIRST = OPMODE_MANUAL,
    OPMODE_LAST = OPMODE_NOBEAM
  };


// static

public:

  // Minimun/maximum values for the input DACs and Delay25 values.

  static unsigned const MIN_DAC_VALUE;
  static unsigned const MAX_DAC_VALUE;
  static unsigned const MIN_DELAY25_VALUE;
  static unsigned const MAX_DELAY25_VALUE;

  static const unsigned TTCRXREG_STATUS = 22;
  static const unsigned MAX_ORBIT_COARSE_DELAY = 4095;
  static const unsigned NUM_MACHINE_MODES = 32;

  //! converts BCChannel to string
  static std::string GetBCChannelName(BCChannel channel);

  //! converts BCChannel to short string used in configuration language
  static std::string GetShortBCChannelName(BCChannel channel);

  //! converts short BC channel string (case sensitive) to BCChannel (default: BC_UNDEF)
  static BCChannel ShortBCChannelNameToEnum(const std::string &name);

  static std::string GetOrbitChannelName(OrbitChannel channel);

  //! converts OrbitChannel to short string used in configuration language
  static std::string GetShortOrbitChannelName(OrbitChannel channel);

  //! converts short orbit channel name (case sensitive) to OrbitChannel enum (default: ORBIT_UNDEF)
  static OrbitChannel ShortOrbitChannelNameToEnum(const std::string &name);

  //! converts OperatingMode to string
  static std::string GetOpModeName(OperatingMode mode);

  //! converts OperatingMode to short string used in configuration language
  static std::string GetShortOpModeName(OperatingMode mode);

  static const Address& GetQPLLStatusRegister(BCChannel channel);

  static const std::vector<BCChannel>& GetAllBCOutputPaths();

  static const std::vector<OrbitChannel>& GetAllOrbitOutputPaths();

  static const std::vector<OrbitChannel>& GetAllOrbitInputPaths();

  static const std::vector<OperatingMode>& GetAllOperatingModes();

  static const Address& GetOrbitInputDelay25Register(OrbitChannel channel);

  static const Address& GetOrbitOutputDelay25Register(OrbitChannel channel);

  /**
   * Gets the Address of the delay25 register for the given OrbitChannel;
   * @param output_path determines whether we want to have the register for the orbit input or orbit output side.
   */
  static const Address& GetOrbitDelay25Register(OrbitChannel channel, bool output_path);

  static const Address& GetOrbitPeriodFifoStatusRegister(OrbitChannel channel);

  static const Address& GetOrbitPeriodReadRegister(OrbitChannel channel);

  static const Address& GetOrbitCounterRegister(OrbitChannel channel);

  static const Address& GetInternalOrbitPeriodCounterRegister(OrbitChannel channel);

  static const Address& GetInternalOrbitPeriodLengthRegister(OrbitChannel channel);

  static const Address& GetOrbitPulseLengthRegister(OrbitChannel channel);

  static const Address& GetOrbitCoarseDelayRegister(OrbitChannel channel);

  static const Address& GetOrbitPolarityRegister(OrbitChannel channel);

  static const Address& GetOrbitSelectRegister(OrbitChannel channel, OperatingMode opmode);

  static const std::vector<BCChannel>& GetPossibleBCMainSources();

  static const std::vector<OrbitChannel>& GetPossibleOrbitMainSources();

protected:

  // These are the reset bits for the QPLLs etc. (Source: p. 6 of then RF2TTC user manual v5.1.)

  static const uint32_t RESET_BIT_DELAY25 = 1 << 0;
  static const uint32_t RESET_BIT_QPLL_BC1 = 1 << 2;
  static const uint32_t RESET_BIT_QPLL_BC2 = 1 << 3;
  static const uint32_t RESET_BIT_QPLL_BCREF = 1 << 4;
  static const uint32_t RESET_BIT_QPLL_BCMAIN = 1 << 5;
  static const uint32_t RESET_BIT_TTCRX = 1 << 6;
  static const uint32_t RESET_BIT_BOARD = 1 << 7;

  //! One value to reset them all.
  static const uint32_t RESET_BIT_QPLL_ALL =
      RESET_BIT_QPLL_BC1 + RESET_BIT_QPLL_BC2 + RESET_BIT_QPLL_BCREF + RESET_BIT_QPLL_BCMAIN;

  static void SetOrbitBit(uint32_t &register_content, RF2TTC::OrbitChannel channel, bool set_bit);

  /**
   * Returns the bit which this channel corresponds to in the WORKING_MODE register.
   * This method is used by the reading and writing methods.
   */
  static uint32_t GetWorkingModeBit(RF2TTC::BCChannel channel);

  static uint32_t GetWorkingModeBit(RF2TTC::OrbitChannel channel);


// members

public:

  /**
   * The RF2TTC constructor. Scans the crate looking for an RF2TTC card.
   * @param bus A reference to a bus adapter to communicate with the RF2TTC.
   * @param useSingleWordBlockTransfer If true, block transfers will be split into single word accesses.
   */
  RF2TTC(
      HAL::VMEBusAdapterInterface& bus,
      int location,
      bool enable_vme_writes_);

  virtual std::string firmwareVersionString();

  virtual void Configure(std::istream &in);

  virtual void WriteConfiguration(std::ostream &out, const std::string &comment = "");

  //! Little helper to convert a uint32_t into a hex std::string.
  std::string UInt32ToHexString(uint32_t const numVal) const;

  // Getters for 32-bit registers

  //! Gets manufacturer ID
  uint32_t ManufacturerId() const;

  std::string ManufacturerIdStr() const;

  //! Gets board ID. Should be VME64xDeviceInfo::BOARD_ID_RF2TTC.
  uint32_t BoardId() const;

  std::string BoardIdStr() const;

  uint32_t RevisionId() const;

  std::string RevisionIdStr() const;

  uint32_t ProgramId() const;

  //! prints the register contents and interprets them
  void DumpRegistersVerbose(std::ostream &os = std::cout);

  void DumpDelay25RegistersVerbose(std::ostream &os = std::cout);

  void DumpDACRegistersVerbose(std::ostream &os = std::cout);

  void DumpSwitchRegistersVerbose(std::ostream &os = std::cout);

  //! retrieve DAC register Address object for given BCChannel
  const Address& GetBCDACRegister(BCChannel channel) const;

  //! retrieve DAC register Address object for given OrbitChannel
  const Address& GetOrbitDACRegister(OrbitChannel channel) const;

  /**
   * Returns the register Address object of the corresponding multiplexer (MUX)
   * for the given operating mode and BC channel line.
   */
  const Address& GetBCSelectRegister(BCChannel channel, OperatingMode opmode);

  const Address& GetQPLLModeRegister(BCChannel channel) const;

  bool IsQPLLLocked(BCChannel channel);

  bool QPLLHasError(BCChannel channel);

  bool IsQPLLInAutoRelockMode(BCChannel channel, uint32_t *_content = NULL, bool *other_bits_nonzero = NULL);

  void SetQPLLAutoRelockMode(BCChannel channel, bool auto_relock);

  std::string getVerboseQPLLStatus(RF2TTC::BCChannel channel);

  std::string getVerboseQPLLMode(RF2TTC::BCChannel channel);

  const Address& GetBCDelay25Register(BCChannel channel);

  bool GetOrbitPeriodFifoEmptyFlag(OrbitChannel channel);

  bool GetOrbitPeriodFifoFullFlag(OrbitChannel channel);

  std::string getVerboseOrbitPeriodFifoStatus(RF2TTC::OrbitChannel channel);

  uint32_t ReadLastOrbitPeriod(OrbitChannel channel);

  void EnableOrbitPeriodCounter(OrbitChannel channel, bool enable);

  unsigned ReadOrbitCounter(OrbitChannel channel);

  uint32_t ReadDelay25Register(const Address & add, const std::string &comment = "") const;

  std::string getVerboseDelay25Status(const ttc::Address& addr);

  /**
   * Reads a TTCrx register (which is attached via I2C to the FPGA).
   * WARNING: In contrast to the other I2C reading methods,
   *          this only returns the lower eight bits.
   */
  uint32_t ReadTTCrxRegister(unsigned offset, const std::string &comment = "");

  void WriteTTCrxRegister(unsigned offset, uint32_t data, const std::string &comment = "");

  void ResetTTCrxWatchdogFlag();

  unsigned GetTTCrxSingleErrorCount();

  unsigned GetTTCrxDoubleErrorCount();

  /**
   * Single event upset (SEU) counter.
   * Probably irrelevant for the TTCrx since such errors are supposed to occur due to radiation.
   */
  unsigned GetTTCrxSeuErrorCount();

  unsigned ReadTTCrxStatusRegister();

  // some bits of the TTCrx status register

  //! tells if a watchdog timeout has happened (i.e. an auto-reset was performed)
  bool TTCrxWatchDogTimeOutHappened();

  bool TTCrxBChannelIsSynchronized();

  bool TTCrxDLLReady();

  bool TTCrxPLLReady();

  bool IsTTCrxReady();

  // Python convenience methods.

  unsigned ReadDelay25RegisterUnsigned(const std::string &reg_name) const;

  unsigned ReadTTCrxRegisterPython(unsigned offset);

  void WriteTTCrxRegisterPython(unsigned offset, unsigned data);

  //! Write the enable bit
  void EnableDelay25BC(BCChannel channel, bool enable);

  //! Read the enable bit
  bool IsDelay25EnabledBC(BCChannel channel);

  /**
   * Tells if delay25 is enabled for the given OrbitChannel.
   * @param output_path determines whether we want to have the info for the orbit input or orbit output side.
   */
  bool IsDelay25EnabledOrbit(OrbitChannel channel, bool output_path);

  void EnableDelay25OrbitInput(OrbitChannel channel, bool enable);

  void EnableDelay25OrbitOutput(OrbitChannel channel, bool enable);

  void EnableAllDelay25BC(bool enable);

  void EnableAllDelay25OrbitInput(bool enable);

  void EnableAllDelay25OrbitOutput(bool enable);

  void EnableAllDelay25Orbit(bool enable);

  //! enables/disables all orbit and BC delay25 paths
  void EnableAllDelay25(bool enable);

  void SetDelay25BC(BCChannel channel, unsigned units);

  /**
   * Returns the number of steps of the delay25 of given BC channel.
   * We do NOT check for unused nonzero bits
   * since there is the enable bit which we do not read here.
   */
  unsigned GetDelay25BC(BCChannel channel);

  /**
   * Similar to GetDelay25BC().
   * Returns the number of steps of the delay25 of given orbit channel
   * (delay on input or output side depending on output_path).
   */
  unsigned GetDelay25Orbit(OrbitChannel channel, bool output_path);

  void SetDelay25OrbitInput(OrbitChannel channel, unsigned units);

  void SetDelay25OrbitOutput(OrbitChannel channel, unsigned units);

  void SetAllDelay25BC(unsigned units);

  void SetAllDelay25OrbitInput(unsigned units);

  void SetAllDelay25OrbitOutput(unsigned units);

  void SetAllDelay25Orbit(unsigned units);

  //! Sets all orbit and BC delay25 delays.
  void SetAllDelay25(unsigned units);

  void SetBCDAC(BCChannel channel, unsigned value);

  unsigned GetBCDAC(BCChannel channel);

  void SetOrbitDAC(OrbitChannel channel, unsigned value);

  unsigned GetOrbitDAC(OrbitChannel channel);

  void SetAllBCDAC(unsigned units);

  void SetAllOrbitDAC(unsigned units);

  void SetAllDAC(unsigned units);

  class BadChannelException : public std::invalid_argument
  {
  public:
    BadChannelException(const std::string &msg) : std::invalid_argument(msg) {}
  };

  // Signal selection (multiplexers).

  /**
   * Sets the state of a multiplexer (for the given working mode).
   * Checks whether we can actually set the source for the given multiplexer.
   *
   * In order to set a non-BCMAIN path to external,
   * call it with 'source' and 'multiplexer' set to the same value.
   */
  void SetBCSelect(BCChannel multiplexer, OperatingMode opmode, BCChannel source);

  void SetOrbitSelect(OrbitChannel multiplexer, OperatingMode opmode, OrbitChannel source);

  void SetOrbitPulseLength(OrbitChannel channel, unsigned value);

  unsigned GetLastOrbitLength(RF2TTC::OrbitChannel channel, bool *other_bits_nonzero = NULL);

  //! gets value of register encoding length (period) of internal orbit
  unsigned GetInternalOrbitPeriodLength(
      RF2TTC::OrbitChannel channel,
      uint32_t *_content = NULL,
      bool *other_bits_nonzero = NULL);

  //! sets length (period) of the internal orbit
  void SetInternalOrbitPeriodLength(RF2TTC::OrbitChannel channel, unsigned orbit_period);

  //! repeatedly reads orbit period, returns result as vector (testing only, direct register access, not using FIFO)
  std::vector<unsigned> ReadOrbitLengthsSimple(OrbitChannel channel, unsigned num_orbits);

  std::vector<unsigned> ReadOrbitLengths(OrbitChannel channel, unsigned num_orbits, bool &overflow);

  void DoOrbitLengthAnalysis(OrbitChannel channel, unsigned num_orbits);

  void GetQPLLInfo(
      RF2TTC::BCChannel channel,
      bool &qpll_ok,
      bool &qpll_locked,
      bool *has_other_bits = NULL,
      uint32_t *register_content = NULL) const;

  unsigned GetInternalOrbitPeriodCounter(
      RF2TTC::OrbitChannel channel,
      uint32_t *_content = NULL,
      bool *other_bits_nonzero = NULL);

  //! Returns the orbit pulse length according to the register
  unsigned GetOrbitPulseLength(
      RF2TTC::OrbitChannel channel,
      uint32_t *_content = NULL,
      bool *other_bits_nonzero = NULL);

  unsigned GetOrbitCoarseDelay(
      RF2TTC::OrbitChannel channel,
      uint32_t *_content = NULL,
      bool *other_bits_nonzero = NULL);

  void SetOrbitCoarseDelay(RF2TTC::OrbitChannel channel, unsigned numbx);

  bool IsOrbitPolarityInverted(
      RF2TTC::OrbitChannel channel,
      uint32_t *_content = NULL,
      bool *other_bits_nonzero = NULL);

  bool IsOrbitCounterEnabled(RF2TTC::OrbitChannel channel);

  bool IsOrbitInternalGeneratorEnabled(RF2TTC::OrbitChannel channel);

  void EnableOrbitInternalGenerator(RF2TTC::OrbitChannel channel, bool enable);

  bool IsOrbitPeriodLengthMeasurementEnabled(RF2TTC::OrbitChannel channel);

  //! Tells whether working mode for given BC channel is automatic or manual.
  bool IsWorkingModeAutomatic(RF2TTC::BCChannel channel);

  //! Tells whether working mode for given orbit channel is automatic or manual.
  bool IsWorkingModeAutomatic(RF2TTC::OrbitChannel channel);

  //! Sets working mode for given BC channel (automatic or manual)
  void SetWorkingModeAutomatic(RF2TTC::BCChannel channel, bool automatic);

  //! Sets working mode for given orbit channel (automatic or manual)
  void SetWorkingModeAutomatic(RF2TTC::OrbitChannel channel, bool automatic);

  /**
   * Returns one of 40, 80, 32 or 64.
   * @param reg must be one of the RF2TTCAdd::*_GCR registers
   */
  unsigned GetDelay25FrequencyMode(
      const Address &reg,
      uint32_t *_content = NULL,
      bool *other_bits_nonzero = NULL) const;

  //! Tells for BC1, BC2, or BCREF whether source is external (==>true) or internal (==>false).
  bool IsBCSourceExternal(
      RF2TTC::BCChannel channel,
      RF2TTC::OperatingMode opmode,
      uint32_t *_content = NULL,
      bool *other_bits_nonzero = NULL);

  //! Tells for ORBIT1, ORBIT2, or ORBIT_INTERNAL (?) whether source is external (==>true) or internal (==>false).
  bool IsOrbitSourceExternal(
      RF2TTC::OrbitChannel channel,
      RF2TTC::OperatingMode opmode,
      uint32_t *_content = NULL,
      bool *other_bits_nonzero = NULL);

  //! Sets source for BC channel BC1, BC2, or BCREF (don't use for BCMAIN).
  void SetBCSourceExternal(BCChannel channel, OperatingMode opmode, bool is_external);

  //! Sets source for orbit channel ORBIT1, ORBIT2, or ORBIT_INTERNAL (?) (don't use for ORBIT_MAIN).
  void SetOrbitSourceExternal(OrbitChannel channel, OperatingMode opmode, bool is_external);

  //! Tells which BCMAIN source is in use for given OperatingMode.
  RF2TTC::BCChannel GetBCMainSource(
      RF2TTC::OperatingMode opmode,
      uint32_t *_content = NULL,
      bool *other_bits_nonzero = NULL);

  //! Tells which ORBIT_MAIN source is in use for given OperatingMode.
  RF2TTC::OrbitChannel GetOrbitMainSource(
      RF2TTC::OperatingMode opmode,
      uint32_t *_content = NULL,
      bool *other_bits_nonzero = NULL);

  std::string getVerboseOrbitSource(
      RF2TTC::OrbitChannel channel,
      RF2TTC::OperatingMode opmode);

  //! Sets BCMAIN source.
  void SetBCMainSource(RF2TTC::OperatingMode opmode, RF2TTC::BCChannel source);

  //! Sets ORBIT_MAIN source.
  void SetOrbitMainSource(RF2TTC::OperatingMode opmode, RF2TTC::OrbitChannel source);

  void ConfigureMachineMode(unsigned machine_mode, bool is_beam_mode);

  /**
   * Returns true if the given LHC machine mode is set to 'beam',
   * false if it is set to 'no beam'.
   */
  bool IsBeamForMachineMode(unsigned machine_mode);

  void HardwareReset(uint32_t bitmask, uint32_t miliseconds_to_wait = 100);

  void ResetDelay25(uint32_t miliseconds_to_wait = 100);

  void ResetQPLLBC1(uint32_t miliseconds_to_wait = 100);

  void ResetQPLLBC2(uint32_t miliseconds_to_wait = 100);

  void ResetQPLLBCRef(uint32_t miliseconds_to_wait = 100);

  void ResetQPLLBCMain(uint32_t miliseconds_to_wait = 100);

  void ResetQPLLAll(uint32_t miliseconds_to_wait = 100);

  void ResetTTCrx(uint32_t miliseconds_to_wait = 100);

  void ResetBoard(uint32_t miliseconds_to_wait = 100);

  /* The following return true if the corresponding system of the
     board is in reset mode (and thus might not be able to respond). */

  bool IsResetDelay25();

  bool IsResetQPLLAny();

  bool IsResetTTCrx();

  bool IsResetBoard();

  uint32_t GetMachineMode();

  /**
   * Returns the current operating mode for the given BC channel. This is either
   * OPMODE_MANUAL (if manual is selected) or
   * OPMODE_BEAM or OPMODE_NOBEAM (if automatic is selected).
   */
  OperatingMode GetCurrentOperatingMode(BCChannel channel);

  /**
   * Returns the current operating mode for the given orbit channel. This is either
   * OPMODE_MANUAL (if manual is selected) or
   * OPMODE_BEAM or OPMODE_NOBEAM (if automatic is selected).
   */
  OperatingMode GetCurrentOperatingMode(OrbitChannel channel);

  //! Returns the BCMAIN source for the currently active operating mode.
  RF2TTC::BCChannel GetCurrentBCMainSource();

  //! Returns the ORBITMAIN source for the currently active operating mode.
  RF2TTC::OrbitChannel GetCurrentOrbitMainSource();

  //! returns IsBCSourceExternal for given channel and current operating mode
  bool IsCurrentBCSourceExternal(RF2TTC::BCChannel channel);

  //! returns IsOrbitSourceExternal for given channel and current operating mode
  bool IsCurrentOrbitSourceExternal(RF2TTC::OrbitChannel channel);

  //! Returns list of write-only registers (to be excluded from register dump)
  virtual std::vector<const Address*> GetExcludedVMEAddressesForDump() const;

  //! Returns map telling for each Orbit channel whether the orbit counter is changing.
  std::map<OrbitChannel, bool> CheckOrbitCounterChanging(const std::vector<OrbitChannel> &channels);

  /**
   * For the given orbit DAC settings, checks whether
   * the orbit counter increments correctly (!) or not.
   *
   * @return is of the form result[i][j] where
   * i is the Orbit channel,
   * j is the DAC value setting and the content is
   * true if the orbit counter increased and
   * false if not.
   */
  std::map<OrbitChannel, std::map<std::pair<unsigned, unsigned>, bool> >
  ScanOrbitDACSettings(
      const std::vector<OrbitChannel>& channels,
      const std::vector<unsigned>& dac_values,
      const std::vector<unsigned>& delay25_values);

  //! Dump the RF2TTC status and some useful configuration details to the logger.
  void DumpStatus();

private:

  //! Read from a I2C register, where we need to do two reads with waiting for 2ms in between.
  uint32_t ReadI2CRegister(const Address& add, const Address& fifo_add, const std::string& comment = "") const;

  void EnableDelay25(const Address &addr, bool enable);

  bool IsDelay25Enabled(const Address &addr);

  void SetDelay25(const Address &addr, unsigned units);

  //! Just checks the desired value (if NDEBUG is not set). TODO: really?
  void SetDAC(const Address &addr, unsigned value);

  unsigned GetDAC(const Address &addr);

  /**
   * Helper method for the following 'IsOrbit...Enabled' methods.
   * This implements the bit layout within the register.
   * */
  bool IsOrbitBitSet(uint32_t register_content, RF2TTC::OrbitChannel channel);
};

}


#endif
