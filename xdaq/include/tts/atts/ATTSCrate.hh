#ifndef _tts_atts_ATTSCRATE_H
#define _tts_atts_ATTSCRATE_H

/**
 *     @class ATTSCrate
 *
 *     @short Class representing the PCI crate containing oe or multiple ATTS interfaces
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:24 $
 *
 *
 **/

#include "hal/PCIDevice.hh"
#include "hal/PCIAddressTable.hh"
#include "hal/PCIBusAdapterInterface.hh"

#include "hal/HardwareAccessException.hh"
#include "xcept/Exception.h"

#include <vector>
#include <stdint.h>

namespace tts {

  class ATTSInterfaceCard;

  class ATTSCrate {
  
  private:
    /// c-tor
    ///
    /// read the address table and determines the PCI-Devices 
    ///
    /// @param dummy: if true the dummy bus adapter will be used
    ATTSCrate(bool dummy=false)
      throw (HAL::HardwareAccessException, xcept::Exception);

  public:

    /// d-tor
    virtual ~ATTSCrate();

    /// get an the (single) instance of the ATTSCrate
    ///
    static ATTSCrate* getInstance()
      throw (HAL::HardwareAccessException, xcept::Exception);

  
    /// get the ATTS Address Table
    HAL::PCIAddressTable* getATTSAddressTable() { return _atts_addresstable; };
  
    /// return the number of ATTS Interface Cards in the crate
    std::vector<tts::ATTSInterfaceCard*>::size_type  numATTSInterfaceCards() { return _theATTSs.size(); };

    /// find an ATTS by its PCI Index
    ///
    tts::ATTSInterfaceCard& getATTSInterfaceCard( uint32_t id )
      throw (xcept::Exception);

  
    /// find an ATTS by its Serial Number
    ///
    /// @param sn is the serial number
    ///
    tts::ATTSInterfaceCard& getATTSInterfaceCardbySN( std::string const& sn )
      throw (xcept::Exception);
  
    /// find an ATTS by its GeoSlot
    ///
    /// @param geoslot is the number of the GeoSlot (0 to 20)
    ///
    /// GeoSlots in a Compact PCI crate range from 0 (rightmost slot) to 20 (leftmost slot)
    /// The rightmost slot (0) is usually occupied by the controller (connection to the PC) 
    /// An ATTS occupies two slots and has its connector in the left one of the two slots.
    ///
    /// 
    /// Note: GeoSlots are only available in Compact PCI crates with a custom CMSDAQ backplane.
    ///
    tts::ATTSInterfaceCard& getATTSInterfaceCardbyGeoSlot( uint32_t geoslot )
      throw (xcept::Exception);

    /// get a reference to the bus adapter
    HAL::PCIBusAdapterInterface& getPCIBusAdapter() { return *_busadapter;};

  private:
    /// clean up all dynamically created objects belonging to ATTSCrate.
    /// only called upon exception in constructor and in desutuctor
    void cleanup();

    /// check that the geoslots are unique in the crate
    void checkGeoSlotsUnique()
      throw (xcept::Exception);

  protected: 
    HAL::PCIBusAdapterInterface *_busadapter;
    HAL::PCIAddressTable *_atts_addresstable;
    std::vector<tts::ATTSInterfaceCard*> _theATTSs;

    static tts::ATTSCrate *_instance;
  };

}
#endif
