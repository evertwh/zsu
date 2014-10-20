//
//  Rev:          $Id: Week.cpp,v 1.5 2005/08/08 14:13:15 evert Exp $
//
//  Author:       Evert Haasdijk
//  Contact:      evert@zukkespijkers.nl
//
//  copyright (c) 2003 - 2004 Zukke Spijkers BV
//
//  This file is part of the Zukke Spijkers Utilities Library.
//
//  The Zukke Spijkers Utilities Library is free software; you can redistribute
//  it and/or modify it under the terms of the GNU General Public License as
//  published by the Free Software Foundation; either version 2 of the License,
//  or (at your option) any later version.
//
//  The Zukke Spijkers Utilities Library is distributed in the hope that it
//  will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with the Zukke Spijkers Utilities Library; if not, write to the Free
//  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,
//  MA  02111-1307  USA
//
//---------------------------------------------------------------------------
     
static const char* sccsid = "$Id: Week.cpp,v 1.5 2005/08/08 14:13:15 evert Exp $";

#include <zsu/Week.h>

using namespace zsu;     
using namespace boost::gregorian;
//---------------------------------------------------------------------------
boost::gregorian::date_period week::make(const boost::gregorian::date& someday)
{
  // Find Monday before and construct 7-day period
  first_kday_before mon(Monday);
  date d = someday;
  if (someday.day_of_week() != Monday)
    d = mon.get_date(someday);
  day_iterator i(d, 7);
  return date_period(d, *(++i));
}
//---------------------------------------------------------------------------

/// Constructs a Week for ISO 8601 week number \a number in \a year.
boost::gregorian::date_period week::make(unsigned number, boost::gregorian::greg_year year)
{
  boost::gregorian::date start(year, Jan, 4);   // Jan 4 by definition falls in week 1
  // create week iterator and increment that by number-1
  week_iterator i(start, number - 1);
  ++i;

  return week::make(*i);
}
//---------------------------------------------------------------------------

/// Constructs an empty Week
boost::gregorian::date_period week::makeEmptyWeek(void)
{
  return date_period(date(not_a_date_time), date(not_a_date_time));
}
//---------------------------------------------------------------------------

