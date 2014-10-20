//
//  Rev:          $Id: Week.h,v 1.4 2004/05/11 07:19:12 evert Exp $
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

#ifndef WeekH
#define WeekH
//---------------------------------------------------------------------------
                      
#include <zsu/config.h>

#include <boost/date_time/gregorian/gregorian_types.hpp>

//---------------------------------------------------------------------------

namespace zsu
{
//---------------------------------------------------------------------------
/**
  Factory class that creates boost::gregorian::date_period instances for 
  working weeks. Each week starts on a Monday and ends the following Sunday 
  (duh). 
  Implements ISO 8601 week numbering.
 */
class ZSU_CLASS week
{
  public:
    /// Constructs a 7-day date_period that starts on the first Monday before \a someday
    static boost::gregorian::date_period make(const boost::gregorian::date& someday = boost::gregorian::day_clock::local_day());
    /// Constructs a week for ISO 8601 week number \a number in \a year.
    static boost::gregorian::date_period make(unsigned number, boost::gregorian::greg_year year);
    /// Constructs an empty week
    static boost::gregorian::date_period makeEmptyWeek(void);
};
//---------------------------------------------------------------------------
}  // namespace

#endif
