#ifndef _CPCICARD_H
#define _CPCICARD_H

/**
 *     @class CPCICard
 *
 *     @short Class representing the basic functions of a CMS DAQ CompactPCI Card
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.2 $
 *     $Date: 2007/03/28 12:06:22 $
 *
 *
 **/

#include "tts/ipcutils/SemaphoreArray.hh"

#include "hal/PCIDevice.hh"
#include "hal/HardwareAccessException.hh"

#include "xcept/Exception.h"

DEFINE_EXCEPTION1(tts, NoWriteLock);



#include <vector>
#include <stdint.h>

namespace tts {

  class CPCICard {
  
  public:
    /// c-tor
    ///
    /// @param fmmdevice is a pinter to the HAL::PCIDevice used to access the hardware. 
    /// The CPCICard becomes the owner of the HAL::PCIDevice  and is responsible for its destruction. 
    ///
    /// The fields "GeoSlot", "sn_a", "sn_b", "sn_c", and "FWID_ALTERA" need to be defined
    ///
    /// @param cratelock is a reference to the cratelock object. 
    CPCICard( HAL::PCIDevice* device, ipcutils::SemaphoreArray& cratelock);

    /// d-tor
    ///
    /// releases the write lock if not done before
    ///
    virtual ~CPCICard();

    /// get a write lock for the FMM
    ///
    /// This method has to be called before any method that
    /// writes to the FMM.
    ///
    /// This method needs a host-wide semaphore arrary which has to be crated with crate_lock_util.exe
    ///
    /// returns true if successful, false if not
    bool getWriteLock()
      throw (ipcutils::exception::Exception);

    /// release the write lock for the FMM
    ///
    /// This method releases the write lock. After completion of this call, no more
    /// methods writing to the FMM may be called. The user has to ensure that other
    /// threads using the FMM have stopped writing to the FMM before calling
    /// releaseWriteLock()
    ///
    void releaseWriteLock()
      throw (ipcutils::exception::Exception);

    /// check if we have a write lock
    ///
    /// this implementation uses a simple variable _have_write_lock to remeber whether it has obtained
    /// a write lock. This approach is problematic in multi-threaded applications.
    ///
    /// In the FMMController Application, both the SOAP callbacks and the HyperDAQ callbacks
    /// for web page creation are executed in the same thread. The only additional thread is 
    /// the autoUpdate thread which is started only after acquiring the lock and stopped before
    /// releasing it. For this case the implementation should work fine.
    ///
    /// A different mechanism has to be used for real multi-threaded operation.
    /// For example a separate semaphore could be used to synchronize multiple threads writing to the FMM.
    /// As long a these therads use distinct functions of the FMM, multiple write operations in parallel could be allowed.
    /// Before releasing the crate lock, the thread calling release would have to wait for all other threads to finish writing.
    /// Larger-scope atomic sections would have to be dealt with at a higher level.
    ///
    bool haveWriteLock();

    /// get process id of the process that has the write lock of the FMM
    /// 
    /// returns -1 if the FMM is not locked
    int getWriteLockOwnerPID()
      throw (ipcutils::exception::Exception);
  

    /// disable locking
    ///
    /// after calling disableLocking(),  getWriteLock and releaseWriteLock will 
    /// not ask the system for a lock for their GeoSlot.
    ///
    /// Nevertheless getWriteLock has to be called before writing to an FMM.
    /// 
    /// needed for crates without geoslots. Be careful to call this only when no write lock is held.
    ///
    void disableLocking();

    /// enable locking
    ///
    /// reverses the effect of disableLocking
    void enableLocking();
  
    /// is locking enabled ?
    bool isLockingEnabled();

    /// read the Revision of the Firmware of the Altera (Bridge)
    ///
    /// The std::string contains 9 characters in the format "YYMMDD_RR",
    /// where YY is the year since 2000, MM, the month (1-12), DD the day (1-31) and RR the revision in this day (00-99)
    std::string readFirmwareRevAltera()
      throw (HAL::HardwareAccessException);

    /// read the serial number
    ///
    /// the reurned std::string contains the 19 digits of the serial number
    std::string getSerialNumber()
      throw (HAL::HardwareAccessException);


    /// read the GeoSlot
    ///
    /// GeoSlots in a Compact PCI crate range from 0 (rightmost slot) to 20 (leftmost slot)
    /// The rightmost slot (0) is usually occupied by the controller (connection to the PC) 
    /// An FMM occupies two slots and has its connector in the left one of the two slots.
    ///
    /// Note: GeoSlots are only available in Compact PCI crates with a custom CMSDAQ backplane.
    ///
    uint32_t getGeoSlot()
      throw (HAL::HardwareAccessException);


    /// get a referene to the HAL HAL::PCIDevice
    ///
    /// warning: if the hardware is accessed through the HAL::PCIDevice, 
    /// no write lock checking is performed!
    ///
    HAL::PCIDevice& device() { return *_device; };

  protected: 
    /// check if we have a write lock and throw exception, otherwise throw an exception
    void check_write_lock() 
      throw (tts::exception::NoWriteLock);

    HAL::PCIDevice* _dev() {
      return _device;
    }

  private:
    HAL::PCIDevice* _device;
    std::string _serialnumber;
    uint32_t _geoslot;

    ipcutils::SemaphoreArray& _cratelock;
    bool _have_write_lock;
    bool _locking_enabled;
  };

}
#endif
