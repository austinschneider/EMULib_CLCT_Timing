#ifndef __DataChecker_hh_
#define __DataChecker_hh_

#include "xdaq/Application.h"
#include "toolbox/mem/Reference.h"
#include "toolbox/mem/Pool.h"
#include "interface/shared/frl_header.h"
#include "myrfb_api.h"

// max superfragment lenfth before giving an error 16 MB
#define FBO_MAXFRAGLENGTH 0x1000000

namespace fedbuilder {

class DataChecker
{
public:

  DataChecker( xdaq::Application *appl );

  void analyzeFragment( toolbox::mem::Reference * ref );

  /**
   *
   * Performs some checks of the Myrinet descriptors and extracts some
   * relevant data fromt the FRL header.
   *
   * check consistency of descriptor length(length of segment including
   * FRL-header) and segSize (length of segment without FRL-header).
   *
   * check consistency of the segment number : the segment number found 
   * in the FRL header is checked against a counter of this class.
   *
   * set some vars: segLast, crcError, fedcrcError, currentPayloadLength
   */
  bool checkMyrinetFBSegment( uint32_t        descLength, 
			      bool          & segLast,
			      bool          & crcError,
			      bool          & fedcrcError,
			      uint32_t      & currentPayloadLength,
			      frlh_t*         descFrlHeader_p, 
			      uint32_t        currentSegmentNumber );


  /**
   * Checks the consistency of a superfragment.
   *
   * A superfragment consists of a chain of fixed size blocks.
   * Every block contains one FRL header at the beginning.
   * After the FRL header follow one or more SLINK fragments. 
   * 
   * This routine checks the consistency of a superfragment trying to reconstruct it:
   * The check starts at the end of the last block where a SLINK trailer should be found.
   * The lendth of the SLINK fragment is written in the trailer. With this the SLINK header
   * of the fragment can be found and checked. If at this point the routine did not arrive
   * at the start of the first block, another SLINK trailer should be found directly before
   * the SLINK trailer (could be in another block). The described checks are repeated until
   * the procedure arrives at the beginning of the first block. 
   *
   * The following inconsistencies can be detected:
   * @li Where an SLINK trailer or header is expected the trailer or header marker are not present.
   * @li The last fragment does not have the Last Fragment flag set.
   * @li The first fragment does not start after the FRL header of the first block in the chain.
   *     (i.e. the procedure mentioned above does not find the last SLINK header directly after 
   *     the FRL header of the first block). 
   *
   */ 
  bool checkSuperFragment( toolbox::mem::Reference * firstRef, std::string &errorString );

  /** 
   * Makes an ASCII dump of a superfragment.
   *
   * If the flag toFile is set the superfragment will be dumped int a series of files in the
   * /tmp directory. The files are named "ruiDump_{evtno}_buf{n}.dat", where every block (as
   * delverend by Myrinet) is dumped into one file and "n" denotes the number of the block in
   * the chain (starting with 0).
   *
   * If toFile is false the dump is going to the logger.
   *
   * The evtno has to be given as a parameter to the routinge.
   */
  void dumpSuperFragment( toolbox::mem::Reference* firstBlock,
			  bool toFile, 
			  std::string comment = "" );

  /**
   * Dumps a single block of data as received from the Myrinet.
   */
  void dumpData ( void* data, int32_t len, bool toFile = false, 
		  uint32_t evtno = 0, uint32_t ibuf = 0,
		  std::string comment = "");
  /**
   * Dump the header of a Myrinet descriptor and the corresponding FRL-Header
   */
  void dumpMyrinetFBSegment( myrfb_handle_t* p_recv_handle );

private:

  Logger logger_;

};

} /* namespace fedbuilder */

#endif /* __DataChecker_hh_ */
