#ifndef _FMMFUNCTIONALTEST_H
#define _FMMFUNCTIONALTEST_H

/**
 *     @class FMMFunctionalTest
 *
 *     @short FMM test to test the functionality
 * 
 *            Basic test of the hardware monitors.
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:27 $
 *
 *
 **/

#include "tts/fmm/FMMBasicTest.hh"
#include "tts/fmm/FMMCard.hh"

#include <iostream>
#include <stdint.h>

namespace tts {

  class FMMFunctionalTest : public tts::FMMBasicTest {
  
  public:
    /// c-tor
    ///
    /// @param card is a reference to the FMMCard
    /// @param os is an std::ostream to which output is directed.
    FMMFunctionalTest( tts::FMMCard& card, 
		       std::ostream& os = std::cout, 
		       tts::FMMBasicTest::VerbosityLevel vlevel = tts::FMMBasicTest::V_ERR ) 
      : tts::FMMBasicTest(os, vlevel), _card(card) {};

    /// d-tor
    virtual ~FMMFunctionalTest() {};

    /// get the name
    std::string getName() const { return "FMMFunctionalTest"; };

    /// get the version of the test
    virtual std::string getVersion() const;

  protected: 
    /// run the test
    ///
    /// returns true if successful, false if not 
    virtual bool _run(uint32_t nloops);

    tts::FMMCard& _card;
  };

}

#endif
