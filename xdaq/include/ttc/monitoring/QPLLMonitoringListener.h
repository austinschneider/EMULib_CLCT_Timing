#ifndef _ttc_monitoring_qpllmonitoringlistener_h_
#define _ttc_monitoring_qpllmonitoringlistener_h_


#include "ttc/monitoring/MonitoringListener.h"

#include <string>


namespace ttc
{

typedef enum {QPLLLocked, QPLLUnlocked, QPLLUndefined, QPLLNotAvailable} QPLLLockingState;

class QPLLMonitoringListener : public MonitoringListener
{

public:

  /**
   * Constructs a QPLLMonitoringListener for XDAQ application app.
   *
   * When autoInit==true, this must be called in the CTOR of app,
   *   and initialization takes place after the CTOR finishes, on event 'setDefaultValues'.
   * When autoInit==false, this can be called at any time,
   *   and the user code must call init() explicitly,
   *   at a point where addComponents() has access to the list of QPLLs to be added.
   * NOTE:
   *   It is recommended to define the complete list of QPLLs independently of the system configuration,
   *   and to use autoInit==true.
   *   However, if you can't easily define the list a priori, you may use autoInit==false.
   *
   * autoRefreshPeriodSecs defines the period for refreshing the status of the QPLLs.
   * autoRefreshTimeGridOffsetSecs defines a global time offset for the regular refresh actions.
   * NOTE:
   *   Please don't change the defaults without good reason.
   */
  QPLLMonitoringListener(
      xdaq::Application* app,
      bool autoInit = true,
      const double& autoRefreshPeriodSecs = 30.0,
      const double& autoRefreshTimeGridOffsetSecs = 0.0);

protected:

  /**
   * Sets list of QPLLs to be monitored.
   * Implement this to define the set of QPLLs for monitoring within an XDAQ application of your system:
   *   use addComponent(group, system, localID) statements.
   * Ideally this is the complete (maximum) set:
   *   temporary non-availability of a QPLL can be signalled in setQPLLLockingState.
   */
  virtual void addComponents() = 0;

  /**
   * Implement this (REQUIRED):
   * set the _current_ QPLL locking state for a given component.
   *    -  set to ttc::QPLLNotAvailable if QPLL cannot be monitored at this moment; else:
   *    -  set to ttc::QPLLUndefined    if QPLL state is undefined or irrelevant at this moment
   *                                    (e.g. because your component is using internal clock,
   *                                     or some upstream clock node is known to be unstable);
   *    -  set to ttc::QPLLLocked       if QPLL is in Locked state at this moment; else:
   *    -  set to ttc::QPLLUnlocked     if QPLL is in Unlocked state at this moment.
   */
  virtual void setQPLLLockingState(const Component& component, QPLLLockingState& qpllLockingState) = 0;

  /**
   * Implement this (OPTIONAL):
   * set the _latched_ QPLL locking state for a given component.
   *    -  set to ttc::QPLLNotAvailable if QPLL cannot be monitored at this moment; else:
   *    -  set to ttc::QPLLUndefined    if QPLL state is undefined or irrelevant at this moment
   *                                    (e.g. because your component is using internal clock,
   *                                     or some upstream clock node is known to be unstable);
   *    -  set to ttc::QPLLLocked       if QPLL was permanently in Locked state between the last and the current update; else:
   *    -  set to ttc::QPLLUnlocked     if QPLL was in Unlocked state at some point between the last and the current update.
   */
  virtual void setQPLLLockingStateLatched(const Component& component, QPLLLockingState& qpllLockingStateLatched);

private:

  //! implements ttc::MonitoringListener::addItems
  virtual void addItems();

  //! implements ttc::MonitoringListener::refreshItems
  virtual bool refreshItems(const Component& component);

  //! converts QPLLLockingState to string
  std::string getStringFromState(QPLLLockingState s);
};

}


#endif
