// $Id: URL.h,v 1.12 2008/07/18 15:27:36 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_net_URL_h_
#define _toolbox_net_URL_h_

#include <string>
#include "toolbox/net/exception/MalformedURL.h"
#include "toolbox/net/exception/BadURL.h"

namespace toolbox {
namespace net {

/*!
For the specification of the URL syntax http://www.ietf.org/rfc/rfc3986.txt

 foo://example.com:8042/over/there?name=ferret#nose
 \_/   \______________/\_________/ \_________/ \__/
  |           |            |            |        |
scheme     authority       path        query   fragment
  |   _____________________|__
 / \ /                        \
 urn:example:animal:ferret:nose
*/
class URL 
{
  public:
    // Create a URL from the specified protocol, hostname,
    // port number and spec.  This will be of the form:
    // protocol://hostname:portnumber/spec
    URL(const std::string& protocol, const std::string& hostname,
	unsigned int portnumber, const std::string& spec) throw (toolbox::net::exception::MalformedURL);

    // Create the URL from the specified string.  May throw
    // MalformedURL.
    URL(const std::string& url) throw (toolbox::net::exception::MalformedURL);

    // Copy the URL
    URL(const URL&);

    // Destructor
    ~URL();

    // Return the entire URL as a single string.
    std::string toString() const;

    //! DEPRECTATED: Return the protocol string.
    std::string getProtocol() const;
    
    //! Return the scheme string (superseeds getProtocol())
    std::string getScheme() const;

    // Return the hostname.
    std::string getHost() const;

    // Return the port number (0 if one was not specified in
    // the URL.
    unsigned int getPort() const;

    // Return the URL path (i.e. the filename part).  Returns
    // an empty string if a spec was not specified in the URL.
    std::string getPath() const;
    
    //! Return URL part after "#" character up to the end
    //
    std::string getFragment() const;
    
    //! Return URL part after the "?" character
    //
    std::string getQuery() const;
    
    //! Return a normalized (resolved) URL 
    /*! \throws toolbox::net::exception::MalformedURL if the host cannot be resolved
    */
    std::string getNormalizedURL() throw (toolbox::net::exception::BadURL);
    
    /*! Return the authority part of the URL */
    std::string getAuthority () const;

  protected:
  private:
  
    std::string d_protocol;
    std::string d_hostname;
    unsigned int d_portno;
    std::string d_spec;
    
};

}}

#endif
