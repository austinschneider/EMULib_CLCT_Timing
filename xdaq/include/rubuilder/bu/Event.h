#ifndef _rubuilder_bu_Event_h_
#define _rubuilder_bu_Event_h_

#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>

#include <map>
#include <stdint.h>

#include "rubuilder/bu/FuRqstForResource.h"
#include "rubuilder/bu/SuperFragmentDescriptor.h"
#include "toolbox/mem/Reference.h"


namespace rubuilder { namespace bu { // namespace rubuilder::bu

  class FUproxy;

  /**
   * \ingroup xdaqApps
   * \brief Represent an event
   */
 
  class Event
  {
  public:

    Event
    (
      const uint32_t ruCount,
      toolbox::mem::Reference*
    );

    ~Event();

    /**
     * Append a super fragment to the event
     */
    void appendSuperFragment(toolbox::mem::Reference*);
    
    /**
     * Return true if all super fragments have been received
     */
    bool isComplete() const;
    
    /**
     * Send the event to the FU specified in the request.
     */
    void sendToFU
    (
      boost::shared_ptr<FUproxy> fuProxy,
      const FuRqstForResource& rqst
    ) const;

    /**
     * Return the buResourceId
     */
    uint32_t buResourceId() const
    { return buResourceId_; }

    /**
     * Return the eventId
     */
    uint32_t eventId() const
    { return eventId_; }

    /**
     * Return the eventNumber
     */
    uint32_t eventNumber() const
    { return eventNumber_; }

    /**
     * Return the payload in Bytes
     */
    size_t payload() const
    { return payload_; }
    
    
  private:
    
    // Map to hold super fragments index by RU instance
    typedef std::map<uint32_t,SuperFragmentDescriptorPtr> Data;
    Data data_;
    mutable boost::mutex mutex_;
    
    const uint32_t nbExpectedSuperFragments_;
    uint32_t nbCompleteSuperFragments_;

    uint32_t buResourceId_;
    uint32_t eventId_;
    uint32_t eventNumber_;
    size_t payload_;
    
  }; // Event
    
  typedef boost::shared_ptr<Event> EventPtr;
  
} } // namespace rubuilder::bu

#endif // _rubuilder_bu_Event_h_


/// emacs configuration
/// Local Variables: -
/// mode: c++ -
/// c-basic-offset: 2 -
/// indent-tabs-mode: nil -
/// End: -
