#ifndef _ttc_monitoring_monitoringlistener_h_
#define _ttc_monitoring_monitoringlistener_h_


#include "ttc/monitoring/InfoSpaceLock.h"
#include "ttc/monitoring/Component.h"

#include "xdata/InfoSpace.h"
#include "toolbox/task/TimerListener.h"
#include "log4cplus/logger.h"
#include "xcept/Exception.h"

#include <string>
#include <list>
#include <set>


XCEPT_DEFINE_EXCEPTION(ttc, MonitoringComponentNotAccessible);


#define TRY_CATCH_ALL(x) \
  try { x; } \
  catch (ttc::exception::MonitoringComponentNotAccessible& e) \
  { /* that's fine, we ignore */ } \
  catch (xdata::exception::Exception& e) \
  { LOG4CPLUS_ERROR(getLogger(), "Failed to " #x ": "+ xcept::stdformat_exception_history(e)); } \
  catch (xcept::Exception& e) \
  { LOG4CPLUS_ERROR(getLogger(), "Failed to " #x ": "+ xcept::stdformat_exception_history(e)); } \
  catch (std::exception& e) \
  { LOG4CPLUS_ERROR(getLogger(), "Failed to " #x ": "+ std::string(e.what())); } \
  catch (...) \
  { LOG4CPLUS_ERROR(getLogger(), "Failed to " #x ": unknown exception"); }


namespace xdata
{
class Serializable;
class InfoSpace;
}

namespace xdaq
{
class Application;
}

namespace toolbox
{
namespace task { class Timer; }
}


namespace ttc
{

class MonitoringListener
:
  public xdata::ActionListener,
  public toolbox::task::TimerListener
{

public:

  /**
   * Constructs a MonitoringListener for XDAQ application app.
   *
   * When autoInit==true, this must be called in the CTOR of app,
   *   and initialization takes place after the CTOR finishes, on event 'setDefaultValues'.
   * When autoInit==false, this can be called at any time,
   *   and the user code must call init() explicitly,
   *   at a point where addComponents() has access to the list of QPLLs to be added.
   *
   * The status of components is updated at regular intervals.
   *
   *
   * autoRefreshPeriodSecs defines the refresh period.
   * autoRefreshTimeGridOffsetSecs defines a global time offset for the regular update actions.
   *
   * Normally only those components with changes fire an update in the monitoring system.
   * However, at regular intervals such an update is enforced; this interval can be defined by autoRefreshForcedPeriodSecs
   *
   * Monitoring items are connected to XMAS infospace items:
   *   For each component there is one infospace (all these infospaces have a common base name given by infospaceBaseName)
   *   For each item of a component there is a corresponding item of the infospace.
   */
  MonitoringListener(
      xdaq::Application* app,
      const std::string& infospaceBaseName,
      bool autoInit,
      const double& autoRefreshPeriodSecs,
      const double& autoRefreshTimeGridOffsetSecs,
      const double& autoRefreshForcedPeriodSecs);

  virtual ~MonitoringListener();

  /**
   * Initializes and starts monitoring.
   */
  void init();

  /**
   * Gets ttc::InfoSpaceLock for xdata::InfoSpace corresponding to componentKey.
   * USAGE HINT:
   *   { ttc::InfoSpaceLockHandler h(mon.infoSpaceLock(componentKey)); mycode(); }
   */
  InfoSpaceLock infoSpaceLock(const std::string& componentKey);

  /**
   * Gets pointer to cloned item (caller takes ownership).
   * Throws if given item is not of type T.
   */
  template<class T>
  T* getItemClone(const std::string& componentKey, const std::string& name)
  {
    InfoSpaceLockHandler h(infoSpaceLock(componentKey));
    T& item= dynamic_cast<T&>(*getItem(componentKey, name));
    return new T(item);
  }

  //! Returns the value of a given item as a string.
  std::string getItemString(const std::string& componentKey, const std::string& name);

  /**
   * Sets item value for given component.
   * Returns true, if value changed, false if not.
   * To fire "item changed", pushComponent().
   * NOTE: Lock infoSpace_ during usage.
   */
  bool setItem(
      const std::string& componentKey, 
      const std::string& name, 
      const xdata::Serializable& value);

  /**
   * Sets item value from a string, for given component.
   * Returns true, if value changed, false if not.
   * To fire "item changed", pushComponent().
   * NOTE: Lock infoSpace_ during usage.
   */
  bool setItemFromString(
      const std::string& componentKey,
      const std::string& name,
      const std::string& value);

  /**
   * Fires "item changed" for all items of given component.
   * NOTE: Lock InfoSpace during usage.
   */
  void pushComponent(const std::string& componentKey);

protected:

  //! gets the XDAQ application that
  xdaq::Application& getApp();

  /**
   * Placeholder for adding components to be monitored.
   * IMPLEMENT THIS TO DEFINE YOUR SET OF COMPONENTS TO BE MONITORED:
   *   use addComponent(group, system, localID) statements
   */
  virtual void addComponents() = 0;

  /**
   * Placeholder for adding items to be monitored for each component;
   * IMPLEMENT THIS TO DEFINE YOUR LIST OF ITEMS TO BE MONITORED FOR EACH OF YOUR COMPONENTS:
   *   use addItem<T>("myitem") statements
   * NOTE: base items (Timestamp, URL, URN, ComponentKey) are added automatically
   */
  virtual void addItems() = 0;

  /**
   * Virtual method refreshing all items for given component.
   * IMPLEMENT THIS TO DEFINE HOW TO UPDATE MONITORED ITEMS FOR GIVEN COMPONENT
   * NOTE: infospace is locked during this operation
   *       exceptions caught during this operation;
   *       use setItem(componentKey, item, value) statements;
   *       return true if pushComponent() should be triggered after this operation
   *       (normally if any of the components' items changed - check return values of setItem);
   *       base items (Timestamp, URL, URN, ComponentKey) are refreshed automatically
   */
  virtual bool refreshItems(const Component& component) = 0;

  /**
   * Adds a new component to be monitored.
   * Returns component key.
   */
  std::string addComponent(
      const std::string& group,
      const std::string& system,
      const std::string& localID);

  /**
   * Adds a new item to be monitored for all components
   * (fires "item available" for corresponding InfoSpaces).
   * Takes ownership of items.
   */
  template<class T>
  void addItem(const std::string& name)
  {
    const std::vector<std::string>& vecComponentKeys = componentColl_.getComponentKeys();

    for (std::vector<std::string>::const_iterator
        it = vecComponentKeys.begin();
        it!= vecComponentKeys.end(); ++it)
    {
      const std::string& componentKey = *it;
      xdata::InfoSpace* infoSpace = getInfoSpace(componentKey);

      InfoSpaceLock lock(infoSpace);
      InfoSpaceLockHandler h(lock);

      infoSpace->fireItemAvailable(name, new T, this);
    }

    // add item to list of item names
    itemNames_.push_back(name);
  }
  
  //! gets reference to logger
  log4cplus::Logger& getLogger();

private:

  xdaq::Application* app_;

  std::string infoSpaceBaseName_;

  mutable bool initAlreadyCalled_;

  std::map<std::string, xdata::InfoSpace*> mapComponentKeyToInfoSpace_;

  log4cplus::Logger logger_;

  ComponentCollection componentColl_;

  std::list<std::string> itemNames_;

  double autoRefreshPeriodSecs_;

  double autoRefreshTimeGridOffsetSecs_;

  double autoRefreshForcedPeriodSecs_;

  double lastAutoRefreshForcedSecs_;

  double initTimeSecs_;

  double initialMonitoringDelaySecs_;

  std::string timerName_;

  toolbox::task::Timer* timer_;


  /**
   * IMPLEMENTS xdata::ActionListener::actionPerformed.
   * Calls init() on setDefaultValues event from user application's infospace.
   */
  virtual void actionPerformed(xdata::Event& e);

  //! gets InfoSpace for given component
  xdata::InfoSpace* getInfoSpace(const std::string& componentKey);

  //! adds base items to InfoSpace (Timestamp, URL, URN, ComponentKey)
  void addBaseItems();

  //! refreshes base items for given component
  void refreshBaseItems(const Component& component);

  //! Gets pointer to given item.
  xdata::Serializable* getItem(const std::string& componentKey, const std::string& name);

  /**
   * IMPLEMENTS toolbox::task::TimerListener::timeExpired.
   * Locks infospace and calls refreshComponents() and scheduleNextRefresh(), catching all exceptions.
   */
  virtual void timeExpired(toolbox::task::TimerEvent& e);
  
  //! Refreshes monitoring data (base items and user items) for each component.
  void refreshComponents(bool force);

  //! Schedules nearest future event in global time grid [1970 + n*autoRefreshPeriodSecs_].
  void scheduleNextRefresh();
};

}


#endif
