#ifndef _FMMCRATE_H
#define _FMMCRATE_H

/**
 *     @class FMMCrate
 *
 *     @short Class representing the PCI crate containing multiple Fast Merging Modules (FMMs)
 *
 *            Besides tts::FMMs, the Crate may also contain FMM Tester Cards and Trigger 
 *            Distributor cards.
 * 
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:26 $
 *
 *
 **/

#include "hal/PCIDevice.hh"
#include "hal/PCIAddressTable.hh"
#include "hal/PCIBusAdapterInterface.hh"

#include <map>
#include <stdint.h>

namespace ipcutils {
  class SemaphoreArray;
}

namespace tts {

  class FMMCard;
  class FMMTDCard;

  class FMMCrate {
  
  public:
    /// c-tor
    ///
    /// read the address table and determines the PCI-Devices 
    ///
    /// @param dummy: if true the dummy bus adapter will be used
    ///
    /// @param project_id is the project ID used in the genreation of a unique key to identify
    ///        the semaphore array. 
    ///        The default value can be used unless there are multiple cPCI crates on the same host  
    FMMCrate(bool dummy=false, char project_id='t')
      throw (HAL::HardwareAccessException, xcept::Exception);

    /// d-tor
    virtual ~FMMCrate();
  
    /// get the FMM Address Table
    HAL::PCIAddressTable* getFMMAddressTable() { return _fmm_addresstable; };
  
    /// return the number of FMMs in the crate
    uint32_t numFMMs() { return (uint32_t) _theFMMs.size(); };

    /// find an FMM by its PCI Index
    ///
    tts::FMMCard& getFMM( uint32_t id )
      throw (xcept::Exception);
  
    /// find an FMM by its Serial Number
    ///
    /// @param sn is the serial number
    ///
    tts::FMMCard& getFMMbySN( std::string const& sn )
      throw (HAL::HardwareAccessException, xcept::Exception);
  
    /// find an FMM by its GeoSlot
    ///
    /// @param geoslot is the number of the GeoSlot (0 to 20)
    ///
    /// GeoSlots in a Compact PCI crate range from 0 (rightmost slot) to 20 (leftmost slot)
    /// The rightmost slot (0) is usually occupied by the controller (connection to the PC) 
    /// An FMM occupies two slots and has its connector in the left one of the two slots.
    ///
    /// 
    /// Note: GeoSlots are only available in Compact PCI crates with a custom CMSDAQ backplane.
    ///
    tts::FMMCard& getFMMbyGeoSlot( uint32_t geoslot )
      throw (HAL::HardwareAccessException, xcept::Exception);

    /// is there a trigger dirtibutor in the crate?
    bool hasTD();

    /// get the Trigger Distributor
    tts::FMMTDCard& getTD()
      throw (xcept::Exception);

    /// get a reference to the bus adapter
    HAL::PCIBusAdapterInterface& getPCIBusAdapter() { return *_busadapter;};

  private:
    /// clean up all dynamically created objects belonging to FMMCrate.
    /// only called upon exception in constructor and in desutuctor
    void cleanup();

    /// check that the geoslots are unique in the crate
    void checkGeoSlotsUnique()
      throw (HAL::HardwareAccessException, xcept::Exception);

  protected: 
    HAL::PCIBusAdapterInterface *_busadapter;
    HAL::PCIAddressTable *_fmm_addresstable;
    std::vector<tts::FMMCard*> _theFMMs;
    HAL::PCIAddressTable *_fmmtd_addresstable;
    tts::FMMTDCard *_td;
    ipcutils::SemaphoreArray *_crateLock;
  };

}

#endif
