#ifndef _IPCUTILS_SEMAPHOREARRAY_H
#define _IPCUTILS_SEMAPHOREARRAY_H

/**
 *     @class SemaphoreArray
 *
 *     @short System V IPC Semaphore Array for inter-process communication
 *
 *            The implementation uses a system-wide semaphore array.
 *            The lock can therefore be used by different applications 
 *            running on the same host.
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:34 $
 *
 *
 **/

#include "xcept/Exception.h"

#include <string>
#include <stdint.h>

// define a new exception definition macro. The one in xcept does not work.
#define DEFINE_EXCEPTION1(NAMESPACE1, EXCEPTION_NAME) \
namespace NAMESPACE1 { \
namespace exception { \
class EXCEPTION_NAME: public xcept::Exception \
{\
	public: \
	EXCEPTION_NAME( std::string name, std::string message, std::string module, int line, std::string function ): \
		xcept::Exception(name, message, module, line, function) \
	{}; \
	EXCEPTION_NAME( std::string name, std::string message, std::string module, int line, std::string function, xcept::Exception& previous ): \
		xcept::Exception(name, message, module, line, function, previous) \
	{}; \
}; \
} \
}

// also define an expection definition macro with a parent exception
#define DEFINE_EXCEPTION1_P(NAMESPACE1, EXCEPTION_NAME, PARENT_NAME) \
namespace NAMESPACE1 { \
namespace exception { \
class EXCEPTION_NAME: public NAMESPACE1::exception::PARENT_NAME \
{\
	public: \
	EXCEPTION_NAME( std::string name, std::string message, std::string module, int line, std::string function ): \
		NAMESPACE1::exception::PARENT_NAME(name, message, module, line, function) \
	{}; \
	EXCEPTION_NAME( std::string name, std::string message, std::string module, int line, std::string function, xcept::Exception& previous ): \
		NAMESPACE1::exception::PARENT_NAME(name, message, module, line, function, previous) \
	{}; \
}; \
} \
}



DEFINE_EXCEPTION1(ipcutils, Exception);
DEFINE_EXCEPTION1_P(ipcutils, OutOfRange, Exception);
DEFINE_EXCEPTION1_P(ipcutils, NoExist, Exception);

#define DEFAULT_PROJECTID 't'

namespace ipcutils {

  class SemaphoreArray {

  public:
    /// c-tor
    ///
    /// @key_file is the name of an existing file in the file system used to identify the semaphore array
    ///
    /// @param projectId is the project ID used in the generation of a unique key to identify
    ///        the semaphore array. 
    ///
    /// @param doCreate is true to create the semaphore array ( only if it does not exist ),
    ///        if doCreate is false, a NoExist exception is thrown if the semaphore array does not exist
    /// 
    /// @param nsem gives the number of semaphores to create (if doCreate is true)
    /// 
    ///        
    SemaphoreArray(const char* keyFile, char projectId, bool doCreate = false, uint32_t nsem = 0)
      throw (ipcutils::exception::NoExist,
	     ipcutils::exception::Exception);

    /// d-tor
    ///
    /// release all locks acquired as a safeguard against stale locks??
    ~SemaphoreArray();


    /// Check if one of the semas is locked
    /// 
    /// @param isem is the index of the semaphore in the array
    ///
    bool isLocked(uint32_t isem)
      throw (ipcutils::exception::OutOfRange,
	     ipcutils::exception::Exception);

    /// Check info on the lock. 
    /// 
    /// returns the PID of the process that last modified the semaphore
    /// 
    /// @param isem is the index of the semaphore in the array
    ///
    uint32_t getPID(uint32_t isem)
      throw (ipcutils::exception::OutOfRange,
	     ipcutils::exception::Exception);


    /// Obtain lock for a semaphore if it is unlocked.
    ///
    /// returns true if successful, false if not.
    ///
    /// @param isem is the index of the semaphore in the array
    ///
    bool takeIfUnlocked(uint32_t isem)
      throw (ipcutils::exception::OutOfRange,
	     ipcutils::exception::Exception);


    /// Obtain lock for a semaphore. Wait indefinitely if it is already locked.
    ///
    /// @param isem is the index of the semaphore in the array
    ///
    void take(uint32_t isem)
      throw (ipcutils::exception::OutOfRange,
	     ipcutils::exception::Exception);

    /// Obtain lock for a semaphore. Wait for timeout seconds if it is already locked.
    ///
    /// @param isem is the index of the semaphore in the array
    /// @param timeout_sec is the number of seconds to wait for the lock
    ///
    /// returns true if the lock was obtained, false if a timeout occured
    ///
    bool takeTimed(uint32_t isem, uint32_t timeout_sec)
      throw (ipcutils::exception::OutOfRange,
	     ipcutils::exception::Exception);


    /// Release lock for a semaphore.
    ///
    /// @param isem is the index of the semaphore in the array
    ///
    void give(uint32_t isem)
      throw (ipcutils::exception::OutOfRange,
	     ipcutils::exception::Exception);


    /// create the system-wide semaphore array
    ///
    /// to be used e.g. in a startup script
    static void createLocks(const char* keyFile, char projectId, uint32_t nsem)
      throw (ipcutils::exception::Exception);
  
    /// destroy the system-wide semaphore array
    ///
    /// to be used e.g. in a maintenace utility
    static void destroyLocks(const char* keyFile, char projectId)
      throw (ipcutils::exception::NoExist,
	     ipcutils::exception::Exception);

  
    /// reset the system-wide semaphore array to unlocked
    ///
    /// to be used e.g. in a maintenace utility
    static void resetLocks(const char* keyFile, char projectId, uint32_t nsem)
      throw (ipcutils::exception::NoExist,
	     ipcutils::exception::Exception);

  protected:
    /// get the semaphore array
    ///
    /// @param doCreate is true to create the semaphore array if it does not exist,
    ///        if doCreate is false, a NoExist exception is thrown if the semaphore array does not exist
    /// 
    /// @param project id is the project ID sued to create the token
    static int getSema(const char* keyFile, char projectId, bool doCreate, uint32_t nsem)
      throw (ipcutils::exception::NoExist,
	     ipcutils::exception::Exception);
  
    /// reset the system-wide semaphore array to unlocked
    ///
    /// @param sid is the semaphore ID
    static void resetSemaphores(int sid, uint32_t nsem)
      throw (ipcutils::exception::Exception);
  private:
    int _sid;
    uint32_t _nsem;
  };
  
}
#endif

