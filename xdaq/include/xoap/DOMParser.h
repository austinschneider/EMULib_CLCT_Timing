#ifndef _xoap_DOMParser_h_
#define _xoap_DOMParser_h_

#include <string>
#include <map>
#include <sstream>
#include "toolbox/BSem.h"
#include "xoap/exception/Exception.h"

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/AbstractDOMParser.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMBuilder.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMError.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMError.hpp>
#include <xercesc/dom/DOMLocator.hpp>
#include <xercesc/util/XMLURL.hpp>

//#include <xercesc/dom/DOM.hpp>
#include "xercesc/framework/MemBufInputSource.hpp"
#include "xercesc/framework/Wrapper4InputSource.hpp"

XERCES_CPP_NAMESPACE_USE

namespace xoap
{

	/*! Default implementation of an error handler for parsing XML documents
 	 * with the xoap::DOMParser class.
	 * This class can be extended to provide user specific error handling.
	 * An error handler should be passed to the DOMParser right before
	 * parsing starts.
	*/
	class DOMParserErrorHandler : public DOMErrorHandler
	{
		public:
	
			DOMParserErrorHandler();

			//! Callback in case of parsing errors
			bool handleError (const DOMError &domError);

			//! Return true if an error during parsing has been detected.
			bool hasErrors();

			//! Return a string with the error message indicating also line and column of the error.
			std::string getError();

			//! Reset the error handler and the stored error messages
			void resetErrors();
	   
		protected:
			std::ostringstream msg_;
			bool errors_;								
	};

	class DOMParser
	{
		public:

		/*! Create a new DOMParser. 
		   * Assume the Xerces XML system has been initialized. 
		   * Throws an exception if the XML system is not initialized or the parser cannot be created.
		   */
		DOMParser() throw (xoap::exception::Exception);
		~DOMParser();		
		
		/* Parse an XML content contained by the string \param data and
		   * return a DOM document. The parser works with namespaces.
		   */
		DOMDocument* parse(const std::string& data) throw (xoap::exception::Exception);
		
		/* Parse an XML content contained by the string \param data and
		   * return a DOM document. The parser works with namespaces.
		   */
		DOMDocument* parse( const char* c_data, size_t size ) throw(xoap::exception::Exception);
		
		/* Parse an XML content contained by the url \param data and
		   * return a DOM document. The parser works with namespaces.
		   */
		DOMDocument* parse(const XMLURL & url) throw (xoap::exception::Exception);
		
		/*! Static function that takes any kind of URL and internally decides
		    how to load the document 
		 */
		DOMDocument* loadXML (const std::string& url) throw (xoap::exception::Exception);
		
		void lock();
		
		void unlock();
		
		private:
				
		DOMImplementation	*impl;
		DOMBuilder		*parser;
		toolbox::BSem		mutex_;
	};	
}

#endif
