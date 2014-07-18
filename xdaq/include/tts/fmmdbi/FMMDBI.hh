#ifndef _FMMDBI_H
#define _FMMDBI_H

/**
 *     @class FMMDBI
 *
 *     @short Abstract base class of database interface for the FMM
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:31 $
 *
 *
 **/

#include <vector>
#include <string>

#include "tts/fmm/FMMBasicTestResult.hh"

namespace tts {

  class FMMDBI {

  public:
    /// c-tor 
    FMMDBI() {};

    /// d-tor
    virtual ~FMMDBI() {};

    /// check if a board is defined in the table of boards
    ///
    ///
    virtual bool boardDefined(std::string serialnumber, std::string type = "FMM") = 0;
  
    virtual void insertBoard(std::string serialnumber, std::string type) = 0;

    virtual int getFirmwareId(std::string board_type, std::string chip_type, std::string revision) = 0;

    virtual void logFirmwareLoad(std::string serialnumber, 
				 int fwid,
				 std::string login,
				 std::string host) = 0;

    virtual int logTest(std::string serialnumber, 
			std::string login,
			std::string host) = 0;

    virtual void logStage1Details(int testid,
				  double milliamps_3v3,
				  double milliamps_5v) = 0;

    virtual void logSelfTestDetails(int testid,
				    std::string fwid_altera,
				    std::string fwid_xilinx) = 0;

    virtual void updateSelfTestDetails(int testid) = 0;

    virtual void logStage2Details(int testid,
				  std::string fwrev_altera,
				  std::string fwrev_xilinx,
				  std::string tester_sn,
				  std::string tester_fwrev_altera,
				  std::string tester_fwrev_xilinx) = 0;

    virtual void updateStage2Details(int testid) = 0;

    virtual void logBasicTestResult(int testid, tts::FMMBasicTestResult const& result) = 0;
    virtual void updateBasicTestResult(int testid, tts::FMMBasicTestResult const& result) = 0;

    virtual void logBasicTestResult(int testid, std::vector<tts::FMMBasicTestResult> const& results) = 0;
    virtual void updateBasicTestResult(int testid, std::vector<tts::FMMBasicTestResult> const& results) = 0;


    virtual void insertBoardLog(std::string serialnumber, 
				std::string login,
				std::string comment) = 0;

  };

}
#endif
