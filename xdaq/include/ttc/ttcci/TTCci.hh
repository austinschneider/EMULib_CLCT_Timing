#ifndef _ttc_ttcci_TTCci_hh_
#define _ttc_ttcci_TTCci_hh_


#include "ttc/utils/GenericTTCModule.hh"

#include "ttc/utils/Utils.hh"
#include "ttc/utils/BChannel.hh"
#include "ttc/utils/CyclicTriggerOrBGO.hh"
#include "ttc/utils/LockMutex.hh"


#define INAME(I) ((I) == ttc::TTC ? "TTC" :      \
                  (I) == ttc::CTC ? "CTC" : \
                  (I) == ttc::LTCIN ? "LTC" : \
                  (I) == ttc::FRONTP0 ? "FRONTPANEL0" : \
                  (I) == ttc::FRONTP1 ? "FRONTPANEL1" : \
                  (I) == ttc::VME ? "VME" : \
                  (I) == ttc::INTERNAL ? "INTERNAL" : \
                  (I) == ttc::CYCLIC ? "CYCLIC" : \
                  (I) == ttc::SCOM ? "SCOM" : \
                  (I) == ttc::BCHANNEL ? "BCHANNEL" : \
                  "UNDEFINED")

#define INTERFACE(S) ((S) == "TTC" ? ttc::TTC : \
                      (S) == "CTC" ? ttc::CTC : \
                      (S) == "LTC" ? ttc::LTCIN : \
                      (S) == "FRONTPANEL0" ? ttc::FRONTP0 : \
                      (S) == "FRONTPANEL1" ? ttc::FRONTP1 : \
                      (S) == "VME" ? ttc::VME : \
                      (S) == "INTERNAL" ? ttc::INTERNAL : \
                      (S) == "CYCLIC" ? ttc::CYCLIC : \
                      (S) == "SCOM" ? ttc::SCOM : \
                      (S) == "BCHANNEL" ? ttc::BCHANNEL : \
                      ttc::UNDEFINED)


namespace HAL
{
class VMEBusAdapterInterface;
}


namespace ttc
{

class TTCci;
class BGOMap;
class RAMTriggers;

struct TTCciThreadPars
{
  bool newSetup;
  TTCci* myTTCci;
  double waitNsec;
  double enabled;
};

enum ExternalInterface { TTC, CTC, LTCIN, INTERNAL, FRONTP1, FRONTP0, VME, CYCLIC, SCOM, BCHANNEL, UNDEFINED };


//! Represents an TTCci card, and all the operations that may be performed on it.
class TTCci : public GenericTTCModule
{
  friend class TTCciConfiguration;
  friend class TTCciConfigurationItem_ClockSource;
  friend class TTCciConfigurationItem_CyclicGen;
  friend class TTCciConfigurationItem_TriggerInterval;
  friend class TTCciConfigurationItem_BGOChannelSetup;
  friend class TTCciConfigurationItem_BGOChannelData;

  friend void* Thread4PeriodicSequence(void*);

public:

  //! Puts together a B frame long command.
  static uint32_t ComposeLongCommand(
      unsigned address,
      bool isExternal,
      unsigned char subaddr,
      unsigned char data);

  /**
   * Returns a long broadcast command which enables the parallel output bus of the TTCrx
   * (assuming the other bits of the TTCrx control register are set to their values after reset).
   * This command has to be sent to the G3TTCrx before long commands can be read.
   */
  static uint32_t GetTTCrxParallelBusEnableCommand();

  /**
   * This method is static so that TTCciControl can use it before object initialization.
   */
  static bool IsRamBufferAtEnd(uint32_t rmc_register_content);

  static size_t NChannels();

public:

  /**
   * The TTCci constructor.
   * Scans the crate looking for a TTCci card.
   * @param bus A reference to a bus adapter to communicate with the TTCci.
   * @param useSingleWordBlockTransfer If true, block transfers will be split into single word accesses.
   */
  TTCci(
      HAL::VMEBusAdapterInterface& bus,
      int location,
      uint32_t btimecorr,
      uint32_t delayt2corr,
      bool enable_vme_writes_);

  virtual std::string firmwareVersionString();

  uint32_t getBTimeCorrection();

  uint32_t getDelayT2Correction();

  //! initializes the hardware
  void initHardware();

  /**
   * Returns the lowest eight bits of the firmware version field
   * (i.e. the part after the firmware date).
   */
  uint32_t GetFirmwareVersion() const;

  //! Returns the firmware date which is (when read in hex) of the form yymmdd.
  uint32_t GetFirmwareDate() const;

  uint32_t GetBoardID() const;

  void ExecuteVMEBGO(const unsigned int ibgo, const bool EnableVMEFirst = false);

  void SendInputSelection(uint32_t inselect_new);

  void ResumeCylicGenAtNextStart(bool resume = true);

  uint32_t ReadInputSelection() const;

  /**
   * Select the clock source.
   * @param itf Option for clock source: TTC, CTC, LTC, or INTERNAL.
   */
  void SelectClock(const ExternalInterface itf);

  ExternalInterface CheckClock() const;

  bool IsSourceSelected(const std::string& Name, const ExternalInterface& Source) const;

  /**
   * Select the trigger source.
   * @param itf Option for trigger source: TTC, CTC, LTC, FRONTP1, or FRONTP2.
   */
  void SelectTrigger(const std::vector<ExternalInterface>& itf);

  std::vector<ExternalInterface> CheckTrigger() const;

  /**
   * Choose the BGO source:
   * @param itf Option for BGO source: VME, CTC, or LTC.
   */
  void SelectBGOSource(const std::vector<ExternalInterface>& itf);

  std::vector<ExternalInterface> CheckBGOSource() const;

  //! Switch off all BGO sources.
  std::vector<ExternalInterface> SwitchOffBGOs();

  /**
   * Select the Orbit source.
   * @param itf Option for orbit source: TTC, CTC, LTC, or INTERNAL.
   */
  void SelectOrbitSource(const ExternalInterface itf);

  ExternalInterface CheckOrbitSource() const;

  void SelectSource(const std::string& Name, const std::vector<ExternalInterface>& itf);

  std::vector<ExternalInterface> CheckSource(const std::string& Name) const;

  void SelectInputs(
      const ExternalInterface clockSource,
      const ExternalInterface orbitSource,
      const std::vector<ExternalInterface>& triggerSource,
      const std::vector<ExternalInterface>& bgoSource);

  void SelectInputs(
      const std::string clockSource,
      const std::string orbitSource,
      const std::vector<std::string>& triggerSource,
      const std::vector<std::string>& bgoSource);

  /**
   * Returns a list of possible sources for the given signal.
   * @param Name The name of the signal, one from: 'Trigger', 'Clock', 'BGO', 'Orbit'.
   */
  std::vector<ExternalInterface> GetSourceList(const std::string& Name) const;

  /**
   * Returns a list of possible sources (as human-readable strings) for the given signal.
   * @param Name The name of the signal, one from: 'Trigger', 'Clock', 'BGO', 'Orbit'.
   */
  std::vector<std::string> GetSourceListNames(const std::string& Name) const;

  //! Configure the TTCci.
  void Configure(std::istream& in);

  void WriteConfiguration(std::ostream& out, const std::string& comment = "");

  BChannel* GetBChannel(const size_t channel);

  void SetBChannelNames();

  void EnableQPLL(bool enable = true);

  void DisableQPLL();

  bool IsQPLLEnabled() const;

  void ResetQPLL(bool doReset);

  bool Is_ResetQPLL() const;

  void AutoRestartQPLL(bool enable);

  bool Is_AutoRestartQPLL() const;

  void SetQPLLFrequencyBits(uint32_t freq, bool only4LSBs = false);

  uint32_t GetQPLLFrequencyBits(bool only4LSBs = false) const;

  /**
   * Sets the number of bunch crossings the given external trigger input (0 or 1) should be delayed.
   * Valid values are 0..255.
   * Earlier versions of the firmware do not support delaying the external trigger input 0.
   * If one tries to do this, an exception is thrown.
   */
  void SetExtTrigInputDelay(unsigned input_num, uint32_t delay);

  //! Returns the number of bunch crossings the given external trigger input is delayed.
  uint32_t GetExtTrigInputDelay(unsigned input_num) const;

  bool ConfiguringResetsQPLL() const;

  void ConfiguringResetsQPLL(bool value);

  uint32_t ReadEventCounter() const;

  uint32_t ReadOrbitCounter() const;

  uint32_t ReadStrobeCounter() const;

  uint32_t BoardStatus(bool getPrevious = false) const;

  void PrintBoardStatus() const;

  void ResetCounters();

  void ClearLatchedStatus();

  void MainReset();

  void EnableL1A();

  void DisableL1A();

  bool IsL1AEnabled() const;

  bool IsLaserOn() const;

  bool ClockInverted() const;

  bool ClockLocked() const;

  bool ClockLocked_Latched(bool getPrevious = false) const;

  bool IsBDataCancelled() const;

  bool IsBDataCancelled_Latched(bool getPrevious = false) const;

  bool IsDataClkError() const;

  bool IsDataClkError_Latched(bool getPrevious = false) const;

  bool IsClkSingleEvtUpset() const;

  bool IsClkSingleEvtUpset_Latched(bool getPrevious = false) const;

  bool MissedL1A() const;

  bool MissedL1A_Latched(bool getPrevious = false) const;

  bool DoubleL1Aat40MHz() const;

  bool DoubleL1Aat40MHz_Latched(bool getPrevious = false) const;

  bool OrbitSyncError() const;

  bool OrbitSyncError_Latched(bool getPrevious = false) const;

  bool TriggerSuppressed() const;

  bool TriggerSuppressed_Latched(bool getPrevious = false) const;

  RAMTriggers* GetRAMTriggers();

  BGOChannel* GetBGOChannel(const size_t channel);

  //! Writes the configuration of one BGO channel (data content, delays etc.) to the TTCci.
  void WriteBGODataToTTCci(const size_t channel);

  //! Writes the configuration of all BGO channel (data content, delays etc.) to the TTCci.
  void WriteBGODataToTTCci();

  void ReadBGODataFromTTCci(const size_t nwords);

  void ResetAllBGODataOnTTCci();

  /**
   * Retrieves the addresses for the BGO configuration
   * (i.e. which data frames to be sent upon reception of a BGO command,
   *  e.g. from the LTC or internal generator).
   */
  void GetBGODataRegisterAddresses(const size_t channel, ttc::Address& addressD, ttc::Address& addressP);

  void ConfigureBData(const bool Enable, const bool shortword, const uint32_t data);

  void ReadBDataConfiguration(bool& IsEnabled, bool& IsShortWord, uint32_t& data) const;

  void SendShortBGODataFromVME(uint32_t d);

  void SendLongBGODataFromVME(uint32_t d);

  //! Returns information about the status of one B-channel.
  void ReadChannelStatus(
      const size_t channel,
      uint32_t& signalcounter,
      bool& anycancelled,
      uint32_t& cancelcounter,
      bool& ramempty) const;

  //! Returns signal counter value for a given B-channel.
  uint32_t ReadChannelSignalCounter(size_t channel) const;

  bool CheckAllChannelStatus(
      std::vector<uint32_t>& Ncancelled,
      std::vector<uint32_t>& Nsignal,
      std::vector<bool>& RAMIsEmpty) const;

  void ExecuteSequenceLine(const std::string& line);

  void failParseSequenceLineInvalidParam(
      const std::string& line,
      const std::string& command,
      const std::string& param);

  bool PeriodicSequenceEnabled() const;

  double Periodicity() const;

  size_t NCyclicTrigger() const;

  size_t NCyclicBGO() const;

  /**
   * Returns object representing cyclic trigger or BGO.
   * @param trigger If true, we mean cyclic trigger generator, else cyclic BGO generator.
   * @param i The index of the cyclic generator.
   */
  CyclicTriggerOrBGO* GetCyclic(const bool trigger, const size_t i);

  const CyclicTriggerOrBGO* GetCyclic(const bool trigger, const size_t i) const;

  CyclicTriggerOrBGO* ReadCyclicGeneratorFromTTCci(const bool trigger, const size_t i);

  /**
   * @param trigger If true, we mean cyclic trigger generator, else cyclic BGO generator.
   */
  void WriteCyclicGeneratorToTTCci(const bool trigger, const size_t i);

  void ResetCyclicGenerators(const bool trigger, const bool bgo);

  void SetTriggerRule(size_t ntrig, uint32_t minDeltaBX);

  uint32_t GetTriggerRule(size_t ntrig, bool readfromboard = false) const;

  size_t FirstTriggerRule() const;

  size_t TriggerRuleSize() const;

  void SendBST(int address = 0);

  bool HasCancelledBData(uint32_t rmc_register_content) const;

  unsigned BGORequestCounter(uint32_t rmc_register_content) const;

  unsigned BGOCancelledCounter(uint32_t rmc_register_content) const;

  //! Reads register and returns the number of BGOs requested.
  unsigned GetNumBgosRequested(unsigned channel);

  //! Reads register and returns the number of BGOs cancelled.
  unsigned GetNumBgosCancelled(unsigned channel);

  /**
   * Returns true if this firmware version supports per-channel BGO counters
   * which are longer than 16 bit (24 bit at the time of writing).
   */
  bool HasLongBGOCountersPerChannel() const;

  /**
   * Returns true if the firmware offers the possibility to have
   * individual postscale numbers for each part of a double/block (?) command.
   */
  bool HasIndividualBPostScaleNumbers() const;

  /**
   * From a certain firmware version on, also the external trigger 0
   * input can be delayed by up to 255 bunch crossings, not only the external input 1.
   */
  bool CanDelayExtTrigger0Input() const;

  //! Returns [0,1] if CanDelayExtTrigger0Input(), else returns [1]
  std::vector<unsigned> GetDelayableExternalTrigInputs() const;

  //! Signals the parallel thread to end and waits for its termination.
  virtual ~TTCci();

  unsigned int Get_Resynch_BGOCh() const;

  unsigned int Get_HardReset_BGOCh() const;

  unsigned int Get_ECntReset_BGOCh() const;

  unsigned int Get_OCntReset_BGOCh() const;

  unsigned int Get_Start_BGOCh() const;

  unsigned int Get_Stop_BGOCh() const;

private:

  /**
   * Gets external trigger input delay mask.
   * Throws an exception if called for external input 0 and firmware does not support delaying it.
   */
  void GetExtTrigInputDelayMask(unsigned input_num, unsigned& mask_width, unsigned& mask_offset) const;

  /**
   * This flag tells us whether or not an explicit QPLL reset
   * was requested upon configuring.
   * (Variable can't be read back from the hardware.)
   */
  bool configuringResetsQPLL_;

  mutable std::vector<BChannel> bgo;

  std::vector<ExternalInterface> triggersource_;
  bool L1Aenabled_;
  uint32_t bTimeCorrection_;
  uint32_t delayT2Correction_;
  mutable std::vector<uint32_t> trigrules;
  uint32_t boardStatusSaved_;

  TTCciThreadPars PeriodicSeqParameters;
  const size_t _n_ctg;

  //! Cyclic trigger generators.
  std::vector<CyclicTriggerOrBGO> _ctg;

  const size_t _n_cbg;

  //! Cyclic BGO generators.
  std::vector<CyclicTriggerOrBGO> _cbg;

  bool _ResumeCylic;
  pthread_t thethread;

  //! The mutex.
  ttc::Mutex periodicmutex;

  //! Object to handle things related to the BGO map.
  BGOMap* bgo_map;

  /**
   * This flag must be read by threads spawned.
   * If this is true, they should terminate as soon as possible.
   */
  bool stop_thread_flag;

  RAMTriggers* ram_triggers;
};

// Non-member functions in namespace ttc

void* Thread4PeriodicSequence(void*);

}


#endif
