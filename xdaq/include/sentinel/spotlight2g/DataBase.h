// $Id: DataBase.h,v 1.10 2008/11/25 13:21:03 lorsini Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _sentinel_spotlight2g_DataBase_h_
#define _sentinel_spotlight2g_DataBase_h_

#include <string>
#include <map>
#include <sqlite3.h>

#include "sentinel/spotlight2g/exception/FailedToStore.h"
#include "sentinel/spotlight2g/exception/FailedToRead.h"
#include "sentinel/spotlight2g/exception/FailedToOpen.h"
#include "sentinel/spotlight2g/exception/FailedToClose.h"
#include "sentinel/spotlight2g/exception/NotFound.h"
#include "sentinel/spotlight2g/exception/FailedToArchive.h"
#include "sentinel/spotlight2g/exception/FailedToRemove.h"
#include "sentinel/spotlight2g/exception/ConstraintViolated.h"
#include "toolbox/Properties.h"

namespace sentinel 
{
	namespace spotlight2g 
	{
		class DataBase
		{
			public:

			DataBase(const std::string& path, bool readOnly )
				throw (sentinel::spotlight2g::exception::FailedToOpen);
			~DataBase();			

			static void hasInsertedfirstRow(bool b);
				
			void mask (double startTime, double endTime, const std::string & exception, const std::string & source, const std::string  &filter )
				throw (sentinel::spotlight2g::exception::FailedToStore, sentinel::spotlight2g::exception::ConstraintViolated);
				
			void unmask (const std::string & mask, const std::string & exception, double endTime )
				throw (sentinel::spotlight2g::exception::FailedToStore, sentinel::spotlight2g::exception::ConstraintViolated);
															
			/*! Store an exception object
				This function is thread safe (read/write lock)
			*/
			void store (xcept::Exception& ex)
				throw (sentinel::spotlight2g::exception::FailedToStore, sentinel::spotlight2g::exception::ConstraintViolated);
				
			void rearm (const std::string & exception, const std::string & source)
				throw (sentinel::spotlight2g::exception::FailedToStore, sentinel::spotlight2g::exception::ConstraintViolated);
	
			void revoke (xcept::Exception& ex)
				throw (sentinel::spotlight2g::exception::FailedToStore, sentinel::spotlight2g::exception::ConstraintViolated);
	
			/*! Store an exception, all values are in the properties object
				The function does not store a chained exception (blob) 
			*/
			void store (toolbox::Properties& properties, const std::string & blob)
				throw (sentinel::spotlight2g::exception::FailedToStore, sentinel::spotlight2g::exception::ConstraintViolated);
				
			void event (const std::string & type, toolbox::Properties& properties)
				throw (sentinel::spotlight2g::exception::FailedToStore, sentinel::spotlight2g::exception::ConstraintViolated);	
			
			/*! Check if database contain the exception for uuid
                        */
			bool hasException (const std::string& uuid) ;

			/*! Retrieve a single exception by uuid in the format it has been stored.
				The name of the format is returned in \param format.
			*/
			void retrieve (const std::string& uuid, const std::string& format, xgi::Output* out) 
				throw (sentinel::spotlight2g::exception::NotFound);

			/*! Return a list of stored exceptions in the \param ex set that match the search query 
				This function is thread safe (read lock)*/
			
			void catalog (xgi::Output* out, toolbox::TimeVal & start, toolbox::TimeVal & end, const std::string& format)
				throw (sentinel::spotlight2g::exception::NotFound);
			
			/*! Return a list of stored exceptions in the \param ex set that match the search query , order desc by dateTime
			*/	
			void catalog (toolbox::TimeVal & age, int (*callback)(void*,int,char**,char**)  , void * context)
				throw (sentinel::spotlight2g::exception::FailedToArchive);
				
			void events (xgi::Output* out, toolbox::TimeVal & start, toolbox::TimeVal & end, const std::string& format)
				throw (sentinel::spotlight2g::exception::NotFound);
	
			void lastStoredEvents(xgi::Output* out, toolbox::TimeVal & since, const std::string& format)
				throw (sentinel::spotlight2g::exception::NotFound);
	
			void remove(toolbox::TimeVal & age)
					throw (sentinel::spotlight2g::exception::FailedToRemove);

			/*! Retrieve the time at which the last exception has been stored from the database */
			toolbox::TimeVal getLatestStoreTime();

			/*! Retrieve the time of the most recent exception in the database */
			toolbox::TimeVal getLatestExceptionTime();

			/*! Retrieve the time of the oldest exception in the database */
			toolbox::TimeVal getOldestExceptionTime();

			/*! Retrieve the number of exceptions stored */
			std::string getNumberOfExceptions();

			size_t getSize();
						
			/*! Average time to store a single exception */
			double getAverageTimeToStore();
			
			/*! Average time to retrieve a catalog */
			double getAverageTimeToRetrieveCatalog();
			
			/*! Average time to retrieve a single exception by uuid */
			double getAverageTimeToRetrieveException();
			
			void writeBlob(const std::string & zKey, const std::string & zBlob)
				throw (sentinel::spotlight2g::exception::FailedToStore);
				
			void readBlob(const std::string& zKey, std::string& pzBlob)
				throw (sentinel::spotlight2g::exception::FailedToRead);
				
			std::string getFileName();
			
			void lock();
			
			void unlock();
			
			// Vacuum the database, other operations TBD
			//
			void maintenance() throw (sentinel::spotlight2g::exception::Exception);
			
			private:
			
			void prepareDatabase (bool readOnly)
				throw (sentinel::spotlight2g::exception::FailedToOpen);
					
			std::string escape(const std::string& s);
			
			toolbox::BSem lock_; // used for db management operations
			sqlite3 *db_;
			sqlite3_stmt* insertCatalogStmt_;
			sqlite3_stmt* insertExceptionStmt_;
			sqlite3_stmt* insertApplicationStmt_;
			sqlite3_stmt* insertEventStmt_;
			sqlite3_stmt* insertMaskStmt_;

			
			std::string filename_;
			double averageTimeToStore_;
			double averageTimeToRetrieveCatalog_;
			double averageTimeToRetrieveException_;
			toolbox::TimeVal lastExceptionTime_;	
		};
	}
}
#endif
