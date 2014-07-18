// $Id: ToolsATCP.h,v 1.1 2007/03/31 14:23:39 mpieri Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _atcp_ToolsATCP_h_
#define _atcp_ToolsATCP_h_

#include "pt/atcp/ATCP.h" //ADDEDATCP

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <netinet/tcp.h>
//#include <netdb.h>

#include <fcntl.h>

//commented out because it does not compile #include "i2oBinding.h"
//commented out because it does not compile #include "i2o/Method.h"
//#include "pt/atcp/exception/Exception.h"

// Log4CPLUS
#include "log4cplus/logger.h"
#include "log4cplus/consoleappender.h"
#include "log4cplus/helpers/appenderattachableimpl.h"
#include "log4cplus/helpers/loglog.h"
#include "log4cplus/helpers/pointer.h"
#include "log4cplus/spi/loggingevent.h"
#include "log4cplus/layout.h"


using namespace std;
using namespace log4cplus;
//using namespace log4cplus::helpers;
//using namespace log4cplus::spi;

namespace pt {
namespace atcp
{
  //! set NONBLOCK socket option
  int setSockOptionNonBlock(int socket);

  //! set TCP_NODELAY socket option
  int setSockOptionNodelay(int socket);

  //! dump a frame for debug
  void dumpFrame(Logger logger, char* data, int len);

}

}
#endif
