#ifndef _FMMTESTCRATE_H
#define _FMMTESTCRATE_H

/**
 *     @class FMMTestCrate
 *
 *     @short Class representing the PCI test crate containing FMMs and FMMTesters.
 *
 *            This class extends the tts::FMMCrate class and adds the capability to 
 *            detect tts::FMMTesters.
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:34 $
 *
 *
 **/

#include "tts/fmm/FMMCrate.hh"
#include "hal/PCIDevice.hh"
#include "hal/PCIAddressTable.hh"

#include "xcept/Exception.h"

#include <stdint.h>

namespace tts {

  class FMMTesterCard;

  class FMMTestCrate : public tts::FMMCrate {
  
  public:
    /// c-tor
    ///
    /// read the address table and determines the PCI-Devices 
    ///
    /// @param dummy: if true the dummy bus adapter will be used
    FMMTestCrate(bool dummy=false)
      throw (HAL::HardwareAccessException, xcept::Exception);

    /// d-tor
    virtual ~FMMTestCrate();
  
    /// get the FMM Address Table
    HAL::PCIAddressTable* getFMMTesterAddressTable() { return _fmm_tester_addresstable; };
  
    /// return the number of FMMs in the crate
    uint32_t numFMMTesters() { return (uint32_t) _theFMMTesters.size(); };

    /// find an FMM Tester by its unique ID
    ///
    /// FIXME: the id is not yet retrieved
    /// for the time being the FMM Testers are reetrieved by their PCI index
    tts::FMMTesterCard& getFMMTester( uint32_t id )
      throw (HAL::HardwareAccessException, xcept::Exception);

  private:
    void cleanup();

  protected: 
    HAL::PCIAddressTable *_fmm_tester_addresstable;
    std::map<uint32_t, tts::FMMTesterCard*> _theFMMTesters;
  };

}
#endif
