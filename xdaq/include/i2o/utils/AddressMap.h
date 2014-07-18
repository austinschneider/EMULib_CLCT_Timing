// $Id: AddressMap.h,v 1.3 2008/07/18 15:26:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _i2o_utils_AddressMap_h_
#define _i2o_utils_AddressMap_h_

#include "i2o/i2oDdmLib.h"

#include<string>
#include<map>

#include "xdaq/ApplicationDescriptor.h"
#include "xdaq/exception/ApplicationDescriptorNotFound.h"

namespace i2o
{
	namespace utils
	{
		class AddressMap
		{
			public:
			
			//! Returns a pointer to an application descriptor. The parameter is an I2O tid
			/*! This function provides access to the mapping of I2O unique tids to 
	 		     *  application descriptors. If no mapping exists, an exception is thrown.
	 		     */
			xdaq::ApplicationDescriptor* getApplicationDescriptor(I2O_TID tid) throw (xdaq::exception::ApplicationDescriptorNotFound);

			//! Returns a I2O target address. The parameter is an xdaq application descriptor.
			/*! This function provides access to the mapping of I2O unique tids to 
	 			*  application descriptors. If no mapping exists, an excception is thrown,
				 */
			I2O_TID getTid(xdaq::ApplicationDescriptor* descriptor) throw (xdaq::exception::ApplicationDescriptorNotFound);

			//! Set the I2O tid for an application descriptor
			/*! This function allows to associate a unique I2O tid with an application descriptor.
        		 *  If a mapping exists already it will be overwritten.
         		*/
			void setApplicationDescriptor (I2O_TID tid, xdaq::ApplicationDescriptor* descriptor);


			//! Remove an I2O target identifier to application descriptor mapping.
			/*! Remove an existing mapping of an I2O target identifier to an xdaq application
         		*  descriptor. If no existing mapping is found, the function throws an exception.
			 */
			void removeTid (I2O_TID tid) throw (xdaq::exception::ApplicationDescriptorNotFound);
				
			void clear();
			
			//! Retrieve a pointer to the toolbox::task::WorkLoopFactory singleton
			//
			static AddressMap* getInstance();
			
			//! Destoy the factory and all associated work loops
			//
			static void destroyInstance();
			
			private:
			
			static AddressMap* instance_;
			
			std::map<I2O_TID, xdaq::ApplicationDescriptor*, std::less<I2O_TID> > tidToApplication_;
			std::map<xdaq::ApplicationDescriptor*, I2O_TID, std::less<xdaq::ApplicationDescriptor*> > applicationToTid_;
		};
		
		//! Retrieve a pointer to the toolbox::task::WorkLoopFactory singleton
		//
		AddressMap* getAddressMap();
	}
}

#endif
