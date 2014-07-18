#ifndef _FMMSTAGE2TEST_H
#define _FMMSTAGE2TEST_H

/**
 *     @class FMMStage2Test
 *
 *     @short Stage2 of the FMM including different tests
 *
 *            The following tests are run:
 *
 *            @li FMMRegisterTest tests all r/w registers with random values
 *            @li FMMZBTTest test the ZBT RAM with random values
 *            @li FMMRandomTransitionTest simulates random transitions and checks the 
 *                history memory.
 *            @li FMMTransitionTest generated more realistic trnsiaitions and tests 
 *                the Merging logic, the output and the history memory. 
 *
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:34 $
 *
 *
 **/

#include "tts/fmm/FMMCard.hh"
#include "tts/fmmtester/FMMTesterCard.hh"
#include "tts/fmmtd/FMMTDCard.hh"
#include "tts/fmm/FMMBasicTest.hh"
#include <iostream>

#include <stdint.h>

namespace tts {

  class FMMTransitionGenerator;

  class FMMStage2Test : public tts::FMMBasicTest {
  
  public:
    /// c-tor
    ///
    /// @param fmm is a reference to the FMMCard
    /// @param fmmt is a reference to the FMMTesterCard
    /// @param os is an std::ostream to which output is directed.
    /// @param vlevel is the desired log level.
    FMMStage2Test(tts::FMMCard& fmm,
		  tts::FMMTesterCard& fmmt,
		  tts::FMMTDCard* td,
		  std::ostream& os = std::cout, 
		  tts::FMMBasicTest::VerbosityLevel vlevel = tts::FMMBasicTest::V_ERR);

    /// d-tor
    virtual ~FMMStage2Test();

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
    tts::FMMTesterCard& _fmmt;
    tts::FMMTransitionGenerator *_tg;
    std::vector<tts::FMMBasicTest*> _tests;
  };

}

#endif
