#ifndef _rubuilder_ru_InputHandler_h_
#define _rubuilder_ru_InputHandler_h_

#include <boost/thread/mutex.hpp>

#include <stdint.h>
#include <vector>

#include "i2o/shared/i2omsg.h"
#include "rubuilder/ru/SuperFragmentGenerator.h"
#include "rubuilder/utils/OneToOneQueue.h"
#include "toolbox/mem/Pool.h"
#include "toolbox/mem/Reference.h"
#include "xdaq/Application.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/Vector.h"
#include "xgi/Output.h"


namespace rubuilder { namespace ru { // namespace rubuilder::ru

  class InputHandler
  {
  public:

    InputHandler(xdaq::Application* app) :
    app_(app) {};

    virtual ~InputHandler() {};
    
    /**
     * Callback for I2O message received from frontend
     */
    virtual void I2Ocallback(toolbox::mem::Reference*) = 0;

    /**
     * Fill the next complete super fragment into the Reference.
     * If no super fragment is ready, it returns false.
     */
    virtual bool getData(const uint32_t eventNumber, toolbox::mem::Reference*&) = 0;

    /**
     * Configure
     */
    virtual void configure
    (
      const uint32_t blockFIFOCapacity,
      const bool dropInputData,
      const uint32_t dummyBlockSize,
      const uint32_t dummyFedPayloadSize,
      xdata::Vector<xdata::UnsignedInteger32>& fedSourceIds
    ) {};
    
    /**
     * Remove all data
     */
    virtual void clear() {};
  
    /**
     * Print monitoring information as HTML snipped
     */
    virtual void printHtml(xgi::Output*) = 0;
    
    /**
     * Return the last event number seen
     */
    inline uint32_t lastEventNumber() const
    { return inputMonitoring_.lastEventNumber; }
    
    /**
     * Return the number of received event fragments
     * since the last call to resetMonitoringCounters
     */
    inline uint64_t fragmentsCount() const
    { return inputMonitoring_.logicalCount; }
    
    /**
     * Reset the monitoring counters
     */
    inline void resetMonitoringCounters()
    {
      boost::mutex::scoped_lock sl(inputMonitoringMutex_);
      
      inputMonitoring_.payload = 0;
      inputMonitoring_.logicalCount = 0;
      inputMonitoring_.i2oCount = 0;
      inputMonitoring_.lastEventNumber = 0;
    }

  protected:

    xdaq::Application* app_;

    struct InputMonitoring
    {
      uint64_t logicalCount;
      uint64_t payload;
      uint64_t i2oCount;
      uint32_t lastEventNumber;
    } inputMonitoring_;
    mutable boost::mutex inputMonitoringMutex_;
  };


  class FBOproxy : public InputHandler
  {
  public:
    
    FBOproxy(xdaq::Application*);
    virtual ~FBOproxy() {};

    virtual void I2Ocallback(toolbox::mem::Reference*);
    virtual bool getData(const uint32_t eventNumber, toolbox::mem::Reference*&);
    virtual void configure
    (
      const uint32_t blockFIFOCapacity,
      const bool dropInputData,
      const uint32_t dummyBlockSize,
      const uint32_t dummyFedPayloadSize,
      xdata::Vector<xdata::UnsignedInteger32>& fedSourceIds
    );
    virtual void clear();
    virtual void printHtml(xgi::Output*);

  private:
    
    void updateInputCounters(const I2O_MESSAGE_FRAME*);
    void appendBlockToSuperFragment(toolbox::mem::Reference*);
    void handleCompleteSuperFragment();

    typedef utils::OneToOneQueue<toolbox::mem::Reference*> BlockFIFO;
    BlockFIFO blockFIFO_;
    bool dropInputData_;

    toolbox::mem::Reference* superFragmentHead_;
    toolbox::mem::Reference* superFragmentTail_;
  };


  class DummyInputData : public InputHandler
  {
  public:
    
    DummyInputData(xdaq::Application*);
    virtual ~DummyInputData() {};

    virtual void I2Ocallback(toolbox::mem::Reference*);
    virtual bool getData(const uint32_t eventNumber, toolbox::mem::Reference*&);
    virtual void configure
    (
      const uint32_t blockFIFOCapacity,
      const bool dropInputData,
      const uint32_t dummyBlockSize,
      const uint32_t dummyFedPayloadSize,
      xdata::Vector<xdata::UnsignedInteger32>& fedSourceIds
    );
    virtual void printHtml(xgi::Output*);

  private:
    
    toolbox::mem::Reference* generateDummySuperFrag(const uint32_t eventNumber);
    void setNbBlocksInSuperFragment
    (
      toolbox::mem::Reference*,
      const uint32_t nbBlocks
    );

    toolbox::net::URN poolURN_;
    rubuilder::ru::SuperFragmentGenerator superFragGenerator_;
    toolbox::mem::Pool* dummySuperFragmentPool_;
    uint32_t dummyBlockSize_;
    uint32_t dummyFedPayloadSize_;
    std::vector<uint32_t> fedSourceIds_;
    
    uint64_t numberOfSuperFragmentsGenerated_;
  };
  
  
} } //namespace rubuilder::ru

#endif // _rubuilder_ru_InputHandler_h_

/// emacs configuration
/// Local Variables: -
/// mode: c++ -
/// c-basic-offset: 2 -
/// indent-tabs-mode: nil -
/// End: -
