#ifndef _FMMZBTTEST_H
#define _FMMZBTTEST_H

/**
 *     @class FMMZBTTest
 *
 *     @short FMM test to test the ZBT RAM
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:27 $
 *
 *
 **/

#include "tts/fmm/FMMBasicTest.hh"
#include "hal/PCIDevice.hh"

#include <iostream>
#include <stdint.h>

namespace tts {

  class FMMZBTTest : public tts::FMMBasicTest {
  
  public:
    /// c-tor
    ///
    /// @param fmmdevice is a reference to an exisitng HAL
    ///        PCIDevice of an FMM
    /// @param os is an std::ostream to which output is directed.
    FMMZBTTest( HAL::PCIDevice& fmmdevice, 
		std::ostream& os = std::cout, 
		tts::FMMBasicTest::VerbosityLevel vlevel = tts::FMMBasicTest::V_ERR) 
      : tts::FMMBasicTest(os, vlevel), _fmm(fmmdevice){};

    /// d-tor
    virtual ~FMMZBTTest() {};

    /// return name
    virtual std::string getName() const { return "FMMZBTTest"; };

    /// get the version of the test
    virtual std::string getVersion() const;

  protected: 
    /// run the test
    ///
    /// returns true if successful, false if not 
    virtual bool _run(uint32_t nloops);

    HAL::PCIDevice& _fmm;
  };

}
#endif
