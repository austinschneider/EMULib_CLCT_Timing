#ifndef _FMMBASICTEST_H
#define _FMMBASICTEST_H

/**
 *     @class FMMBasicTest
 *
 *     @short Abstract base class for tests of the FMM
 *
 *            This framework class allows different tests to be 
 *            treated with a common interface. In order to run tests
 *            in pseudo-parallel mode, test can be run for a given number
 *            of loops at a time, accumulationg the total number of loops,
 *            the total number of Errors and the total time spent in the test.
 *
 *            The framework further controls the generation of logging output.
 *            a log straem and verbosity level can be set in the constructor.
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:26 $
 *
 *
 **/

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdint.h>


#include "tts/fmm/FMMBasicTestResult.hh"

namespace tts {

  class TeeStreambuf : public std::streambuf {
  public:
    TeeStreambuf(std::ostream &o1, std::ostream &o2, uint32_t maxlength2)
      : os1_(o1), os2_(o2), _maxlength2(maxlength2), _count2(0) {
    }

  private:
    int overflow(int i) {
      char c = static_cast<char>(i);
      os1_.write(&c, 1);
      if ( ++_count2 < _maxlength2)
	os2_.write(&c, 1);

      return i;
    }

    std::ostream &os1_;
    std::ostream &os2_;
    uint32_t _maxlength2;
    uint32_t _count2;
  };

  class Tee : private tts::TeeStreambuf, public std::ostream {
  public:
    Tee(std::ostream &o1, std::ostream &o2, uint32_t maxlength2)
      : tts::TeeStreambuf(o1, o2, maxlength2), std::ostream(this) {
    }

  }; 

  class FMMBasicTest {
  
  public:
    enum VerbosityLevel { V_OFF=0, V_ERR=1, V_WARN=2, V_INFO=3, V_DEBUG=4 };

    /// c-tor
    ///
    /// @param os is an std::ostream for the test output
    /// @param vlevel is the verbosity level (V_OFF, V_ERR, V_WARN, V_INFO, V_DEBUG )
    FMMBasicTest(std::ostream& os = std::cout, VerbosityLevel vlevel = V_ERR) 
      : _ss(), _os(os, _ss, 2048), _vlevel(vlevel), _nloops(0), _nerrors(0), _nusec(0) {};

    /// d-tor
    virtual ~FMMBasicTest() {};


    /// reset the test counters
    ///
    void resetCounters() { _nloops = _nerrors = 0; _nusec = 0;};

    /// run the test
    ///
    /// returns true if successful, false if not 
    /// this method does the timing of the test and calls the virtual method _run()
    /// to actually run the test.
    virtual bool run(uint32_t nloops = 1);

    /// get the name of the test
    virtual std::string getName() const { return "undefined"; };

    /// get the version of the test
    virtual std::string getVersion() const { return "base version"; };

    /// get the parameters of the test
    ///
    /// returns any special parameters of the test as a std::string 
    virtual std::string getParameters() const { return ""; };

    /// get the number of loops run (since creation of test or last reset)
    uint64_t getNumLoops() const { return _nloops; };
  
    /// get the number of errors found (since creation of test or last reset)
    uint64_t getNumErrors() const { return _nerrors; };
  
    /// get the total time in microseconds spent in the test (since creation of test or last reset)
    uint64_t getTotalTime() const { return _nusec; };

    /// get the beginnign of the error log
    std::string getErrorLog() const { return _ss.str(); };

    /// get the current test result
    void getTestResult(tts::FMMBasicTestResult& result) const;

  protected:
    virtual bool _run(uint32_t nloops) = 0;

    /// is verbosity level greater or equal a certain level
    bool doLog( VerbosityLevel level ) const { return _vlevel >= level; }

    /// return a std::string to prefix error messages in the log
    std::string errPos() const;

    std::stringstream _ss;
    tts::Tee _os;
    VerbosityLevel _vlevel;

    uint64_t _nloops;
    uint64_t _nerrors;
    uint64_t _nusec;

  };

}

#endif
