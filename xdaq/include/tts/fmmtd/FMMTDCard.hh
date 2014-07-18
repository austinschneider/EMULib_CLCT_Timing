#ifndef _FMMTDCARD_H
#define _FMMTDCARD_H

/**
 *     @class FMMTDCard
 *
 *     @short Class representing the basic functions of the FMM Trigger Distributor
 *
 *            A trigger distributor will be present in every FMM crate (leftmost card)
 *            It  distributes a reset pulse to all tts::FMMs in order to
 *            reset the time tags synchronously.
 *
 *            The reset pulse can either be reveived by a LEMO connector on the front panel
 *            or can be generated via PCI.
 *
 *            The tts::FMMTDCard class is using a HAL PCIDevice in order to 
 *            access the Trigger Distributor.
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:32 $
 *
 *
 **/

#include "hal/PCIDevice.hh"
#include "tts/cpcibase/CPCICard.hh"

namespace tts {

  class FMMTDCard : public tts::CPCICard {
  
  public:
    /// c-tor
    ///
    /// @param fmmdevice is a pointer to the HAL::PCIDevice used to access the hardware. 
    /// The FMMTDCard becomes the owner of the HAL::PCIDevice  and is responsible for its destruction. 
    ///
    /// @param cratelock is a reference to the cratelock object. 
    FMMTDCard( HAL::PCIDevice* device, ipcutils::SemaphoreArray& cratelock );

    /// d-tor
    virtual ~FMMTDCard();

    /// toggle PCI mode
    ///
    /// 
    /// @param pcimode is true for PCI mode, false for LEMO mode
    void togglePCIMode(bool pcimode)
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);

    /// generate reset pulse
    ///
    /// only works in PCI mode
    void generateResetPulse()
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);

    /// get a referene to the HAL PCIDevice
    HAL::PCIDevice& device() { return * ( _dev() ); };

  };

}

#endif
