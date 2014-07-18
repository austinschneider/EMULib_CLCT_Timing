// $Id: HTTPLoader.h,v 1.5 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef xoap_HTTPLoader_h
#define xoap_HTTPLoader_h

#include <iostream>
#include <string>
#include <fstream>

#include "xercesc/util/PlatformUtils.hpp"
#include "xercesc/util/XMLNetAccessor.hpp"
#include "xercesc/util/BinInputStream.hpp"
#include "xercesc/util/XMLURL.hpp"

#include "xoap/exception/Exception.h"

XERCES_CPP_NAMESPACE_USE

// #include "util/NetAccessors/Socket/SocketNetAccessor.hpp"
// #include "util/NetAccessors/Socket/UnixHTTPURLInputStream.hpp"


namespace xoap
{

class HTTPLoader
{
        XMLByte* 		buffer;
        int 			bufferSize;
        // SocketNetAccessor* 	accessor;

        public:
	
		//! Start the HTTPLoader and optionally
		//! initialize the Xerces XML subsystem
		//! The size of the intermediate donload
		//! buffer is set to 16 KBytes.
		//
                HTTPLoader (bool xmlInitialize) throw (xoap::exception::Exception);
		
		//! Start the HTTPLoader, optionally initialize
		//! the Xerces XML subsystem and pass the size
		//! for the intermediate download buffer.
		//
		HTTPLoader (bool xmlInitialize, int size) throw (xoap::exception::Exception);
		
		~HTTPLoader ();
		
		//! Get the file from the url and return it in
		//! a string buffer
		//
		int get (const std::string& url, std::string& fileBuf)
			throw (xoap::exception::Exception);
		
		//! Get a file from url and stores the file into the given path (directory)
                //! If the path is empty, the file will be downloaded
		//! into the current folder ("./")
		//
		int store (const std::string& url, const std::string& path)
			throw (xoap::exception::Exception);
	
	protected:	
	
		// Intermediate initialization function called by CTOR
		//
		void init (bool xmlInitialize, int size) throw (xoap::exception::Exception);
};

}
#endif
