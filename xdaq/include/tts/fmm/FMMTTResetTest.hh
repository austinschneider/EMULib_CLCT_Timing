#ifndef _FMMTTRESETTEST_H
#define _FMMTTRESETTEST_H

/**
 *     @class FMMTTResetTest
 *
 *     @short Test the Time-Tag reset via the backplane.
 *
 *            A trigger distributor is required to perform this test.
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
#include "tts/fmmtd/FMMTDCard.hh"

#include <iostream>
#include <stdint.h>

namespace tts {

  class FMMTTResetTest : public tts::FMMBasicTest {
  
  public:
    /// c-tor
    ///
    /// @param card is the FMMCard to use
    /// @param td is a reference to an FMM Trigger Distributor
    /// @param os is an std::ostream to which output is directed.
    /// @param vlevel is the verbosity level
    FMMTTResetTest( tts::FMMCard& card,
		    tts::FMMTDCard& td,
		    std::ostream& os = std::cout, 
		    tts::FMMBasicTest::VerbosityLevel vlevel = tts::FMMBasicTest::V_ERR) 
      : tts::FMMBasicTest(os, vlevel), _card(card), _td(td) {};

    /// d-tor
    virtual ~FMMTTResetTest() {};

    /// return name
    virtual std::string getName() const { return "FMMTTResetTest"; };

    /// get the version of the test
    virtual std::string getVersion() const;

  protected: 
    /// run the test
    ///
    /// returns true if successful, false if not 
    virtual bool _run(uint32_t  nloops);

    tts::FMMCard& _card;
    tts::FMMTDCard& _td;
  };

}
#endif
