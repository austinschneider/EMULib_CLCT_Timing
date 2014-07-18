// $Id: XStr.h,v 1.4 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_XStr_h_
#define _xdata_XStr_h_

#include "xercesc/dom/DOM.hpp"
#include <string>

XERCES_CPP_NAMESPACE_USE

namespace xdata
{
	std::string XMLCh2String (const XMLCh* ch);

	class XStr
	{
		public :

		    XStr(const char* const toTranscode);
		    XStr(const std::string& toTranscode);     
		    ~XStr();

		    const XMLCh* unicodeForm() const;

		    operator const XMLCh*();

		private :

		    XMLCh*   fUnicodeForm;
	};
}

#endif
