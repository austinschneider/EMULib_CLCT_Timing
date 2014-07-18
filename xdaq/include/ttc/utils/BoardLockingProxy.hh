#ifndef _ttc_utils_BoardLockingProxy_hh_
#define _ttc_utils_BoardLockingProxy_hh_


#include "ttc/utils/BoardProxy.hh"

#include "xcept/Exception.h"


namespace ttc
{

/**
 * Class template BoardTempLocker.
 *
 * The CTOR takes a reference to a BoardProxy.
 * The operator->() takes the BoardProxy's mutex and returns the BoardProxy::ptr() casted to a T*.
 * The DTOR releases the lock, if taken.
 *
 * Descendants of BoardProxy may in turn overload operator->() to return a BoardTempLocker<T>,
 * which then, by the operator->() chaining rule, returns the T*.
 * (The temporary BoardTempLocker<T> goes out of scope, and unlocks,
 * when the T method invocation has finished.)
 */
template<typename T>
class BoardTempLocker
{
public:

  explicit BoardTempLocker(BoardProxy& p)
  : p_(p), locked_(false)
  {}

  ~BoardTempLocker()
  {
    if (locked_)
    {
      BoardProxy::getMutex().unlock();
    }
  }

  T* operator->()
  {
    BoardProxy::getMutex().lock();
    locked_ = true;

    if (T* ptr = dynamic_cast<T*>(p_.ptr()))
      return ptr;

    XCEPT_RAISE(
        xcept::Exception,
        "Casting board object to template type failed");
  }

private:

  BoardProxy& p_;
  bool locked_;
};


// forward declaration
class GenericTTCModule;


//! proxy class managing resources for talking to a GenericTTCModule
class BoardLockingProxy : public BoardProxy
{
public:
  BoardTempLocker<GenericTTCModule> operator->();
};

}


#endif
