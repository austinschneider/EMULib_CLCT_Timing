/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _xmas_broker2g_Utils_h_
#define _xmas_broker2g_Utils_h_

#include <string>
#include <list>

#include "xdata/InfoSpace.h"
#include "xdata/Table.h"
#include "xdata/Properties.h"

#include "xmas/broker2g/exception/ParserException.h"

#include "xoap/MessageReference.h"
#include "xoap/MessageFactory.h"
#include "xoap/SOAPEnvelope.h"
#include "xoap/SOAPBody.h"
#include "xoap/domutils.h"
#include "xoap/Method.h"

namespace xmas
{
namespace broker2g
{

	DOMDocument* loadDOM( const std::string& pathname) throw (xmas::broker2g::exception::ParserException);

}
}
#endif

