// $Id: TimeVal.h,v 1.7 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_TimeVal_h_
#define _toolbox_TimeVal_h_

#include <sys/time.h>		
#include <unistd.h>		
#include <cmath>		
#include <string> 
#include <iostream>
#include "toolbox/TimeInterval.h"
#include "toolbox/exception/Exception.h"

namespace toolbox 
{

/*! 
 *
 * TimeVal is a wrapper around UNIX timeval structure.
 * 
 */
class TimeVal : public timeval
{
	public:
	
	typedef enum 
	{ 
		gmt,	// GMT 
		loc	// Local Time Zone 
	} TimeZone;

	// Default constructor. Sets time to 0 sec. 0 usecs. To get current time, use TimeVal (gettimeofday());
	TimeVal ();

	// Constructor from seconds/microseconds pair.
	TimeVal (time_t sec, suseconds_t usec);

	// Constructor from double.
	TimeVal (double d);

	// Constructor from <TT> struct timeval</TT>.
	TimeVal (const timeval& tv);

	// Copy constructor.
	TimeVal (const TimeVal& tv); 

	// Implicit conversion to double.
	operator double () const;

	// Set seconds.
	void sec (time_t sec) { tv_sec = sec; }

	// Get secons.
	time_t sec (void) const { return tv_sec; }

	// Set microsecs.
	void usec (suseconds_t msec) { tv_usec = msec; }

	// Get microsecs.
	suseconds_t usec (void) const { return tv_usec; }

	// Convert tv_usec (microseconds) to milliseconds (1 / 1,000 of a second)
	size_t millisec () const;

	// Set timezone.
	void tz (TimeZone tz) { m_tz = tz; }

	// Get timezone.
	TimeZone tz (void) const { return m_tz; }

	TimeVal& operator= (const TimeVal& tv);

	// Addition of TimeVal
	TimeVal& operator+= (const TimeVal& rhs);
	
	// Addition of TimeInterval
	TimeVal& operator+= (const TimeInterval& rhs);

	// Substraction of TimeVal
	TimeVal& operator-= (const TimeVal& rhs);
	
	// Substraction of TimeInterval
	TimeVal& operator-= (const TimeInterval& rhs);

	// Addition of TimeVal
	friend TimeVal operator+(const TimeVal& lhs, const TimeVal& rhs);
	
	// Addition of TimeInterval
	friend TimeVal operator+(const TimeVal& lhs, const TimeInterval& rhs);

	// Substraction of TimeVal
	friend TimeVal operator-(const TimeVal& lhs, const TimeVal& rhs);
	
	// Substraction of TimeInterval
	friend TimeVal operator-(const TimeVal& lhs, const TimeInterval& rhs);

	// Comparison.
	bool operator< (const TimeVal& rhs) const;

	// Equality.
	bool operator==(const TimeVal& rhs) const;

	// Comparison.
	friend bool operator> (const TimeVal& lhs, const TimeVal& rhs);

	// Comparison.
	friend bool operator!=(const TimeVal& lhs, const TimeVal& rhs);

	// Comparison.
	friend bool operator<=(const TimeVal& lhs, const TimeVal& rhs);

	// Comparison.
	friend bool operator>=(const TimeVal& lhs, const TimeVal& rhs);

	/*! Format timeval structure into readable format.
	    Default format is CCYY/DDD HH:MM:SS.MMM which is de fasco
	    for the software. To get something different, pass fmt_
	    format string as specified by strftime(3). Popular format
	    is "%c" which will return something like: 
	    "Fri Oct 1 10:54:27 1999". Note that timezone aspect of
	    formatting time is controlled by tz() member function.
	    @param fmt_ Format string as in strftime(3)
	    Note: The conversion toString does not take into consideration microseconds
	    @return Formatted string.
	*/
	std::string toString (TimeZone tz) const;
	std::string toString (const std::string& fmt, TimeZone tz) const;

	/*! Reverse of toString, does not take into consideration microseconds if a \param fmt format is used.
		\throws toolbox::exception::Exception if parsing fails for any reason
	*/
	void fromString (const std::string& s, const std::string& fmt, TimeZone tz)
		throw (toolbox::exception::Exception);

	//! Static that returns zero timeval: {0,0}
	static TimeVal zero () { return m_zero; }

	/** Shields off underlying OS differences in getting
	    current time.
	    @return time of the day as timeval in GMT timezone
	*/
	static TimeVal gettimeofday ();

protected:
	// Internal initialization common to most constructors.
	void init (time_t, suseconds_t, TimeZone);

private:
	// Normalization after arithmetic operation.
	void normalize ();

private:
	// Time zone
	TimeZone m_tz;

	// Zero time value
	static TimeVal m_zero;
};

//------------------------------------------------------------------------------
// Inlines
//------------------------------------------------------------------------------

inline void TimeVal::init (time_t s, suseconds_t ms, TimeZone tz)
{
	tv_sec = s;
	tv_usec = ms;
	m_tz = tz;
	normalize ();
}

inline TimeVal::TimeVal ()
{
	init (0, 0, gmt);
}

inline TimeVal::TimeVal (time_t sec, suseconds_t usec) 
{
	init (sec, usec, gmt);
}

inline TimeVal::TimeVal (double d)
	: m_tz (gmt)
{
	time_t s = time_t(d);
	tv_sec = s;
	tv_usec = (suseconds_t) std::floor(((d - double(s))*1000000.0) + 0.5 );
	normalize();
}

inline TimeVal::TimeVal (const timeval& tv)
{
	init (tv.tv_sec, tv.tv_usec, gmt);
}

inline TimeVal::TimeVal (const TimeVal& tv)
{
	init (tv.tv_sec, tv.tv_usec, tv.m_tz);
}

inline TimeVal TimeVal::gettimeofday () 
{ 

	timeval tv;
	::gettimeofday (&tv, 0); // in GMT
	
	return tv;
}

inline TimeVal::operator double () const
{ 
	return tv_sec + tv_usec / 1000000.0;
}

inline size_t TimeVal::millisec () const
{
	return (this->usec () % 1000000) / 1000;
}



//------------------------------------------------------------------------------
// Friend functions
//------------------------------------------------------------------------------

inline TimeVal& TimeVal:: operator=(const TimeVal& tv)
{
	init (tv.tv_sec, tv.tv_usec, tv.m_tz);
	return *this;
}

inline TimeVal operator+(const TimeVal& lhs, const TimeVal& rhs)
{
	TimeVal temp(lhs);
	temp += rhs;
	temp.normalize ();
	return temp;
}

inline TimeVal operator+(const TimeVal& lhs, const TimeInterval& rhs)
{
	TimeVal temp(lhs);
	temp += rhs;
	temp.normalize ();
	return temp;
}

inline TimeVal operator-(const TimeVal& lhs, const TimeVal& rhs)
{
	TimeVal temp(lhs);
	temp -= rhs;
	temp.normalize ();
	return temp;
}

inline TimeVal operator-(const TimeVal& lhs, const TimeInterval& rhs)
{
	TimeVal temp(lhs);
	temp -= rhs;
	temp.normalize ();
	return temp;
}

inline bool  TimeVal::operator<(const TimeVal& rhs) const
{
	return (tv_sec < rhs.tv_sec
		|| (tv_sec == rhs.tv_sec && tv_usec < rhs.tv_usec) ) ;
}

inline bool  TimeVal::operator==(const TimeVal& rhs) const
{
	return !(*this < rhs || rhs < *this);
}

inline bool operator> (const TimeVal& lhs, const TimeVal& rhs)
{
	return rhs < lhs;
}

inline bool operator!=(const TimeVal& lhs, const TimeVal& rhs)
{
	return !( lhs == rhs );
}

inline bool operator<=(const TimeVal& lhs, const TimeVal& rhs)
{
	return !(rhs < lhs);
}

inline bool operator>=(const TimeVal& lhs, const TimeVal& rhs)
{
	return !(lhs < rhs);
}

} // end namespace toolbox

#endif 
