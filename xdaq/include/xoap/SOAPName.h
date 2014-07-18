// $Id: SOAPName.h,v 1.2 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef xoap_SOAPName_h
#define xoap_SOAPName_h

#include <string>

namespace xoap
{

/*! A representation of an XML name. This class provides methods for obtaining
    the local and namespace-qualified names, the prefix associated with the
    namespace, and the URI of the namespace.

    The following is an example of a namespace declaration:

        <myPrefix:myLocalName xmlns:xoap="http://www.myURI.org">

    where \e xmlns stands for XML namespace. The following shows what the member functions in the
    SOAPName class will return:
    - getQualifiedName will return \e myPrefix:myLocalName
    - getURI will return \e http://www.myURI.org
    - getLocalName will return \e myLocalName
    - getPrefix will return \e myPrefix
 */
class SOAPName {
    public:
        /*!
          \param name - the local name
          \param prefix - the prefix of the namespace
          \param uri - the URI of the namespace
         */
	SOAPName(const std::string& name, const std::string& prefix, const std::string& uri);
	
        /*! Retrieves the namespace-qualified name of the XML name which this SOAPName
            object represents.
           \return a string with the namespace-qualified name
         */
	std::string getQualifiedName();
	
        /*! Retrieves the local name of the XML name which this SOAPName object represents.
           \return a string with the local name
         */
	std::string getLocalName();
	
        /*! Retrieves the prefix associated with the namespace of the XML name which this SOAPName
            object represents.
           \return a string with the prefix
         */
	std::string getPrefix();
	
        /*! Retrieves the URI associated with the namespace of the XML name which this SOAPName
            object represents.
           \return a string with the URI of the namespace
         */
	std::string getURI();
	
        /*! A preliminary comparison operator which compares
            local names.
           \param name - a SOAPName object
           \return \e true if the local name of the input SOAPName object is identical to the local name of the
                   current SOAPName object, and \e false otherwise
         */
	bool operator==(SOAPName& name);
	
    protected:
	std::string prefix_;
	std::string name_;
	std::string uri_;
};

}

#endif
