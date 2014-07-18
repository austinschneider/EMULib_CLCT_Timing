// $Id: TimeInterval.h,v 1.4 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_TimeInterval_h_
#define _toolbox_TimeInterval_h_

#include <sys/time.h>		
#include <unistd.h>		

#include <string> 
#include "toolbox/exception/Exception.h"

namespace toolbox 
{

/*! 
 *
 * TimeVal is a wrapper around UNIX timeval structure.
 * 
 */
class TimeInterval : public timeval
{
	public:
	
	// Default constructor. Sets time to 0 sec. 0 usecs. To get current time, use TimeVal (gettimeofday());
	TimeInterval ();

	// Constructor from seconds/microseconds pair.
	TimeInterval (time_t sec, suseconds_t usec);

	// Constructor from double.
	TimeInterval (double d);

	// Constructor from <TT> struct timeval</TT>.
	TimeInterval (const timeval& tv);

	// Copy constructor.
	TimeInterval (const TimeInterval& tv); 

	// Implicit conversion to double.
	operator double () const;

	// Set seconds.
	void sec (time_t sec) { tv_sec = sec; }

	// Get secons.
	time_t sec (void) const { return tv_sec; }

	// Set microsecs.
	void usec (suseconds_t usec) { tv_usec = usec; }

	// Get microsecs.
	suseconds_t usec (void) const { return tv_usec; }

	// Convert tv_usec (microseconds) to milliseconds (1 / 1,000 of a second)
	size_t millisec () const;

	TimeInterval& operator= (const TimeInterval& tv);

	// Addition.
	TimeInterval& operator+= (const TimeInterval& rhs);

	// Substraction.
	TimeInterval& operator-= (const TimeInterval& rhs);

	// Addition.
	friend TimeInterval operator+(const TimeInterval& lhs, const TimeInterval& rhs);

	// Substraction.
	friend TimeInterval operator-(const TimeInterval& lhs, const TimeInterval& rhs);

	// Comparison.
	bool operator< (const TimeInterval& rhs) const;

	// Equality.
	bool operator==(const TimeInterval& rhs) const;

	// Comparison.
	friend bool operator> (const TimeInterval& lhs, const TimeInterval& rhs);

	// Comparison.
	friend bool operator!=(const TimeInterval& lhs, const TimeInterval& rhs);

	// Comparison.
	friend bool operator<=(const TimeInterval& lhs, const TimeInterval& rhs);

	// Comparison.
	friend bool operator>=(const TimeInterval& lhs, const TimeInterval& rhs);

	/*! Format timeval structure into readable format.
	    Default format is CCYY/DDD HH:MM:SS.MMM 
	    \returns formatted string.
	*/
	std::string toString () const;
	
	/* Format timeval structure into a readable format.
	   If the format \param fmt is empty or "xs:duration", the W3C format
	   The duration data type is used to specify a time interval.

		The time interval is specified in the following W3C xs:duration form "PnYnMnDTnHnMnS" where:

		P indicates the period (required)
		nY indicates the number of years
		nM indicates the number of months
		nD indicates the number of days
		T indicates the start of a time section (required if you are going to specify hours, minutes, or seconds)
		nH indicates the number of hours
		nM indicates the number of minutes
		nS indicates the number of seconds
	    \returns formatted string.
	*/
	std::string toString (const std::string& fmt) const;

	/* Reverse as toString */
	void fromString (const std::string& s) throw (toolbox::exception::Exception);

protected:
	// Internal initialization common to most constructors.
	void init (time_t sec, suseconds_t usec);

private:
	// Normalization after arithmetic operation.
	void normalize ();
};

//------------------------------------------------------------------------------
// Inlines
//------------------------------------------------------------------------------

inline void TimeInterval::init (time_t s, suseconds_t ms)
{
	tv_sec = s;
	tv_usec = ms;
	normalize ();
}

inline TimeInterval::TimeInterval ()
{
	init (0, 0);
}

inline TimeInterval::TimeInterval (time_t sec, suseconds_t usec) 
{
	init (sec, usec);
}

inline TimeInterval::TimeInterval (double d)
{
	time_t s = time_t(d);
	tv_sec = s;
	tv_usec = (suseconds_t) ((d - double(s))*1000000.0);
	normalize();
}

inline TimeInterval::TimeInterval (const timeval& tv)
{
	init (tv.tv_sec, tv.tv_usec);
}

inline TimeInterval::TimeInterval (const TimeInterval& tv)
{
	init (tv.tv_sec, tv.tv_usec);
}

inline TimeInterval::operator double () const
{ 
	return tv_sec + tv_usec / 1000000.0;
}

inline size_t TimeInterval::millisec () const
{
	return (this->usec () % 1000000) / 1000;
}

//------------------------------------------------------------------------------
// Friend functions
//------------------------------------------------------------------------------

inline TimeInterval& TimeInterval:: operator=(const TimeInterval& tv)
{
	init (tv.tv_sec, tv.tv_usec);
	return *this;
}

inline TimeInterval operator+(const TimeInterval& lhs, const TimeInterval& rhs)
{
	TimeInterval temp(lhs);
	temp += rhs;
	temp.normalize ();
	return temp;
}

inline TimeInterval operator-(const TimeInterval& lhs, const TimeInterval& rhs)
{
	TimeInterval temp(lhs);
	temp -= rhs;
	temp.normalize ();
	return temp;
}

inline bool  TimeInterval::operator<(const TimeInterval& rhs) const
{
	return (tv_sec < rhs.tv_sec
		|| (tv_sec == rhs.tv_sec && tv_usec < rhs.tv_usec) ) ;
}

inline bool  TimeInterval::operator==(const TimeInterval& rhs) const
{
	return !(*this < rhs || rhs < *this);
}

inline bool operator> (const TimeInterval& lhs, const TimeInterval& rhs)
{
	return rhs < lhs;
}

inline bool operator!=(const TimeInterval& lhs, const TimeInterval& rhs)
{
	return !( lhs == rhs );
}

inline bool operator<=(const TimeInterval& lhs, const TimeInterval& rhs)
{
	return !(rhs < lhs);
}

inline bool operator>=(const TimeInterval& lhs, const TimeInterval& rhs)
{
	return !(lhs < rhs);
}

} // end namespace toolbox

#endif 
