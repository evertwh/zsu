//
//  Rev:          $Id: test_Log.cpp,v 1.4 2005/08/08 14:13:15 evert Exp $
//
//  Author:       Evert Haasdijk
//  Contact:      evert@zukkespijkers.nl
//
//  Test cases for zsu::TestFile
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

#include <iostream>
#include <fstream>
#include <string>

#include <boost/test/unit_test.hpp>
#include <zsu/Log.h>

using namespace boost::unit_test_framework;
using zsu::Log;

//---------------------------------------------------------------------------
namespace test_Log
{
//---------------------------------------------------------------------------

void cout_test(void)
{
  Log* log( new Log("foo.log") );

  std::cout << "test" << std::endl;

  delete log;

  std::ifstream is("foo.log");     
  BOOST_CHECK(is.good());
  
  std::string buf;
  std::getline(is, buf);
  BOOST_CHECK_EQUAL(buf, "test");
}

//---------------------------------------------------------------------------

void cerr_clog_append_test(void)
{
  Log* log( new Log("foo.log") );
  std::cerr << "cerr" << std::flush;
  delete log;

  log = new Log("foo.log", true);
  std::clog << "clog" << std::flush;
  delete log;

  std::ifstream is("foo.log");
  BOOST_CHECK(is.good());
  
  std::string buf;
  std::getline(is, buf);
  BOOST_CHECK_EQUAL(buf, "cerrclog");
}

//---------------------------------------------------------------------------
} // end namespace test_Log
//---------------------------------------------------------------------------


void add_log_tests(test_suite* test)
{
  test->add( BOOST_TEST_CASE( &test_Log::cout_test ) );
  test->add( BOOST_TEST_CASE( &test_Log::cerr_clog_append_test ) );
}

//---------------------------------------------------------------------------

