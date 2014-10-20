//
//  Rev:          $Id: Week_test.cpp,v 1.5 2005/08/08 14:13:15 evert Exp $
//
//  Author:       Evert Haasdijk
//  Contact:      evert@zukkespijkers.nl
//
//  Test cases for zsu::Uniquifier
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

#include <boost/test/unit_test.hpp>
#include <zsu/Week.h>

#include <ostream>

#include "boost/date_time/gregorian/gregorian.hpp"

using namespace boost::unit_test_framework;
using zsu::week;
using namespace boost::gregorian;
//---------------------------------------------------------------------------

void week_construction_test(void)
{
  date_period d1(week::make(date(2004,Mar,16)));    // Tuesday
  date_period d2(week::make(date(2004,Mar,21)));    // Sunday
  date_period d3(week::make(date(2004,Mar,15)));    // Monday    
  date_period d4(week::make(12, 2004));

  BOOST_CHECK_EQUAL(d1, d2);
  BOOST_CHECK_EQUAL(d3, d2);
  BOOST_CHECK_EQUAL(d1, d3);
  BOOST_CHECK_EQUAL(d1, d4);

  std::clog << d4 << std::endl;

  date_period e1(week::make(1, 2005));
  date_period e2(week::make(date(2005, Jan, 1)));
  date_period e3(week::make(date(2005, Jan, 4)));
  date_period e4(week::make(date(2004, Dec, 31)));

  BOOST_CHECK( !( e1 == e2) );
  BOOST_CHECK_EQUAL(e1, e3);
  BOOST_CHECK_EQUAL(e2, e4);
}

//---------------------------------------------------------------------------

void add_week_tests(test_suite* test)
{
  test->add( BOOST_TEST_CASE( &week_construction_test ) );
}

//---------------------------------------------------------------------------

