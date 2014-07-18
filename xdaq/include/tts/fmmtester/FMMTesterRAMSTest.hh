#ifndef _FMMTESTERRAMSTEST_H
#define _FMMTESTERRAMSTEST_H

/**
 *     @class FMMTesterRAMSTest
 *
 *     @short Test of the FMM Tester Sequence RAMs
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:34 $
 *
 *
 **/

#include "tts/fmm/FMMBasicTest.hh"
#include "hal/PCIDevice.hh"

#include <stdint.h>

namespace tts {

  class FMMTesterRAMSTest : public tts::FMMBasicTest {
  
  public:
    /// c-tor
    ///
    /// @param fmmdevice is a reference to an exisitng 
    ///        HAL::PCIDevice of an FMM
    FMMTesterRAMSTest( HAL::PCIDevice& fmmtdevice, 
		       std::ostream& os = std::cout,
		       tts::FMMBasicTest::VerbosityLevel vlevel = tts::FMMBasicTest::V_ERR) 
      : tts::FMMBasicTest(os, vlevel), _fmmt(fmmtdevice) {};

    /// d-tor
    virtual ~FMMTesterRAMSTest() {};

    /// get the name of the test
    virtual std::string getName() const { return "FMMTesterRAMSTest"; };

    /// get the version of the test
    virtual std::string getVersion() const;

    /// run the test
    ///
    /// returns true if successful, false if not 
    virtual bool _run(uint32_t nloops);

  protected: 
    HAL::PCIDevice& _fmmt;

  };

}
#endif
