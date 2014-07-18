// $Id: SOAPMessage.h,v 1.5 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef xoap_SOAPMessage_h
#define xoap_SOAPMessage_h

#include <xercesc/dom/DOM.hpp>
XERCES_CPP_NAMESPACE_USE

#include <stdlib.h>
#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>

#include "xoap/SOAPPart.h"
#include "xoap/AttachmentPart.h"
#include "xoap/exception/Exception.h"
#include "xoap/MimeHeaders.h"

namespace xoap
{

/*! The root class for all SOAP messages. A SOAP message is an XML document or a MIME
    message whose first body part is an XML/SOAP document.
    
    A SOAPMessage object consists of a SOAP part and optionally one or more attachment parts.
    The SOAP part of a SOAPMessage object is a SOAPPart object. It contains information
    used for message routing and identification. In addition, it may contain
    application-specific content such as text messages. All data in the SOAP part of a SOAP
    message must be in XML format. An attachment is not required to be in XML format and may
    be anything from simple text to an image file.

    By default a new SOAPMessage object contains the following:
    - A SOAPPart object - mandatory
    - A SOAPEnvelope object - mandatory
    - A SOAPBody object - mandatory
    - A SOAPHeader object - optional (has not yet been implemented in XOAP)

    The SOAPPart object contains the SOAPEnvelope which again contains the SOAPHeader and
    the SOAPBody objects. By default the SOAPHeader object and the SOAPBody objects are
    empty when constructed. The SOAPHeader object is optional (and has not yet been implemented
    in XOAP). Both the SOAPBody and SOAPHeader objects can be removed and replaced (see the 
    documentation for the SOAPEnvelope object or the SOAPBody object for details). 
    However, note that only one SOAPBody object and one
    SOAPHeader object may be present at a time.

    A SOAPMessage object is simply created by declaring a SOAPMessage object. 
    The SOAPPart can be retrieved by calling the member function getSOAPPart(). The
    SOAPEnvelope can then be retrieved from the SOAPPart object, and from the SOAPEnvelope
    object the SOAPBody and SOAPHeader objects can be retrieved. The SOAPMessage class also provides
    member functions for creating AttachmentPart objects and for adding them to a SOAPMessage object.
    
    The following is a small example of how to create a SOAPMessage object, retrieve the SOAPEnvelope
    and how to create and add an AttachmentPart object:
    - SOAPMessage message;
    - SOAPPart soapPart = message.getSoapPart();
    - SOAPEnvelope envelope = message.getSoapEnvelope();
    - AttachmentPart * attachment = message.createAttachmentPart("/full_file_path_to_attachment/filename");
    - message.addAttachmentPart(attachment);
    
    Note that the \e createAttachmentPart member function only creates the AttachmentPart object.
    The AttachmentPart object has to be added to the SOAPMessage object using the \e addAttachmentPart 
    member function. See the AttachmentPart class for more details. Finally, it should be noted that
    AttachmentPart objects must not be empty. If an empty AttachmentPart object is created, it should
    be populated using one of the member functions \e setContent.
    MIME headers are set using the member functions:
    \e setContentType, \e setContentId, \e setContentEncoding, \e setContentLocation, and \e addMimeHeader 
    in the AttachmentPart class.
 */
class SOAPMessage {
    public:
        /*! Constructs a SOAPMessage object.
         */
        SOAPMessage() throw (xoap::exception::Exception);
        /*! Takes a text string representing a SOAP message and parses it, i.e. it turns the string
            into a SOAP message containing a SOAPEnvelope object and a SOAPBody object. 
            The SOAPBody object contains the XML data given
            in the input, and the SOAP message may contain one or more attachments.
            This constructor is useful for instance
            when having received a SOAP message. Using this constructor the SOAP message may be rebuild
            and the wanted information extracted.
            \param buf - a byte buffer representing a SOAP message
	    \param size - the size of the string
         */
        SOAPMessage(char* buf, size_t size) throw (xoap::exception::Exception);
	
        /*! Takes a DOM_Node as input and builds a SOAP message. The DOM_Node is expected to contain a tree
            representation of an already existing SOAP message. 
	    \param node - a DOM_Node which contains a DOM representation of an already existing SOAP message
         */
	SOAPMessage(DOMNode* node);

  	SOAPMessage( const SOAPMessage & msg );
  	SOAPMessage( SOAPMessage & msg );
	
	~SOAPMessage();

	SOAPMessage & operator=( const SOAPMessage & msg );
	
	/*! Parses the XML part of the entire SOAP message into a SOAPMessage object containing a SOAPEnvelope
            object and a SOAPBody object.
	    \param buf - a string giving the XML part of the SOAP message (i.e. excluding attachments)
            \param len - the length of the string
	    \throw string - if an error occurs during parsing
	 */
	void parseFrom(const char* buf, size_t len) throw (xoap::exception::Exception);
	
        /*! Returns the SOAPPart object, i.e. the root element which contains the SOAPEnvelope object, of this
            SOAPMessage object.
            \return Returns the SOAPPart object of this SOAPMessage object
        */
	SOAPPart getSOAPPart();
	
	/*! Writes this SOAPMessage object to the given output stream.
            \param ostream - the output stream to which this SOAP message will be written
	    \throw SOAPException - if any AttachmentPart objects are empty
         */
        void writeTo (std::ostream& stream) throw (xoap::exception::Exception);
	
        /*! Serializes a SOAP message to a string reference.
            \param destination - a string giving the name of the string reference
            \throw SOAPException - if any AttachmentPart objects are empty
         */
        void writeTo (std::string& destination) throw (xoap::exception::Exception);
	
        /*! Converts a byte buffer containing a SOAP message (optionally
            with attachments) into a SOAP message represented by this
            SOAPMessage object.
            \param buf - the byte buffer containing the SOAP message
            \param size - the size of the buffer
            \throw SOAPException - if the start or end of the SOAPMessage cannot be found,
	    if no MIME headers are found (the SOAPMessage should at least contain the MIME
	    header \e Content-Type), or if the start of the attachment could not be found
	 */
	void readFrom(const char* buf, size_t size) throw (xoap::exception::Exception);
	
	/*! Returns the SOAPEnvelope object as a DOM_Node object.
            \return the SOAPEnvelope object as a DOM node
         */
	DOMNode* getEnvelope();
	
	/*! Returns the DOM document representing the message
         */
	DOMDocument* getDocument();
	
        /*! Creates an empty AttachmentPart object. Note that it should
	    be populated using one of the member functions \e setContent.
            \return a pointer to the created AttachmentPart object which can be populated 
	    and added to this SOAPMessage object
         */
        AttachmentPart * createAttachmentPart();
	
	/*! Creates an AttachmentPart object which has been populated 
            with the content of the specified file.
	    \param file - the path to a file that contains the content 
            with which the AttachmentPart object
	    should be populated 
            \return a pointer to the created AttachmentPart object
	 */
	AttachmentPart * createAttachmentPart(const std::string& file) 
		throw (xoap::exception::Exception);
	
	/*! Creates a populated AttachmentPart object.
	    \param content - the content with which the AttachmentPart object should be populated
	    \param len - the length of the content given in bytes
	    \param type - the value of the MIME header \e Content-Type
            \return a pointer to the created AttachmentPart object
	 */
	AttachmentPart * createAttachmentPart(const char* content, size_t len, const std::string& type)
		throw (xoap::exception::Exception);
	
	/*! Adds the given AttachmentPart object to this SOAPMessage object. 
            An AttachmentPart object must be created before
	    it can be added to a SOAP message.
	    \param AttachmentPart - a pointer to the AttachmentPart object 
                                    which is to be added to this SOAPMessage object
	    \throw SOAPException - if trying to add an empty AttachmentPart object
	*/   
        void addAttachmentPart(AttachmentPart * a) 
		throw (xoap::exception::Exception);
	
        /*! Counts the number of attachments in this SOAP message. The count does not include the SOAP part.
            \return the number of AttachmentPart objects in this SOAPMessage object.
        */
        size_t countAttachments();
	
        /*! Retrieves all the AttachmentPart objects that are part of this SOAPMessage object.
            \return a list containing pointers to all the AttachmentPart objects which have
                    been added to this SOAP message
         */
        std::list<AttachmentPart*> getAttachments();
	
        /*! Sets the MIME boundary. The default name is \e XDAQ_Boundary.
	    \param boundary - a string containing the new name of the MIME boundary
            \throw SOAPException - if the MIME boundary does not begin with "--"
         */
        void setMimeBoundary(const std::string& boundary) 
		throw (xoap::exception::Exception);
	
        /*! Retrieves the name of the MIME boundary. 
            \return the name of the MIME boundary
         */
	std::string getMimeBoundary();
	
        /*! Removes all AttachmentPart objects which have been added to this SOAPMessage object. 
	    The AttachmentPart objects themselves still exist. This member function does not touch the SOAPPart object.
	 */
        void removeAllAttachments();
	
	/*! Removes the specified AttachmentPart object from this SOAPMessage object. The AttachmentPart
	    object itself still exists.
	    \param AttachmentPart - a pointer to the AttachmentPart object which should be removed
	 */
        void removeAttachment(AttachmentPart * attachment)
		throw (xoap::exception::Exception);
	
	/*! Create a new SOAP Message. Put the DOM inside and invalidate the original
	   message. It can be deleted safely without affecting the DOM 
	*/
	SOAPMessage* relocate();
	
	/*! Returns all the transport-specific MIME headers for this SOAPMessage object in a transport independent fashion.
	*/
	MimeHeaders* getMimeHeaders();
	
    protected:
	DOMDocument* 	doc_;
	DOMElement*     envelope_;
        std::list<AttachmentPart*> * aps_;
	std::list<AttachmentPart*> * remember_;
        std::string boundary_;
	int * referenceCounterPtr_;
        DOMBuilder* parser_;
	MimeHeaders headers_;
};

}

#endif
