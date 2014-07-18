// $Id: XceptSerializer.h,v 1.2 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/
 
#ifndef _xdaq_XceptSerializer_h_
#define _xdaq_XceptSerializer_h_
 
#include "xcept/Exception.h"
#include "xdaq/exception/SerializationFailed.h"
#include <xercesc/dom/DOM.hpp>

#include "xdata/exdr/OutputStreamBuffer.h"
#include "xdata/exdr/InputStreamBuffer.h"
 
XERCES_CPP_NAMESPACE_USE
 
namespace xdaq 
{
 	class XceptSerializer
	{
		public:
		
		/*! Write an exception into a DOM node according to the
		      XML schema at http://xdaq.web.cern.ch/xdaq/xsd/2005/ErrorNotification-11.xsd
		      The serialized exception is appended to the given DOM node
		   */
		static void writeTo (xcept::Exception& e, DOMNode* node) 
			throw (xdaq::exception::SerializationFailed);
		
		/*! Read a serialized exception into the provided exception object */
		static void importFrom (DOMNode* dom, xcept::Exception& e) 
			throw (xdaq::exception::SerializationFailed);		

		/*! Write an exception into a memory buffer using EXDR format */
		static void writeTo (xcept::Exception& e, xdata::exdr::OutputStreamBuffer *sbuf )
			throw(xdata::exception::Exception);
		
		/*! Read a serialized exception into the provided exception object */
		static void importFrom (xdata::exdr::InputStreamBuffer *sbuf, xcept::Exception& e)
			throw(xdata::exception::Exception);
	};
}
 
#endif

