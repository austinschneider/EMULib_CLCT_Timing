#ifndef _FMMRANDOMTRANSITIONTEST_H
#define _FMMRANDOMTRANSITIONTEST_H

/**
 *     @class FMMRandomTransitionTest
 *
 *     @short FMM test to test the functionality
 *
 *            Input states are randomly chosen and simulated using
 *            the input registers. After generating 128k transitions,
 *            the contents of the history memory are checked.
 *            (Attn: No check of the case that two random state vecrors may
 *            be the same.)
 *  
 *            No check of the emrging function since the result will
 *            be invalid most of the time.
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

  class FMMRandomTransitionTest : public tts::FMMBasicTest {
  
  public:
    /// c-tor
    ///
    /// @param fmmdevice is a reference to an exisitng HAL
    ///        PCIDevice of an FMM
    /// @param os is an std::ostream to which output is directed.
    FMMRandomTransitionTest( tts::FMMCard& card,
			     std::ostream& os = std::cout, 
			     tts::FMMBasicTest::VerbosityLevel vlevel = tts::FMMBasicTest::V_ERR) 
      : tts::FMMBasicTest(os, vlevel), _card(card) {};

    /// d-tor
    virtual ~FMMRandomTransitionTest() {};

    /// get the name
    virtual std::string getName() const { return "FMMRandomTransitionTest"; }; 

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
