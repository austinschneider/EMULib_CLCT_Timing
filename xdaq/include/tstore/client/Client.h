// $Id: Client.h,v 1.2 2007/05/18 15:39:45 brett Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: A. Brett, J. Gutleber and L. Orsini				 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _Client_h_
#define _Client_h_
#include "xcept/Exception.h"

#define TSTORE_NS_URI "http://xdaq.web.cern.ch/xdaq/xsd/2006/tstore-10.xsd"

namespace tstoreclient {

//functions for manipulating view configuration
//returns a DOMElement representing the XML to be added to a view configuration file to configure a database table
DOMElement *createDOMElementForTable(DOMDocument *doc,/*const*/ xdata::Table &table,const std::string &tableName,const std::string &key) throw (xcept::Exception);

//functions for examining the actions performed/proposed during a sync.

//returns whether \a response contains any information on actions that were performed in a sync
//\a response should be the response of a TStore sync message, if it isn't then this function will throw an exception.
bool responseHasSyncActions(xoap::MessageReference response) throw (xcept::Exception);

//general stuff

//returns the connection ID from \a response
//throws an exception if response is not a response to a connect SOAP message, or if it does not have a connection ID
std::string connectionID(xoap::MessageReference response) throw (xcept::Exception);

//returns the class name for a view, which should be the namespace used for that view's parameters.
//views are named urn:class-name:view-name
//this returns urn:class-name, or an empty string if the view name is incorrectly formatted
std::string classNameForView(const std::string &viewName) throw ();

//returns the node (at the root level) of \a response with the name \a nodeName
//throws an exception if there are multiple nodes with this name or if there are none.
//this is not particularly TStore-client specific, but it is here because it is used both by this library and by
//the TStoreTest application. However, I think that the operations that TStoreTest uses it for could also be
//moved into this library, in which case this function could be made private.
DOMNode *getNodeNamed(xoap::MessageReference msg,const std::string &nodeName) throw (xcept::Exception);
void getNodesNamed(std::vector<DOMNode *> &nodes,xoap::MessageReference msg,const std::string &nodeName) throw (xcept::Exception);

}
#endif
