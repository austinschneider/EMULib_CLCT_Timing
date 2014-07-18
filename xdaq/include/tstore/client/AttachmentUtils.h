#include "xdata/Table.h"
#include "xoap/MessageReference.h"
#include "xoap/exception/Exception.h"

namespace tstoreclient {
//A few utility functions for converting xdata::Serializable objects to and from attachments.
//these should probably be in xoap

//copies the attachment with the given content ID into attachment. 
//Returns false and does not touch attachment if no such attachment was found.
//Throws an exception if the attachment with the given content ID is not of the same type as the attachment parameter.
//Throws an exception if the attachment could not be read.
bool getAttachmentWithID(xoap::MessageReference nessage,xdata::Serializable &attachment,std::string contentID) throw (xoap::exception::Exception);

//copies the first attachment with the appropriate content type into attachment.
//Returns false and does not touch attachment if no such attachment was found.
//Throws an exception if the attachment could not be read.
bool getFirstAttachmentOfType(xoap::MessageReference nessage,xdata::Serializable &attachment) throw (xoap::exception::Exception);

//attaches the given data to the message, with the given content-ID
void addAttachment(xoap::MessageReference message,xdata::Serializable &data,std::string contentId) throw (xoap::exception::Exception);
}
