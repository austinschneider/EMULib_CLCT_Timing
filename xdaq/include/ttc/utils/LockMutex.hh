#ifndef _ttc_utils_LockMutex_hh_
#define _ttc_utils_LockMutex_hh_


#include <pthread.h>


namespace ttc
{

/**
 * Class implementing a mutual-exclusion semaphore.
 * This serves the purpose of synchronization of concurring threads.
 */
class Mutex
{
public:

  //! constructs a mutex; if recursive, the same thread may lock a mutex more than once
  Mutex(bool recursive = false);

  ~Mutex();

  /**
   * If (recursive) mutex is locked (by a different thread) then waits until mutex gets unlocked;
   * else locks the mutex and continues.
   */
  void lock();

  //! unlocks the mutex (after being previously locked by the same thread)
  void unlock();

private:

  pthread_mutex_t mutex_;
  pthread_mutexattr_t attr_;

  //! private copy constructor - prevent copying
  Mutex(const Mutex&);

  // private copy assignment operator - prevent copying
  Mutex& operator=(const Mutex&);
};


/**
 * Class implementing the "Resource Acquisition Is Initialization" (RAII) idiom for a ttc::Mutex.
 * This allows to define a critical section to be thread-synchronized (initially locked and finally unlocked)
 * as the scope of an instance of this class.
 */
class MutexHandler
{
public:

  //! locks the passed @param mutex
  MutexHandler(Mutex& mutex);

  //! unlocks the mutex a reference to which was passed on construction
  ~MutexHandler();

private:

  //! reference to the mutex being handled by this MutexHandler
  Mutex& mutex_;

  //! private copy constructor - prevent copying
  MutexHandler(const MutexHandler&);

  // private copy assignment operator - prevent copying
  MutexHandler& operator=(const MutexHandler&);
};

}


#endif
