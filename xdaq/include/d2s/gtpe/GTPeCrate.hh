#ifndef _GTPECRATE_H
#define _GTPECRATE_H

/**
 *     @class GTPeCrate
 *
 *     @short Class representing the PCI crate containing the GTPe
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 08:02:33 $
 *
 *
 **/

#include "hal/PCIAddressTable.hh"
#include "hal/PCIBusAdapterInterface.hh"
#include "hal/PCIAddressTableASCIIReader.hh"

#include "hal/HardwareAccessException.hh"
#include "xcept/Exception.h"


namespace d2s {

  class GTPeCard;

  class GTPeCrate {
  
  public:
    /// c-tor
    ///
    /// read the address table and determines the PCI-Devices 
    ///
    /// @param dummy: if true the dummy bus adapter will be used
    GTPeCrate(bool dummy=false)
      throw (HAL::HardwareAccessException, xcept::Exception);

    /// d-tor
    virtual ~GTPeCrate();
  
    /// return the GTPeCard
    ///
    GTPeCard& getGTPe()
      throw (xcept::Exception);
  
  private:
    /// clean up all dynamically created objects belonging to GTPeCrate.
    /// only called upon exception in constructor and in destructor
    void cleanup();

  protected: 

    HAL::PCIBusAdapterInterface *_busadapter;
    HAL::PCIAddressTable *_gtpe_addresstable;
    GTPeCard* _gtpe;
  };

}
#endif
