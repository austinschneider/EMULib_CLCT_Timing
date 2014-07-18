#ifndef _FMMREGISTERTEST_H
#define _FMMREGISTERTEST_H

/**
 *     @class FMMRegisterTest
 *
 *     @short Test testing the registers of the FMM
 *
 *            One loop corresponds to 10000 repetitions of writing and 
 *            reading each r/w register.
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

  class FMMRegisterTest : public tts::FMMBasicTest {
  
  public:
    /// c-tor
    ///
    /// @param fmmdevice is a reference to an exisitng HAL
    ///        PCIDevice of an FMM
    /// @param os is an std::ostream to which output is directed.
    /// @param vlevel is the verbosity level
    FMMRegisterTest( HAL::PCIDevice& fmmdevice, 
		     std::ostream& os = std::cout, 
		     tts::FMMBasicTest::VerbosityLevel vlevel = tts::FMMBasicTest::V_ERR) 
      : tts::FMMBasicTest(os, vlevel), _fmm(fmmdevice) {};

    /// d-tor
    virtual ~FMMRegisterTest() {};

    /// return name
    virtual std::string getName() const { return "FMMRegisterTest"; };

    /// get the version of the test
    virtual std::string getVersion() const;

  protected: 
    /// run the test
    ///
    /// returns true if successful, false if not 
    virtual bool _run(uint32_t  nloops);

    HAL::PCIDevice& _fmm;
  };

}

#endif
