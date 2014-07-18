// $Id: AttachmentPart.h,v 1.3 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef xoap_AttachmentPart_h
#define xoap_AttachmentPart_h

#include <xercesc/util/BinFileInputStream.hpp>
XERCES_CPP_NAMESPACE_USE

#include <string>
#include <map>

#include "xoap/exception/Exception.h"

namespace xoap
{

/*! An attachment to a SOAPMessage object. A SOAPMessage object may contain zero, one, or
    many AttachmentPart objects. Each AttachmentPart object consists of two parts, the 
    application-specific content and the associated MIME headers. The MIME headers consist
    of name/value pairs that can be used to identify and describe the content.
    An AttachmentPart object must conform to certain standards:\n
    1) It must conform to MIME standards (RFC2045, http://www.ietf.org/rfc/rfc2045.txt)\n
    2) It must contain content\n
    3) The header part must contain the header \e Content-Type. This header identifies the
       type of data which are in the content of the AttachmentPart object and it must conform
       to RFC2045.

    An example of a Content-Type header is:
       - Content-Type: image/gif

    The following line of code sets the above header:
    - AttachmentPart* attachment;
    - attachment->setContentType("image/gif");

    There are no restrictions on the type of content in an AttachmentPart object. The content
    may be simple plain text, an XML document, or an image file.
    
    An AttachmentPart object is created with one of the member functions \e createAttachmentPart. These member
    function creates an AttachmentPart object which --if not already populated-- must be 
    populated using the member functions
    \e setContent (recall that an AttachmentPart object must contain content). After setting the
    MIME headers, the AttachmentPart object can be added to the SOAPMessage object using the member
    function \e addAttachmentPart.
    
    The following code fragment shows how to create an AttachmentPart object, populate it with
    some content, set the headers, and add the AttachmentPart object to the SOAPMessage object
    from which it was created:
    
    - SOAPMessage message;
    - AttachmentPart * attachment = message.createAttachmentPart();
    - attachment->setContent("/full_file_path_to_attachment/filename");
    - attachment->setContentId("SOAPTest_No_1");
    - attachment->addMimeHeader("Content-Description", "This is a SOAP message with attachments");
    - message.addAttachmentPart(attachment);
 */
class AttachmentPart 
{
    public:
        AttachmentPart();
	
	~AttachmentPart();
	
	AttachmentPart(const AttachmentPart & ap );
	
	AttachmentPart & operator=(const AttachmentPart & ap);
	
	/*! Sets the MIME header \e Content-Id with the given value.
	    \param id - a string giving the value of the \e Content-Id header
	    \warning - if the \e Content-Id header already 
                       has been given a value and thus is overwritten
	 */
	void setContentId(const std::string& id);
	
	/*! Sets the MIME header \e Content-Type with the given value.
	    \param type - a string giving the value of the \e Content-Type header
	 */
	void setContentType(const std::string& type);
	
	/*! Sets the MIME header \e Content-Location with the given value.
	    \param location - a string giving the value of the \e Content-Location header
	    \warning - if the \e Content-Location header already 
                       has been given a value and thus is overwritten
	 */
        void setContentLocation(const std::string& location);
	
	/*! Sets the MIME header \e Content-Transfer-Encoding with the given value.
	    \param encoding - a string giving the value of the \e Content-Transfer-Encoding header
	    \warning - if the \e Content-Transfer-Encoding header already 
                       has been given a value and thus is overwritten
	 */
        void setContentEncoding(const std::string& encoding);
	
	/*! Sets the content of this AttachmentPart object, the length of the specified content,
            and the value of the MIME header \e Content-Type.
	    \param content - the content of this AttachmentPart object
	    \param len - an int specifying the length of the content in bytes
	    \param type - a string specifying the value of the \e Content-type header
	    \warning - if already existing content is overwritten
	 */
        void setContent(const char* content, size_t len, const std::string& type);
	
	/*! Sets the content of this AttachmentPart object to the one contained in the given 
	    file. 
	    \param file - gives the position of the file containing the content
	    \throw SOAPException - if the given file is empty	
	    \warning - if already existing content is overwritten
	 */
	void setContent(const std::string& file) throw (xoap::exception::Exception);
	
	/*! Retrieves the value of the MIME header \e Content-Id.
	    \return a string giving the value of the \e Content-Id header
	 */
	std::string& getContentId();
	
	/*! Retrieves the value of the MIME header \e Content-Type.
	    \return a string giving the value of the \e Content-Type header
	    \throw SOAPException - if the \e Content-Type header is empty
	 */
	std::string& getContentType() throw (xoap::exception::Exception);
	
	/*! Retrieves the value of the MIME header \e Content-Location.
	    \return a string giving the value of the \e Content-Location header
	 */
        std::string& getContentLocation();
	
	/*! Retrieves the value of the MIME header \e Content-Transfer-Encoding.
	    \return a string giving the value of the \e Content-Transfer-Encoding header
	 */
        std::string& getContentEncoding();
	
	/*! Retrieves the application-specific content of this AttachmentPart object.
	    \return the content of this AttachmentPart object
	 */
        char* getContent();
	
	/*! Retrieves the number of bytes in this AttachmentPart object.
	    \return the size of this AttachmentPart object in bytes.
	 */ 
	size_t getSize();
	
	/*! Removes the content of this AttachmentPart object. Its MIME headers are left untouched.
	 */
        void clearContent();
	
        /*! Adds any given MIME header with the specified name and value to this AttachmentPart object.
            Note that according to the MIME specification, a MIME header should 
            contain only US-ASCII characters and begin with \e Content-.
	    If this MIME header previously has been given a value, the old value is overwritten.
	    \param name - the name of the MIME header to be set, for instance \e Content-Description
	    \param value - the value of the MIME header
	    \throw SOAPException - if the name of the MIME header does not start with \e Content-
	 */
        void addMimeHeader(const std::string& name, const std::string& value) throw (xoap::exception::Exception);
	
	/*! Retrieves the value of the MIME header identified by the given string.
	    \param name - the name of the MIME header
	    \return a string giving the value of the specified header
	    \throw SOAPException - if the name of the given MIME header does not exist
	 */
	std::string getMimeHeader(const std::string& name) throw (xoap::exception::Exception);
	
	/*! Retrieves all MIME headers of this AttachmentPart object.
	    \return a map containing all MIME headers of this AttachmentPart object. 
	            The first entry contains the name of the MIME header
	            and the second entry the value.
	 */
	std::map<std::string, std::string, std::less<std::string> > getAllMimeHeaders();
	
        /*! Removes all MIME headers of this AttachmentPart object
	 */
        void removeAllMimeHeaders();
	
        /*! Removes the MIME header with the specified name.
	    \param header - the name of the MIME header which is to be removed
	    \throw SOAPException - if the MIME header does not exist and thus cannot be
                                   deleted
	 */
        void removeMimeHeader(const std::string& header) throw (xoap::exception::Exception);
	
	void * operator new (size_t size );
	void operator delete (void * );
	
    protected:
	size_t len_;
	char * content_;
        std::map<std::string, std::string, std::less<std::string> > mimeHeaders_;
	//int * referenceCounterPtr_;
};

}

#endif	
