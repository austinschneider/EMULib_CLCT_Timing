// $Id: LoadDOM.h,v 1.2 2007/08/16 17:54:43 brett Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: A. Brett, J. Gutleber and L. Orsini				 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/
#ifndef _tstoreclient_LoadDOM_h_
#define _tstoreclient_LoadDOM_h_


namespace tstoreclient
{
	std::string parsePath(const std::string& pathname) throw (xcept::Exception);
	std::string parseLocalPath(const std::string &path) throw (xcept::Exception);

	void writeXML(DOMNode *pDoc,const std::string &path) throw (xcept::Exception);
	std::string writeXML(DOMNode *pDoc) throw (xcept::Exception);
	void writeXML(DOMNode *pDoc,XMLFormatTarget *target) throw (xcept::Exception);
	
	void removeBlankTextNodes(DOMNode *node);

	std::vector<DOMNode *> nodesWithPrefix(DOMNode *node,const std::string &prefix);	
}


#endif
