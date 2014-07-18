// $Id: FlashlistData.h,v 1.8 2008/09/02 07:16:46 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_las2g_FlashlistData_h_
#define _xmas_las2g_FlashlistData_h_

#include <string>
#include "toolbox/BSem.h"
#include "toolbox/TimeVal.h"
#include "xdata/Table.h"
#include "xdata/Properties.h"
#include "xmas/FlashListDefinition.h"
#include "xmas/exception/Exception.h"
#include "xmas/las2g/exception/Exception.h"
#include "toolbox/mem/Reference.h"
#include "xdata/exdr/Serializer.h"

namespace xmas
{
	namespace las2g
	{
		class FlashlistData: public toolbox::Properties
		{
			public:
			
			FlashlistData();
			
			virtual ~FlashlistData();
						
			//void setData(xdata::Table::Reference& data, xdata::Properties & plist); // re-write internal table
			void setData(toolbox::mem::Reference * ref, xdata::Properties & plist); // re-write internal table

			void reset();
			
			// The following functions are not thread-safe and locking is required
			//
			bool hasData();
			toolbox::TimeVal& getLastUpdate();
			std::string getVersion();
			std::string getTags();
			std::string getLastOriginator();
			size_t getSize();
			
			void lock();
			void unlock();
			
			void toEXDR(std::ostream& out, std::map<std::string, std::string>& filter)
				throw (xmas::las2g::exception::Exception);		     
			void toJSON(std::ostream& out, std::map<std::string, std::string>& filter)
				throw (xmas::las2g::exception::Exception);
			void toHTML(std::ostream& out, std::map<std::string, std::string>& filter)
				throw (xmas::las2g::exception::Exception);
			void toCSV(std::ostream& out, std::map<std::string, std::string>& filter)
				throw (xmas::las2g::exception::Exception);
			
			private:
			xdata::Table *  getDataTable()
					throw (xmas::las2g::exception::Exception);

			// helper function to stream an inner table
			//
			void toJSON(std::ostream& out, xdata::Table* table, const std::string & tablename);
			void displayTableToHTML( std::ostream& out, xdata::Serializable * s );
			
			bool match 
			(
				xdata::Table * table,
				size_t row, 
				std::map<std::string, std::string>& filter
			);
			
			toolbox::BSem mutex_;
			bool hasData_;
			
			//xdata::Table::Reference data_;
			toolbox::mem::Reference * ref_;
			toolbox::TimeVal lastUpdate_;
			toolbox::TimeVal lastSerialized_;
			std::string version_;
			std::string tags_;
			std::string lastOriginator_;
			std::string name_; // flashlistname
			xdata::exdr::Serializer serializer_;
			xdata::Table *  table_; //cached table

			
		};
	}
}
#endif
