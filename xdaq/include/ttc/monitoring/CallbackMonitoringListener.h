#ifndef _ttc_monitoring_callbackmonitoringlistener_h_
#define _ttc_monitoring_callbackmonitoringlistener_h_


#include "ttc/monitoring/MonitoringListener.h"

#include <sstream>


namespace ttc
{

class ItemSetterSignature
{
public:
  virtual void invoke(
      const Component& component,
      std::ostringstream& value) = 0;

  virtual ~ItemSetterSignature() {}
};


template<class C>
class ItemSetter : public ItemSetterSignature
{
public:
  typedef void (C::*Func)(const Component&, std::ostringstream&);

  ItemSetter(C* obj, Func f) : obj_(obj), f_(f)
  {
    if (!obj_ || !f_)
    {
      XCEPT_RAISE(xcept::Exception, "Undefined obj_ or f_");
    }
  }

  virtual void invoke(
      const Component& component,
      std::ostringstream& value)
  {
    (obj_->*f_)(component, value);
  }

private:
  C* obj_;
  Func f_;
};


/**
 * This class is a Monitoring listener (with a user defined list of identical monitored components),
 * where the monitoring items for each component are registered with individual callbacks.
 */
class CallbackMonitoringListener : public MonitoringListener
{
public:

  CallbackMonitoringListener(
      xdaq::Application* app,
      const std::string& infospaceBaseName,
      bool autoInit,
      const double& autoRefreshPeriodSecs,
      const double& autoRefreshTimeGridOffsetSecs,
      const double& autoRefreshForcedPeriodSecs = 600.0);

  virtual ~CallbackMonitoringListener();

protected:

  /**
   * Defines an item and a corresponding refresh-callback, which gets called for all defined components.
   *
   * NOTE: For a given component, the order in which items are updated
   * corresponds to the order in which they are added by this method.
   * (This can be exploited if the update action for some item depends on a prior update of some other item.)
   */
  template<class T, class C>
  void addItemAndCallback(const std::string& name,
      C* obj,
      typename ItemSetter<C>::Func f)
  {
    MonitoringListener::addItem<T>(name);
    ItemSetter<C>* s = new ItemSetter<C>(obj, f);
    callbackItemNames_.push_back(name);
    mapCallbackItemNameToItemSetter_[name] = s;
  }

private:

  //! implements ttc::MonitoringListener::refreshItems
  virtual bool refreshItems(const Component& component);

  std::list<std::string> callbackItemNames_;
  std::map<std::string, ItemSetterSignature*> mapCallbackItemNameToItemSetter_;
};

}


#endif
