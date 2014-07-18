#ifndef _FMMORACLEDBI_H
#define _FMMORACLEDBI_H

/**
 *     @class FMMOracleDBI
 *
 *     @short OCCI Database interface for the FMM
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:31 $
 *
 *
 **/


#include "tts/fmmdbi/FMMDBI.hh"
#include "tts/fmm/FMMBasicTestResult.hh"

#include <vector>
#include <string>
#include <occi.h>

namespace tts {

  class FMMOracleDBI : public tts::FMMDBI {

  public:
    /// c-tor 
    FMMOracleDBI(std::string user, std::string pwd, std::string db);

    /// d-tor
    virtual ~FMMOracleDBI();

    /// check if a board is defined in the table of boards
    ///
    ///
    virtual bool boardDefined(std::string serialnumber, std::string type = "FMM");
  
    virtual void insertBoard(std::string serialnumber, std::string type);

    virtual int getFirmwareId(std::string board_type, std::string chip_type, std::string revision);

    virtual void logFirmwareLoad(std::string serialnumber, 
				 int fwid,
				 std::string login,
				 std::string host);

    virtual int logTest(std::string serialnumber, 
			std::string login,
			std::string host);

    virtual void logStage1Details(int testid,
				  double milliamps_3v3,
				  double milliamps_5v);

    virtual void logSelfTestDetails(int testid,
				    std::string fwid_altera,
				    std::string fwid_xilinx);

    virtual void updateSelfTestDetails(int testid);

    virtual void logStage2Details(int testid,
				  std::string fwrev_altera,
				  std::string fwrev_xilinx,
				  std::string tester_sn,
				  std::string tester_fwrev_altera,
				  std::string tester_fwrev_xilinx);

    virtual void updateStage2Details(int testid);

    virtual void logBasicTestResult(int testid, tts::FMMBasicTestResult const& result);
    virtual void updateBasicTestResult(int testid, tts::FMMBasicTestResult const& result);

    virtual void logBasicTestResult(int testid, std::vector<tts::FMMBasicTestResult> const& results);
    virtual void updateBasicTestResult(int testid, std::vector<tts::FMMBasicTestResult> const& results);


    virtual void insertBoardLog(std::string serialnumber, 
				std::string login,
				std::string comment);

  private:
    int insertLog(std::string login, std::string comment);
    int insertTest(std::string sn, int logid, int result);


    oracle::occi::Environment* _env;
    oracle::occi::Connection* _conn;
    oracle::occi::Statement* _stmt;

  };

}
#endif
