#ifndef _FMMOPENINPUTSTEST_H
#define _FMMOPENINPUTSTEST_H

/**
 *     @class FMMOpenInputsTest
 *
 *     @short Test the FMM with open inputs.
 *
 *            This test tests that all inputs of the FMM go to disconnected state,
 *            when no caabled are connected.
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
#include "tts/fmm/FMMCard.hh"

#include <iostream>
#include <stdint.h>

namespace tts {

  class FMMOpenInputsTest : public tts::FMMBasicTest {
  
  public:
    /// c-tor
    ///
    /// @param card is the FMMCard to use
    /// @param os is an std::ostream to which output is directed.
    /// @param vlevel is the verbosity level
    FMMOpenInputsTest( tts::FMMCard& card,
		       std::ostream& os = std::cout, 
		       tts::FMMBasicTest::VerbosityLevel vlevel = tts::FMMBasicTest::V_ERR) 
      : tts::FMMBasicTest(os, vlevel), _card(card) {};

    /// d-tor
    virtual ~FMMOpenInputsTest() {};

    /// return name
    virtual std::string getName() const { return "FMMOpenInputsTest"; };

    /// get the version of the test
    virtual std::string getVersion() const;

  protected: 
    /// run the test
    ///
    /// returns true if successful, false if not 
    virtual bool _run(uint32_t  nloops);

    tts::FMMCard& _card;
  };

}
#endif
