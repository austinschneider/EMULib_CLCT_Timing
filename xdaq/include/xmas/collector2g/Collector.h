// $Id: Collector.h,v 1.8 2008/08/27 15:30:58 lorsini Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_collector2g_Collector_h_
#define _xmas_collector2g_Collector_h_

#include <string>
#include "toolbox/BSem.h"
#include "toolbox/TimeVal.h"
#include "xdata/Table.h"
#include "xdata/TableIndex.h"
#include "xdata/Properties.h"
#include "xdata/exdr/Serializer.h"
#include "xdata/UnsignedInteger64.h"
#include "xmas/exception/Exception.h"
#include "xmas/collector2g/exception/FailedSerialization.h"
#include "xmas/collector2g/exception/NoData.h"
#include "xmas/collector2g/Topic.h"

#include "toolbox/ActionListener.h"
#include "toolbox/Properties.h"
#include "toolbox/mem/Reference.h"
#include "toolbox/task/AsynchronousEventDispatcher.h"

namespace xmas
{
	namespace collector2g
	{
		class Collector: public toolbox::Properties, public toolbox::ActionListener
		{
			public:
			
			Collector(xmas::collector2g::Topic setting)
				throw(xmas::collector2g::exception::Exception);
			
			virtual ~Collector();

			//! re-write internal table
			//
			void setData(xdata::Table::Reference& data, xdata::Properties & plist); 
			
			//! Merge data into cached data table or set cached data to table passed if no data are cached yet
			//
			void mergeData(xdata::Table::Reference& data, xdata::Properties & plist) throw (xmas::exception::Exception);
			
			//! Clear table rows that match column \param name with \param value
			//
			void clear(const std::string& name, const std::string& value) throw (xmas::exception::Exception);
			
			//! Clear all data rows 
			//
			void clear() throw (xmas::exception::Exception);

			// ! Reset all collected data , definitions and indexing information
			void reset() throw (xmas::exception::Exception);
			
			// The following functions are not thread-safe and locking is required
			//
			std::string getName();
			bool hasData();
			toolbox::TimeVal getLastUpdate();
			std::string getVersion();
			std::string getTags();
			std::string getLastOriginator();
			size_t getRowCount();
			size_t getLostCounter();
			size_t getDataEventCounter();
			
			/* Serialize cached data into the buffer provided. Set flashlist name and version into the passed plist
			   If the Settings has 'clear=true' set, clear the internal cached data table after the operation
			*/
			void extractDataCollection(toolbox::mem::Reference *  ref, xdata::Properties & plist) 
				throw (xmas::collector2g::exception::NoData, xmas::collector2g::exception::FailedSerialization);		     
			
			toolbox::task::AsynchronousEventDispatcher& getDispatcher();
			
			Topic  getTopic();
			
			void actionPerformed(toolbox::Event& e);
			
			// Statistics retrieval
			//
			double getAverageMergeTime();
			double getDataMergeRate();
			double getAverageDeserializeTime();
			double getDataDeserializeRate();
			

			bool hasChanged();

			void incrementSerializationFailedCounter();
                        void incrementFireCounter();
                        void incrementInternalLossCounter();
                        void incrementCommunicationLossCounter();
                        void incrementMemoryLossCounter();
                        void incrementUnassignedLossCounter();

                        xdata::UnsignedInteger64T getSerializationFailedCounter();
                        xdata::UnsignedInteger64T getFireCounter();
                        xdata::UnsignedInteger64T getInternalLossCounter();
                        xdata::UnsignedInteger64T getCommunicationLossCounter();
                        xdata::UnsignedInteger64T getMemoryLossCounter();
                        xdata::UnsignedInteger64T getUnassignedLossCounter();

			
			private:
			
			bool match 
			(
				xdata::Table::Reference& table,
				size_t row, 
				std::map<std::string, std::string>& filter
			);
			
			toolbox::task::AsynchronousEventDispatcher dispatcher_;
			
			xmas::collector2g::Topic settings_;			
			toolbox::BSem mutex_;
			bool hasData_;
			
			xdata::Table::Reference data_;
			xdata::TableIndex* index_;
			toolbox::TimeVal firstUpdate_;
			toolbox::TimeVal lastUpdate_;
			toolbox::TimeVal lastOutput_;
			std::string version_;
			std::string tags_;
			std::string lastOriginator_;
			std::string name_; // flashlistname
			xdata::exdr::Serializer serializer_;
			
			// statistics data
			double averageMergeTime_; // in seconds
			double averageMergeRate_;
			size_t dataEventCounter_; // counts incoming data events
			size_t dataEventLostCounter_;
			double averageDeserializeTime_; // in seconds
			double averageDeserializeRate_;

       			xdata::UnsignedInteger64T monitorSerializationFailedCounter_;
                        xdata::UnsignedInteger64T monitorFireCounter_;

                        xdata::UnsignedInteger64T monitorInternalLossCounter_;
                        xdata::UnsignedInteger64T monitorCommunicationLossCounter_;
                        xdata::UnsignedInteger64T monitorMemoryLossCounter_;
                        xdata::UnsignedInteger64T monitorUnassignedLossCounter_;

		};
	}
}
#endif
