// $Id: Serializer.h,v 1.2 2008/07/18 15:27:29 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/
 
 #ifndef _sentinel_utils_Serializer_h_
 #define _sentinel_utils_Serializer_h_
 
 #include "xcept/Exception.h"
 #include <xercesc/dom/DOM.hpp>
 
 XERCES_CPP_NAMESPACE_USE
 
 namespace sentinel {
 namespace utils {
 
 	class Serializer
	{
		public:
		
		/*! Write an exception into a DOM node according to the
		      XML schema at http://xdaq.web.cern.ch/xdaq/xsd/2005/ErrorNotification-11.xsd
		      The serialized exception is appended to the given DOM node
		   */
		static void writeTo (xcept::Exception& e, DOMNode* node);
		
		/*! Read a serialized exception into the provided exception object */
		static void importFrom (DOMNode* dom, xcept::Exception& e);		
	};
}
}
 
 #endif
