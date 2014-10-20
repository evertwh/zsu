//
//  Rev:          $Id: test_strip.cpp,v 1.2 2005/08/08 14:13:15 evert Exp $
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


#include <algorithm>
#include <functional>
#include <string>

#include <zsu/strip.h>

#include <boost/test/unit_test.hpp>

using namespace boost::unit_test_framework;
     
//---------------------------------------------------------------------------
void test_strip(void)
{
  std::binder1st< std::equal_to<char> > pred1( std::bind1st(std::equal_to<char>(), '#') );

  BOOST_CHECK_EQUAL(zsu::strip_left_if(std::string("##foo#bar##"), pred1) , "foo#bar##");
  BOOST_CHECK_EQUAL(zsu::strip_left_if(std::string(" ##foo#bar##"), pred1) , " ##foo#bar##");
  BOOST_CHECK_EQUAL(zsu::strip_left_if(std::string("foo"), pred1) , "foo");
  BOOST_CHECK_EQUAL(zsu::strip_left_if(std::string(), pred1) , "");

  BOOST_CHECK_EQUAL(zsu::strip_right_if(std::string("##foo#bar##"), pred1) , "##foo#bar");
  BOOST_CHECK_EQUAL(zsu::strip_right_if(std::string("##foo#bar## "), pred1) , "##foo#bar## ");
  BOOST_CHECK_EQUAL(zsu::strip_right_if(std::string("foo"), pred1) , "foo");
  BOOST_CHECK_EQUAL(zsu::strip_right_if(std::string(), pred1) , "");
  
  BOOST_CHECK_EQUAL(zsu::strip_if(std::string("##foo#bar##"), pred1) , "foo#bar");
  BOOST_CHECK_EQUAL(zsu::strip_if(std::string("##foo#bar## "), pred1) , "foo#bar## ");
  BOOST_CHECK_EQUAL(zsu::strip_if(std::string("foo"), pred1) , "foo");
  BOOST_CHECK_EQUAL(zsu::strip_if(std::string(), pred1) , "");
}
//---------------------------------------------------------------------------
void add_strip_tests(test_suite* test)
{
  test->add( BOOST_TEST_CASE( &test_strip ) );
}

//---------------------------------------------------------------------------

