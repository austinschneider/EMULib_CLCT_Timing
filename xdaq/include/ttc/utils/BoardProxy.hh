#ifndef _ttc_utils_BoardProxy_hh_
#define _ttc_utils_BoardProxy_hh_


#include "ttc/utils/LockMutex.hh"

#include "log4cplus/logger.h"
#include "xcept/Exception.h"

#include <string>


namespace HAL
{
class VMEBusAdapterInterface;
}


//! BoardProxy exception for when an access attempt is made but defining params have not yet been passed
XCEPT_DEFINE_EXCEPTION(ttc, BoardProxyParamsNotInited);


namespace ttc
{

// forward declarations
class GenericTTCModule;

/**
 * A class representing a proxy object to the interface of a GenericTTCModule
 * that is managed by a TTCXDAQBase application.
 */
class BoardProxy
{
template<typename T> friend class BoardTempLocker;

// static
private:

  static ttc::Mutex mutex_;

public:

  static ttc::Mutex& getMutex();

// members
public:

  //! constructs BoardProxy, with board resource acquisition parameters declared uninitialized
  BoardProxy();

  //! frees up hardware access resources
  virtual ~BoardProxy();

  //! sets hardware access parameters that are common to all GenericTTCModule descendants
  void initHardwareAccessParams(
      const std::string& busAdapterName,
      const int boardSlot,
      const bool enableVMEWrite);

  /**
   *  Declares that all hardware access parameters (including ones defined in subclasses) have been set,
   *  i.e. subsequent access requests may succeed.
   */
  void setParamsInited();

  /**
   * Returns name of bus adapter currently in use.
   * That's either of the following.
   *   "CAEN"     : CAENLinuxBusAdapter instantiated
   *   "DUMMY64X" : VME64xDummyBusAdapter instantiated
   *   ""         : no VMEBusAdapterInterface instantiated
   */
  std::string getUsedBusAdapterName();

  /**
   * Tells whether the resources needed for accessing the hardware
   * have already been successfully initialized.
   */
  bool boardResourcesInitialized();

protected:

  //! abstract factory method for the GenericTTCModule managed by this proxy
  virtual GenericTTCModule* createPtr(HAL::VMEBusAdapterInterface* busAdapter) = 0;

  log4cplus::Logger logger_;

  // hardware access parameters

  std::string busAdapterName_;

  int boardSlot_;

  bool enableVMEWrite_;

private:

  //! Returns ptr_ after lazy initialization.
  GenericTTCModule* ptr();

  //! Deletes resources (bus adapter and board objects).
  void deleteResources();

  //! Deletes resources (bus adapter and board objects) and recreates them.
  void recreateResources();


  // bookkeeping variables

  std::string proxyName_;

  bool paramsInited_;


  // hardware access primitives

  HAL::VMEBusAdapterInterface* busAdapter_;

  GenericTTCModule* volatile ptr_;
};

}


#endif
