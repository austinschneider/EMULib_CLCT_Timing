#ifndef _FMMFULLSELFTEST_H
#define _FMMFULLSELFTEST_H

/**
 *     @class FMMFullSelfTest
 *
 *     @short Full self-test of the FMM including different possible tests
 *
 *            The following tests are run:
 *
 *            @li FMMRegisterTest tests all r/w registers with random values
 *            @li FMMZBTTest test the ZBT RAM with random values
 *            @li FMMRandomTransitionTest simulates random transitions and checks the 
 *                history memory.
 *            @li FMMTransitionTest generated more realistic trnsiaitions and tests 
 *                the Merging logic, the output and the history memory. 
 *            @li FMMFunctionalTest, testing the qualitative functioning function of the dead time counters.
 *
 *            Not tested: Time tag
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:27 $
 *
 *
 **/

#include "tts/fmm/FMMCard.hh"
#include "tts/fmmtd/FMMTDCard.hh"
#include "tts/fmm/FMMBasicTest.hh"

#include <iostream>
#include <stdint.h>

namespace tts {

  class FMMTransitionGenerator;

  class FMMFullSelfTest : public tts::FMMBasicTest {
  
  public:
    /// c-tor
    ///
    /// @param fmm is a reference to the FMMCard
    /// @param os is an std::ostream to which output is directed.
    /// @param vlevel is the desired log level.
    FMMFullSelfTest(tts::FMMCard & fmm, 
		    tts::FMMTDCard *td,
		    std::ostream& os = std::cout, 
		    tts::FMMBasicTest::VerbosityLevel vlevel = tts::FMMBasicTest::V_ERR);

    /// d-tor
    virtual ~FMMFullSelfTest();

    /// print the status of the tests
    void printStatus();

    /// return a reference to the FMM Card
    tts::FMMCard& card() const { return _fmm; };

    /// return the std::vector of test results
    void getResults(std::vector <tts::FMMBasicTestResult>& results);

  private:
    /// run the test with default parameters
    ///
    /// returns true if successful, false if not 
    virtual bool _run(uint32_t nloops);

    tts::FMMCard& _fmm;
    tts::FMMTransitionGenerator *_tg;
    std::vector<tts::FMMBasicTest*> _tests;
  };

}

#endif
