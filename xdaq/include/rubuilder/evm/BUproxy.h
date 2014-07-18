#ifndef _rubuilder_evm_BUproxy_h_
#define _rubuilder_evm_BUproxy_h_

#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <set>
#include <stdint.h>
#include <string>
#include <utility>

#include "i2o/i2oDdmLib.h"
#include "log4cplus/logger.h"

#include "interface/evb/i2oEVBMsgs.h"
#include "rubuilder/evm/EventIdTable.h"
#include "rubuilder/utils/InfoSpaceItems.h"
#include "rubuilder/utils/OneToOneQueue.h"
#include "rubuilder/utils/OneToOneQueueCollection.h"
#include "toolbox/mem/Reference.h"
#include "xdaq/Application.h"
#include "xdata/Boolean.h"
#include "xdata/Serializable.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/UnsignedInteger64.h"
#include "xgi/Output.h"


namespace rubuilder { namespace evm { // namespace rubuilder::evm

  class EoLSHandler;

  /**
   * \ingroup xdaqApps
   * \brief Proxy for EVM-BU communication
   */
  
  class BUproxy
  {
    
  public:

    struct PairFifoElement
    {
      toolbox::mem::Reference *trigBufRef;
      uint32_t evtId;
      uint32_t eventNumber;
      uint32_t runNumber;
      uint32_t lumiSection;
    };

    struct RqstFifoElement
    {
      I2O_TID buTid;
      uint32_t buIndex;
      uint32_t resourceId;
    };
    
    struct ReleasedEvtIdFifoElement
    {
      uint32_t eventId;
      uint32_t eventNumber;
      uint32_t buIndex;
      uint32_t resourceId;
    };


    BUproxy
    (
      xdaq::Application*,
      boost::shared_ptr<EoLSHandler>,
      toolbox::mem::Pool*
    );

    virtual ~BUproxy() {};

    /**
     * Callback for I2O message received from BU
     */
    void I2Ocallback(toolbox::mem::Reference*);

    /**
     * Add the PairFifoElement to the pair message queue
     * for the BU. If there's a request from the BU,
     * use it to satisfy the request.
     */
    void addPair(const PairFifoElement&);

    /**    
     * Service a single BU request if possible.
     * Returns true if an event was served.
     */
    bool serviceBuRqst();

    /**
     * Process the next released event. Return true if an 
     * event was released. In this case, the clearedEventId
     * contains the corresponding event id.
     */
    bool processNextReleasedEvent(uint32_t& clearedEventId);

    /**
     * Append the info space parameters used for the
     * configuration to the InfoSpaceItems
     */
    void appendConfigurationItems(utils::InfoSpaceItems&);
    
    /**
     * Append the info space items to be published in the 
     * monitoring info space to the InfoSpaceItems
     */
    void appendMonitoringItems(utils::InfoSpaceItems&);
    
    /**
     * Update all values of the items put into the monitoring
     * info space. The caller has to make sure that the info
     * space where the items reside is locked and properly unlocked
     * after the call.
     */
    void updateMonitoringItems();
    
    /**
     * Reset the monitoring counters
     */
    void resetMonitoringCounters();
  
    /**
     * Configure
     */
    void configure(const uint32_t nbEvtIdsInBuilder);

    /**
     * Remove all data
     */
    void clear();

    /**
     * Find the application descriptors of the participating BUs
     */
    void getApplicationDescriptors();

    /**
     * Send the end-of-lumi-section message to all BUs.
     */
    void sendEoLSmsg(I2O_EVM_END_OF_LUMISECTION_MESSAGE_FRAME*);

    /**
     * Return the logical count of confirm messages sent to the BUs
     */
    inline uint64_t getConfirmLogicalCount() const
    { return confirmCounters_.logicalCount; }

    /**
     * Print monitoring/configuration as HTML snipped
     */
    void printHtml(xgi::Output*);

    /**
     * Print the content of the pair FIFO as HTML snipped
     */
    inline void printPairFIFO(xgi::Output* out)
    { pairFIFO_.printVerticalHtml(out); }

    /**
     * Print the content of the request FIFO as HTML snipped
     */
    inline void printRequestFIFOs(xgi::Output* out)
    { requestFIFOs_.printVerticalHtml(out); }

    /**
     * Print the content of the released event id FIFO as HTML snipped
     */
    inline void printReleasedEventIdFIFO(xgi::Output* out)
    { releasedEventIdFIFO_.printVerticalHtml(out); }


  private:

    void updateParticipatingBUs(const I2O_TID&);
    void pushRequestOntoFIFOs(const EvtIdRqstsAndOrReleasesMsg*, const I2O_TID&);
    void requestEvent(const RqstFifoElement&);
    void releaseEvent(const ReleasedEvtIdFifoElement&);
    void updateAllocateClearCounters(const uint32_t& nbElements);
    void updateConfirmCounters(const I2O_MESSAGE_FRAME*);

    xdaq::Application* app_;
    EventIdTable evtIdTable_;
    toolbox::mem::Pool* fastCtrlMsgPool_;
    log4cplus::Logger& logger_;
    uint32_t tid_;

    typedef utils::OneToOneQueue<PairFifoElement> PairFIFO;
    PairFIFO pairFIFO_;

    typedef utils::OneToOneQueueCollection<RqstFifoElement> RequestFIFOs;
    RequestFIFOs requestFIFOs_;

    typedef utils::OneToOneQueue<ReleasedEvtIdFifoElement> ReleasedEventIdFIFO;
    ReleasedEventIdFIFO releasedEventIdFIFO_;

    typedef std::set<I2O_TID> ParticipatingBUs;
    ParticipatingBUs participatingBUs_;
    mutable boost::mutex participatingBUsMutex_;

    struct AllocateClearCounters
    {
      uint64_t payload;
      uint64_t logicalCount;
      uint64_t i2oCount;
    } allocateClearCounters_;
    mutable boost::mutex allocateClearCountersMutex_;

    struct ConfirmCounters
    {
      uint64_t payload;
      uint64_t logicalCount;
      uint64_t i2oCount;
      uint32_t lastEventNumberToBUs;
    } confirmCounters_;
    mutable boost::mutex confirmCountersMutex_;

    struct EoLSMonitoring
    {
      uint64_t payload;
      uint64_t msgCount;
      uint64_t i2oCount;
    } EoLSMonitoring_;
    mutable boost::mutex EoLSMonitoringMutex_;
    
    utils::InfoSpaceItems buParams_;
    xdata::UnsignedInteger32 requestFIFOCapacity_;
    xdata::Boolean assignRoundRobin_;
    
    xdata::UnsignedInteger32 lastEventNumberToBUs_;
    xdata::UnsignedInteger64 i2oEVMAllocClearCount_;
    xdata::UnsignedInteger64 i2oBUConfirmLogicalCount_;

  };

  inline std::ostream& operator<< (std::ostream& s, const BUproxy::PairFifoElement& element)
  {
    s << "trigBufRef=" << element.trigBufRef << " ";
    s << "evtId="      << (int)(element.evtId);
    
    return s;
  }
    
  inline std::ostream& operator<< (std::ostream& s, const BUproxy::RqstFifoElement& element)
  {
    s << "buTid="      << element.buTid   << " ";
    s << "buIndex="    << element.buIndex << " ";
    s << "resourceId=" << element.resourceId;
    
    return s;
  }

  inline std::ostream& operator<< (std::ostream& s, const BUproxy::ReleasedEvtIdFifoElement& element)
  {
    s << "eventId="     << (int)(element.eventId)     << " ";
    s << "eventNumber=" << (int)(element.eventNumber) << " ";
    s << "buIndex="     << (int)(element.buIndex)     << " ";
    s << "resourceId="  << (int)(element.resourceId);
    
    return s;
  }

} } // namespace rubuilder::evm



#endif // _rubuilder_evm_BUproxy_h_

/// emacs configuration
/// Local Variables: -
/// mode: c++ -
/// c-basic-offset: 2 -
/// indent-tabs-mode: nil -
/// End: -
