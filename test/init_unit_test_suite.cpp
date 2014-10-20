//
//  Rev:          $Id: init_unit_test_suite.cpp,v 1.8 2005/08/08 14:13:15 evert Exp $
//
//  Author:       Evert Haasdijk
//  Contact:      evert@zukkespijkers.nl
//
//  Defines the test framework entry point init_unit_test_suite. This is where
//  the various sub-suites that test ZSU are brought together.
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

#include <fstream>

#include <boost/test/unit_test.hpp>

using namespace boost::unit_test_framework;

//---------------------------------------------------------------------------

//
// forward definition of functions to add sub-test_suites
//
extern void add_properties_tests(test_suite* test);
extern void add_uniquify_tests(test_suite* test);    
extern void add_tempfile_tests(test_suite* test);
extern void add_log_tests(test_suite* test);
extern void add_IPAddress_tests(test_suite* test);
extern void add_week_tests(test_suite* test);       
extern void add_EnumToString_tests(test_suite* test);
extern void add_StringUtils_tests(test_suite* test);
extern void add_strip_tests(test_suite* test);
extern void add_func_tests(test_suite* test);
extern void add_Diff_tests(test_suite* test);

//---------------------------------------------------------------------------

std::ofstream test_ZSU_log("testZSU.log");

//
// Construct the test_suite
//
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
  unit_test_log::instance().set_log_stream(test_ZSU_log);

  test_suite* test= BOOST_TEST_SUITE( "ZSU test" );

  add_properties_tests(test);
  add_uniquify_tests(test);   
  add_tempfile_tests(test);     
  add_log_tests(test);
  add_IPAddress_tests(test);
  add_EnumToString_tests(test);
  add_week_tests(test);
  add_strip_tests(test);
  add_StringUtils_tests(test);
  add_func_tests(test);
  add_Diff_tests(test);
  
  return test;
}

//---------------------------------------------------------------------------

 