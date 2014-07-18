#ifndef _rubuilder_evm_EventIdTable_h_
#define _rubuilder_evm_EventIdTable_h_

#include <boost/shared_ptr.hpp>
#include <ostream>
#include <stdint.h>
#include <string>
#include <map>
#include <vector>

#include "i2o/i2o.h"
#include "rubuilder/utils/Constants.h"
#include "rubuilder/utils/EventUtils.h"
#include "toolbox/BSem.h"


namespace rubuilder { namespace evm { // namespace rubuilder::evm

  class EoLSHandler;

/**
 * \ingroup xdaqApps
 * \brief Table used by the EVM to track the lifecycle of each event id in
 * the event builder.
 *
 * The lifecycle of an event id is tracked using the following three 
 *counters:
 * <ul>
 * <li>freeCounter
 * <li>pairedCounter
 * <li>allocatecCounter
 * </ul>
 * Counters are used to allow multiple threads to modify the lifecyle of an
 * event id without the need for locking (semaphores etc.).  Each counter 
 * must be incremented by only one thread.  All the counters maybe read by
 * any number of threads.
 *
 * The table detects invalid counter increments based on the FSTN of an
 * event id, which is as follows:
 *
 *     Free -> Paired -> Allocated -> "back to Free"
 *
 * From the FSTN the following statements must be true:
 * <ul>
 * <li>(freedCounter         == allocatedCounter) before incrementing
 *     freedCounter
 * <li>((pairedCounter+1)    == freedCounter    ) before incrementing
 *     pairedCounter
 * <li>((allocatedCounter+1) == pairedCounter   ) before incrementing
 *     allocatedCounter
 * </ul>
 *
 * Please note that all the counters are unsigned integers, are continuously
 * incremented and are allowed to wrap around.  The above statements work
 * with wrapping counters.
 */
class EventIdTable
{
public:
  
  /**
   * Event id descriptor.
   */
  struct EventIdDescriptor
  {
    uint64_t freedCounter;
    uint64_t pairedCounter;
    uint64_t allocatedCounter;
    uint32_t trigger;
    uint32_t buIndex;
    uint32_t buResourceId;
    uint32_t runNumber;
    uint32_t lumiSection;
    
    EventIdDescriptor() :
    freedCounter(1),pairedCounter(0),allocatedCounter(0),trigger(0),
    buIndex(0),buResourceId(0),runNumber(0),lumiSection(0) {}
  };
  
  
  /**
   * Constructor.
   */
  EventIdTable(boost::shared_ptr<EoLSHandler>);
  
  
  /**
   * Initialises the event id table.  nbEvtIds is the total number of
   * event ids in the builder and must be less than or equal to
   * utils::MAX_EVT_IDS.  All the event ids in the table are set to
   * the FREE state.
   */
  void init(const uint32_t nbEvtIds);
  
  
  /**
   * Increments by 1 the freed counter of the specified event id.
   * This method throws an exception if the increment is illegal.
   * This method also checks to see if the event id to be freed came by
   * the correct BU resource and was paired with the correct trigger.
   */
  void incrementFreedCounter
  (
    const uint32_t eventId,
    const uint32_t trigger,
    const uint32_t buIndex,
    const uint32_t buResourceId
  );
  
  
  /**
   * Increments by 1 the paired counter of the specified event id.
   * This method displays throws an exception if the increment is illegal.
   */
  void incrementPairedCounter
  (
    const uint32_t eventId,
    const uint32_t trigger,
    const uint32_t runNumber,
    const uint32_t lumiSection
  );
  
  
  /**
   * Increments by 1 the allocated counter of the specified event id.
   * This method throws an exception if the increment is illegal.
   */
  void incrementAllocatedCounter
  (
    const uint32_t eventId,
    const uint32_t buIndex,
    const uint32_t buResourceId
  );
  
  /**
   * Prints the table to the specified stream for display purposes.
   */
  void printToStream(std::ostream &s);
  
  
  /**
   * Frees all of the event ids.
   */
  void freeAll();
  
  
private:
  
  //Lookup table of event id descriptors, indexed by event id.
  typedef std::vector<EventIdDescriptor> EvtIds;
  EvtIds evtIds_;
  
  boost::shared_ptr<EoLSHandler> eolsHandler_;

  uint32_t nbEvtIds_;
  uint32_t currentLumiSectionNumber_;

  typedef std::map<uint32_t, uint32_t> LumiSectionMap;
  LumiSectionMap lumiSectionMap_;

  void incrementEventsInRuBuilderForLumiSection(const uint32_t lumiSection);
  void decrementEventsInRuBuilderForLumiSection(const uint32_t lumiSection, const uint32_t runNumber);
  void sendEoLSsignal(const uint32_t runNumber);
  void updateLumiSectionInfo(const uint32_t lumiSection);
  void checkEventId(const std::string &methodName, const uint32_t eventId);

}; // EventIdTable

} } // namespace rubuilder::evm


std::ostream& operator<<
(
  std::ostream                                       &s,
  volatile rubuilder::evm::EventIdTable::EventIdDescriptor &d
);


std::ostream& operator<<
(
  std::ostream           &s,
  rubuilder::evm::EventIdTable &table
);


#endif


/// emacs configuration
/// Local Variables: -
/// mode: c++ -
/// c-basic-offset: 2 -
/// indent-tabs-mode: nil -
/// End: -
