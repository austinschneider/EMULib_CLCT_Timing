// $Id: MimeHeaders.h,v 1.2 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xoap_MimeHeaders_h_
#define _xoap_MimeHeaders_h_

#include <map>
#include <vector>
#include <string>
#include "xoap/exception/Exception.h"


namespace xoap
{
/**
 * A container for <code>MimeHeader</code> objects, which represent 
 * the MIME headers present in a MIME part of a message. 
 *
 * <p>This class is used primarily when an application wants to
 * retrieve specific attachments based on certain MIME headers and
 * values. This class will most likely be used by implementations of
 * <code>AttachmentPart</code> and other MIME dependent parts of the JAXM 
 * API.
 * @see SOAPMessage#getAttachments
 * @see AttachmentPart
 */
class MimeHeaders 
{
    private:
    
    std::multimap<std::string, std::string, std::less<std::string> > headers_;
    
    public:
     
   /**
    * Constructs a default <code>MimeHeaders</code> object initialized with
    * an empty <code>multimap</code> object. 
    */
   
    MimeHeaders();

    /**
     * Returns all of the values for the specified header as a vector of
     * <code>string</code> objects.
     *
     * @param	name the name of the header for which values will be returned
     * @return a <code>string</code> array with all of the values for the
     *         specified header 
     * @see #setHeader
     */
    std::vector<std::string> getHeader(const std::string& name);

    /**
     * Replaces the current value of the first header entry whose name matches 
     * the given name with the given value, adding a new header if no existing header
     * name matches. This method also removes all matching headers after the first one.
     * <P>
     * Note that RFC822 headers can contain only US-ASCII characters.
     *
     * @param	name a <code>string</code> with the name of the header for
     *          which to search
     * @param	value a <code>string</code> with the value that will replace the
     *          current value of the specified header
     *
     * @exception SOAPException (IllegalArgumentException) if there was a problem in the
     * mime header name or the value being set
     * @see #getHeader
     */
    void setHeader(const std::string& name, const std::string& value) throw (xoap::exception::Exception);
    
    /**
     * Adds a MimeHeader <code>name/value</code> pair  
     * to this <code>MimeHeaders</code> object's list of headers.
     * <P> 
     * Note that RFC822 headers can contain only US-ASCII characters.
     *
     * @param	name a <code>string</code> with the name of the header to
     *          be added
     * @param	value a <code>string</code> with the value of the header to
     *          be added
     *
     * @exception SOAPException (IllegalArgumentException) if there was a problem in the
     * mime header name or value being added
     */ 
    void addHeader(const std::string& name, const std::string& value) throw (xoap::exception::Exception);

    /**
     * Remove all <code>MimeHeader</code> objects whose name matches the
     * the given name.
     *
     * @param	name a <code>string</code> with the name of the header for
     *          which to search
     */
    void removeHeader(const std::string& name);

    /**
     * Removes all the header entries from this <code>MimeHeaders</code> object.
     */
    void removeAllHeaders();
    

    /**
     * Returns all the MimeHeaders in a <code>Multimap</code> object reference.
     */
    std::multimap<std::string, std::string, std::less<std::string> >& getAllHeaders();

};

}
#endif
