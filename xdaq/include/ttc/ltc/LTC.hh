#ifndef _ttc_ltc_LTC_hh_
#define _ttc_ltc_LTC_hh_


#include "ttc/utils/GenericTTCModule.hh"

#include "ttc/ltc/Monitoring.hh"
#include "ttc/ltc/LTCStatusInfo.hh"
#include "ttc/utils/BGOChannel.hh"
#include "ttc/utils/CyclicTriggerOrBGO.hh"

#include <string>


#define LTC_RESET_BGOS 2
#define LTC_RESET_ORBIT 4
#define LTC_RESET_EVENT 8
#define LTC_RESET_TRIGGER 16
#define LTC_RESET_BLOCKED 32
#define LTC_RESET_CANCELLED 256
#define LTC_RESET_ALLCOUNTERS 0x13e


namespace HAL
{
class VMEBusAdapterInterface;
}


//! exception thrown by CheckBXConflicts
XCEPT_DEFINE_EXCEPTION(ttc, BXConflictsDetected);


namespace ttc
{

class RAMTriggers;
class BGOMap;

struct PeriodicThreadPars
{
  bool newSetup;
  double waitNsec;
  double enabled;
  time_t t0, t1;
};

struct GPSTimeThreadPars
{
  bool newSetup;
  double waitNsec;
  double enabled;
  time_t t0, t1;
};

struct MonitoringThreadPars
{
  bool newSetup;
  double waitNsec;
  double enabled;
  time_t t0, t1;
};

struct StatusParameters
{
  bool newSetup;
  double waitNsec;
  double enabled;
  time_t t0, t1;
};

struct LTCThreadPars
{
  bool newSetup;
  LTC* myLTC;
  MonitoringThreadPars Monitoring;
  GPSTimeThreadPars GPS;
  PeriodicThreadPars Periodic;
  StatusParameters Parameters;
};

/**
 * Represents an LTC card, and all the operations that may be performed on it.
 */
class LTC : public GenericTTCModule
{
  // Classes which need access to private items.
  friend class LTCConfiguration;
  friend class LTCConfigurationItem_RunLog;
  friend class LTCConfigurationItem_FifoDump;
  friend class LTCConfigurationItem_CyclicTriggerOrBgo;
  friend class LTCOrbitJumps;

public:

  /**
   * The LTC constructor. Scans the crate looking for an LTC card.
   * If there is not exactly one enabled LTC in the crate,
   * the plug-n-play code will throw a logic_error exception.
   *
   * @param bus A reference to a bus adapter to communicate with the LTC.
   * @param useSingleWordBlockTransfer if true, block transfers will be split into single word accesses.
   */
  LTC(
      HAL::VMEBusAdapterInterface& bus,
      int location,
      uint32_t btimecorr,
      bool enable_vme_writes_,
      uint32_t slinkSrcId = 815);

  virtual ~LTC();

  virtual std::string firmwareVersionString();

  //! Returns the numeric LTC firmware version.
  uint32_t ReadFirmwareVersion() const;

  //! Returns the lower 16 bits of ReadFirmwareVersion().
  uint32_t GetFirmwareVersion() const;

  //! Reads the Board ID and returns it.
  uint32_t GetBoardID() const;

  size_t NChannels() const;

  void ExecuteVMEBGO(const int8_t ibgo, const int32_t BX = -1);

  void ExecuteVMETrigger();

  uint32_t GetSlinkSrcId() const;

  void StartCyclicGenerators();

  void StopCyclicGenerators();

  //! Like StopCyclicGenerators() but also stop the ones configured as 'permanent'.
  void StopAllCyclicGenerators();

  void StartPermanentCyclicGenerators();

  void SendControlWord();

  uint32_t GetControlWord() const;

  uint32_t ReadControlWord() const;

  uint32_t GetVMEBGOBX() const;

  void SetVMEBX(const uint32_t bx);

  //! Configure the LTC.
  virtual void Configure(std::istream &in);

  /**
   * Writes the current configuration to the stream 'out'.
   * Adds lots of comments to the configuration text.
   */
  virtual void WriteConfiguration(std::ostream& out, const std::string& comment = "");

  virtual void ExecuteSequence(const std::string& identifier);

  virtual void ExecuteSequenceLine(const std::string& line);

  void failParseSequenceLineInvalidParam(
      const std::string& line,
      const std::string& command,
      const std::string& param);

  RAMTriggers* GetRAMTriggers();

  BGOChannel* GetBGOChannel(const size_t channel);

  void SetQPLLExternal(bool external);

  bool IsQPLLExternal() const;

  /**
   * If called with doReset == true,
   * this will clear the reset state after a given delay (0.1 s)
   */
  void ResetQPLL(bool doReset);

  bool Is_ResetQPLL() const;

  void AutoRestartQPLL(bool enable);

  bool Is_AutoRestartQPLL() const;

  void SetQPLLFrequencyBits(uint32_t freq, bool only4LSBs = false);

  uint32_t GetQPLLFrequencyBits() const;

  uint32_t ReadEventCounter() const;

  uint32_t ReadTriggerCounter() const;

  uint32_t ReadOrbitCounter() const;

  uint32_t ReadStrobeCounter() const;

  uint32_t ReadBlockedTriggersCounter() const;

  uint32_t BoardStatus() const;

  void ResetCounters(unsigned counters = LTC_RESET_ALLCOUNTERS & ~LTC_RESET_TRIGGER);

  void ResetEventFIFO();

  void MainReset();

  bool IsExternalTriggerEnabled(const size_t i) const;

  void EnableExternalTrigger(const size_t i, const bool Enable = true);

  void SetL1ATicket(unsigned num); // set size of trigger burst (0=disable)

  unsigned GetL1ATicket() const;

  unsigned GetMaxTrigger() const;

  void SendL1ATicket();

  //! Start the triggers which are generated from a pattern stored in internal RAM.
  void StartRAMTrigs();

  //! Stop the triggers which are generated from a pattern stored in internal RAM.
  void StopRAMTrigs();

  bool IsCyclicTrigEnabled() const;

  void EnableCyclicTrig(bool enable = true);

  bool IsRAMTrigEnabled() const;

  void EnableRAMTrig(bool enable = true);

  /**
   * Enables/disables L1A.
   * Note: It seems this also needs to be called in order to to
   * enable non-permanent cyclic BGO (!) generators.
   */
  void EnableL1A(const bool enable = true);

  bool IsL1AEnabled() const;

  bool OrbitInSync() const;

  uint32_t CancelledTriggers() const;

  /**
   * Checks whether any of the bunch crossings at which BGOs shall be sent
   * (e.g. from VME or cyclic triggers) are too close to each other.
   * Thrown ttc::exception::BXConflictsDetected in case of conflicts found, else returns normally.
   */
  void CheckBXConflicts();

  bool PeriodicSequenceEnabled() const;

  double Periodicity() const;

  //! Returns the number of cyclic trigger generators.
  size_t NCyclicTrigger() const;

  //! Returns the number of cyclic BGO generators.
  size_t NCyclicBGO() const;

  CyclicTriggerOrBGO* GetCyclic(const bool trigger, const size_t i);

  //! Reads all cyclic generators back from the LTC.
  void ReadAllCyclicGeneratorsFromLTC();

  /**
   * @param trigger Defines whether this is a trigger (true) or a BGO cyclic generator (false).
   * @param i The number of the generator.
   */
  void WriteCyclicGeneratorToLTC(const bool trigger, const size_t i);

  void ResetCyclicGenerators(const bool trigger, const bool bgo);

  void SetTriggerRule(size_t ntrig, uint32_t minDeltaBX);

  uint32_t GetTriggerRule(size_t ntrig) const;

  size_t FirstTriggerRule() const;

  size_t TriggerRuleSize() const;

  size_t Nextern() const;

  //! Returns the number of 'events' which are in the Event Fifo (?).
  unsigned int GetFIFOLevel() const;

  bool GetFIFOEvents(LTCEventFIFO & ret);

  //! Reads the TTS status register and returns its content.
  uint32_t ReadTTSStatus() const;

  std::string TTSStatusSummary(size_t& mask) const;

  size_t NTTS() const;

  bool IsTTSEnabled(const size_t idx) const;

  void EnableTTS(const size_t idx, const bool Enable = true);

  void EnableBSTGPSviaVME(bool Enable = true);

  bool IsBSTGPSviaVME() const;

  double GetBSTGPSInterval() const;

  void SetBSTGPS(const uint32_t GPSlow, const uint32_t GPShigh);

  void IgnoreSlinkBackpressure(bool Ignore = true);

  bool IsSlinkBackpressureIgnored() const;

  void UpdateMonitoring();

  void EnableMonitoring(const bool enable = true);

  bool IsMonitoringEnabled() const;

  void SetMonitoringInterval(const double dt);

  double GetMonitoringInterval() const;

  uint32_t IncrementRunNumber(bool dontIncrement = false);

  uint32_t GetRunNumber() const;

  void SetRunNumber(const uint32_t run);

  Monitoring* GetMonitoring();;

  void SetBXMask(const bool enable, const size_t begin, const size_t end = 9999);

  void BXMaskReset();

  void GetBXGaps(std::vector<size_t> &begin, std::vector<size_t> &end) const;

  double GetActiveBXFraction() const;

  uint32_t ReadSLinkStatus() const;

  uint32_t ReadSLinkStatus(std::string &status, const bool usehtmlstyle = false) const;

  uint32_t GetWarningInterval() const;

  void SetWarningInterval(const uint32_t pause);

  void SetHWInputDelays(const std::vector<float> &delays);

  std::vector<float> GetHWInputDelays() const;

  void DumpEventFIFO(std::ostream *oo = NULL, bool html = false);

  std::string GetTriggerName(const size_t i) const;

  void SetTriggerName(const size_t i, const std::string &name);

  bool IsClockLocked() const;

  uint32_t GetBTimeCorrection() const;

  const LTCStatusInfo *GetLTCStatusInfo() const;

  void UpdateLTCStatusInfo();

  bool DumpEventFIFOToFile() const;

  bool DefaultFIFODumpEnabled() const;

  std::string FIFODumpPrefix() const;

  std::string EventFIFOToFilePath() const;

  void SetFilePathForFIFODump(const bool enable, const std::string &newpath);

  /**
   * Don't call this method unless you want to get an output frequency around 32 MHz
   * and thus the TTCci unlocked (in an interconnection test).
   */
  void SetExternalCrystalTo160MHz(bool externalQuarzIs160MHz);

  //! Sets the S-Link source ID for the LTC
  void SetSlinkSrcId(uint32_t);

private:

  //! Creates (starts) the parallel thread which e.g. does updating the GPS time via VME etc.
  void CreateParallelThread();

  /** This flag must be read by threads spawned. If this is true,
   they should terminate as soon as possible. */
  bool stop_thread_flag;

  friend void* ParallelThread(void *);

  RAMTriggers* ram_triggers;

  //! Returns information about which TTS inputs were enabled (not the actual input signals).
  size_t GetTTSStatus_Pattern(size_t idx) const;

  //! Returns the date when the firmware was built (the upper 16 bits of ReadFirmwareVersion()).
  uint32_t GetFirmwareBuiltNumber() const;

  void PrintBoardStatus() const;

  void SetInternalTriggerFrequency(const double frequency, bool random = 0);

  //! Stop the cyclic generators configured as 'permanent'.
  void ResetInternalTrigsAndAllCyclicGenerators();

  /**
   * Determines the B channel names (which depends on the BGO map).
   * This should be called whenever the BGO map has changed.
   */
  void SetBChannelNames();

  void ReadChannelStatus(
      const size_t channel,
      uint32_t& signalcounter,
      bool& anycancelled,
      uint32_t& cancelcounter,
      bool& ramempty) const;

  const CyclicTriggerOrBGO* GetCyclic(const bool trigger, const size_t i) const;

  CyclicTriggerOrBGO* ReadCyclicGeneratorFromLTC(const bool trigger, const size_t i);

  /**
   * Same as the TTSStatusSummary command but without the
   * possibility of getting the mask back (for convenience mostly, e.g. from python).
   */
  std::string TTSStatusSummary() const;

  void SetBSTGPSInterval(const double dt);

  //! returns the number of microseconds since 1.1.1970
  uint64_t GetBSTGPSTime() const;

  //! Returns the number of seconds since 1.1.1970.
  unsigned GetBSTGPSTimeSeconds() const;

  void ReadBSTGPS(uint32_t &GPSlow, uint32_t &GPShigh) const;

  //! Returns true if the slink status is 'full' which corresponds to backpressure.
  bool HasSlinkBackPressure() const;

  void EnableGPSFromVME(const bool enable = true);

  void EnableCurrentRatesUpdate(bool enable = true);

  void EnablePeriodicSequence(bool enable = true);

  const Monitoring* GetMonitoring() const;

  std::string GetRunLogPath() const;

  void WriteRunLog() const;


  //! Front Panel input selection.
  mutable uint32_t control_;

  unsigned l1aticket;

  uint32_t VMEbx;

  bool CyclicTrigOn;

  std::vector<BGOChannel> bgo;

  static const size_t maxtriglength = 1024;

  bool L1Aenabled_;

  uint32_t BTimeCorrection_;

  LTCThreadPars ThreadParameters;

  size_t _n_ctg;

  //! cyclic trigger generators
  std::vector<CyclicTriggerOrBGO> _ctg;

  size_t _n_cbg;

  //! Cyclic BGO generators.
  std::vector<CyclicTriggerOrBGO> _cbg;

  bool _ResumeCylic;

  //! The thread spawned (e.g. for periodic updating of the BST time via VME.
  pthread_t thethread;

  Mutex periodicmutex;

  mutable Monitoring monitor;
  bool overwriteRunNo;
  time_t mont0;
  uint32_t orb0;
  uint32_t evt0;
  uint32_t blockedevt0;
  uint32_t bgo0;
  uint32_t can0;
  std::vector<bool> bxmask;
  std::vector<std::string> trigname;
  LTCStatusInfo CurrentRates;
  std::string runlog;
  bool dumpevtstofile;
  std::string dumpevtstofilepath;
  bool dumpevtstofile_setonenable;
  std::string dumpevtstofilepath_prefix;

  //! Object to handle things related to the BGO map.
  BGOMap* bgo_map;
};

/**
 * This is the method which is called when spawning another thread.
 * It's an infinite loop which periodically performs certain tasks.\
 */
void* ParallelThread(void*);

}


#endif
