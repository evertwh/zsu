//
//  Rev:          $Id: Uniquifier_test.cpp,v 1.2 2004/03/04 07:53:30 evert Exp $
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


#include <algorithm>
#include <string>
#include <vector>

#include <boost/test/unit_test.hpp>
#include <zsu/Uniquifier.h>

using namespace boost::unit_test_framework;
using zsu::Uniquifier;
using zsu::SimpleDecorator;
using zsu::PrependingDecorator;

//---------------------------------------------------------------------------

void simpleDecorator_test(void)
{
  SimpleDecorator decorator;

  const std::string undecorated("foo");

  BOOST_CHECK( decorator(undecorated, 0) == undecorated );
  BOOST_CHECK( decorator(undecorated, 2) != undecorated);
  BOOST_CHECK( decorator(undecorated, 2) == undecorated + " 2");
}

//---------------------------------------------------------------------------

void prependingDecorator_test(void)
{
  PrependingDecorator decorator;

  const std::string undecorated("foo");

  BOOST_CHECK( decorator(undecorated, 0) == undecorated );
  BOOST_CHECK( decorator(undecorated, 2) != undecorated);
  BOOST_CHECK( decorator(undecorated, 1) == std::string("copy of ") + undecorated);
}

//---------------------------------------------------------------------------

void uniquifier_test(void)
{
  std::vector<std::string> names;

  names.push_back("foo");
  names.push_back("foo 1");
  names.push_back("bar");
  names.push_back("copy of bar");
  names.push_back("zukke spijkers");
  names.push_back("pipo");

  Uniquifier<SimpleDecorator> u1;
  BOOST_CHECK( u1("new", names.begin(), names.end()) == "new" );
  BOOST_CHECK( u1("foo", names.begin(), names.end()) == "foo 2" );
  BOOST_CHECK( std::find(names.begin(), names.end(), u1("foo", names.begin(), names.end())) == names.end() );
  
  Uniquifier<PrependingDecorator> u2;
  BOOST_CHECK( std::find(names.begin(), names.end(), u1("foo", names.begin(), names.end())) == names.end() );
}

//---------------------------------------------------------------------------

void add_uniquify_tests(test_suite* test)
{
  test->add( BOOST_TEST_CASE( &simpleDecorator_test ) );
  test->add( BOOST_TEST_CASE( &prependingDecorator_test ) );
  test->add( BOOST_TEST_CASE( &uniquifier_test ) );
}

//---------------------------------------------------------------------------

