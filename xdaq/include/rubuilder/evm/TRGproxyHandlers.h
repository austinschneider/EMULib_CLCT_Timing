#ifndef _rubuilder_evm_TRGproxyHandlers_h_
#define _rubuilder_evm_TRGproxyHandlers_h_

#include "rubuilder/evm/TRGproxy.h"
#include "rubuilder/utils/ApplicationDescriptorAndTid.h"
#include "rubuilder/utils/TriggerGenerator.h"
#include "rubuilder/utils/TimerManager.h"


namespace rubuilder { namespace evm { // namespace rubuilder::evm

  namespace TRGproxyHandlers {
    
    class GTPhandler : public Handler
    {
    public:
      
      GTPhandler(TRGproxy* parent) :
      Handler(parent) {}
      
      virtual ~GTPhandler() {};
    };
    
    
    class GTPehandler : public Handler
    {
    public:
      
      GTPehandler(TRGproxy* parent) :
      Handler(parent) {}
      
      virtual ~GTPehandler() {};
      
      virtual void I2Ocallback(toolbox::mem::Reference**) const;

    private:

      utils::TriggerGenerator triggerGenerator_;
    };
    
    
    class TAhandler : public Handler
    {
    public:
      
      TAhandler(TRGproxy* parent);
      virtual ~TAhandler() {};
      
      virtual bool requestTriggers(const uint32_t&);
      virtual bool sendOldTriggerMessage();
      virtual void printHtml(xgi::Output*);
      virtual void reset();
      
    private:
      
      void findTA();
      void sendTrigCredits(const uint32_t&);
      
      uint32_t tid_;
      utils::ApplicationDescriptorAndTid ta_;
      utils::TimerManager timerManager_;
      const uint8_t timerId_;
      uint32_t nbCreditsToBeSent_;
      
      xdata::Boolean foundTA_;
      struct TAMonitoring
      {
        uint64_t triggersRequested;
        uint64_t payload;
        uint64_t i2oCount;
      } taMonitoring_;
    };
    
    
    class DummyTrigger : public Handler
    {
    public:
      
      DummyTrigger(TRGproxy* parent);
      
      virtual ~DummyTrigger() {};
      
      virtual void I2Ocallback(toolbox::mem::Reference**) const;
      virtual bool requestTriggers(const uint32_t&);
      virtual void reset();
      
    private:

      void generateDummyTriggers(const uint32_t&);

      utils::TriggerGenerator triggerGenerator_;
      uint32_t tid_;
      uint32_t eventNumber_;
      
    };
    
  } // namespace TRGproxyHandlers
} } // namespace rubuilder::evm

#endif // _rubuilder_evm_TRGproxyHandlers_h_

/// emacs configuration
/// Local Variables: -
/// mode: c++ -
/// c-basic-offset: 2 -
/// indent-tabs-mode: nil -
/// End: -
