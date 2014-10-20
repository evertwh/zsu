//
//  Rev:          $Id: Properties_test.cpp,v 1.4 2005/08/08 14:13:15 evert Exp $
//
//  Author:       Evert Haasdijk
//  Contact:      evert@zukkespijkers.nl
//
//  Test cases for zsu::Properties
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
                    
#include <cstdlib>
#include <string>
#include <fstream>

#include <boost/test/unit_test.hpp>
#include <zsu/Properties.h>

using namespace boost::unit_test_framework;
using zsu::Properties;
      
//---------------------------------------------------------------------------
BOOST_TEST_DONT_PRINT_LOG_VALUE( Properties );

//---------------------------------------------------------------------------

void setProperty_test(void)
{
  Properties prop;

  prop.setProperty("test", "hello there");

  BOOST_CHECK_EQUAL( prop.getProperty("test"), std::string("hello there") );
  BOOST_CHECK( prop.hasProperty("test") );
  BOOST_CHECK( !(prop.hasProperty("not_a_property")) );
}

//---------------------------------------------------------------------------

void properties_IO_test(void)
{
  const std::string tmpFileName("properties_IO_test.tmp");

  Properties org;
  org.setProperty("foo", "bar");
  org.setProperty("name", "pipo");

  std::ofstream out(tmpFileName.c_str());
  org.store(out);
  out.close();

  Properties copy;
  std::ifstream in(tmpFileName.c_str());
  copy.load(in);

  BOOST_CHECK_EQUAL(org, copy);
}

//---------------------------------------------------------------------------

void properties_load_test(void)
{
  Properties p;
  const std::string tst("name=\"pipo\" foo=bar cmd=\"foo=bar\" tab=\"\\t\"");

  p.load(tst);

  BOOST_CHECK( p.hasProperty("name") );
  BOOST_CHECK( p.hasProperty("cmd") );
  BOOST_CHECK( p.hasProperty("foo") );
  BOOST_CHECK( p.hasProperty("tab") );

  BOOST_CHECK_EQUAL( p.getProperty("name"), std::string("pipo") );
  BOOST_CHECK_EQUAL( p.getProperty("cmd"), std::string("foo=bar") );
  BOOST_CHECK_EQUAL( p.getProperty("foo"), std::string("bar") );
  BOOST_CHECK_EQUAL( p.getProperty("tab"), std::string("\\t") );

  const std::string env("aap=noot");
  std::putenv(env.c_str());
  p.addEnvironment("aap");
  p.addEnvironment("noot");

  BOOST_CHECK( p.hasProperty("aap") );
  BOOST_CHECK_EQUAL( p.getProperty("aap"), std::string("noot") );
  BOOST_CHECK( !(p.hasProperty("noot")) );

  const std::string tmpFileName("properties_IO_test.tmp");
  std::ofstream out(tmpFileName.c_str());
  p.store(out);
  out.close();

  Properties copy;
  std::ifstream in(tmpFileName.c_str());
  copy.load(in);

  BOOST_CHECK_EQUAL(p, copy);
}

//---------------------------------------------------------------------------
void properties_load_file_test(void)
{
  const std::string tmpFileName("properties_IO_test.tmp");

  std::ofstream out(tmpFileName.c_str());
  out << "name=pipo\n"
      << "foo=bar\n"
      << "cmd=foo=bar\n"
      << "tab=\\t\n";
  out.close();

  std::ifstream in(tmpFileName.c_str());
  Properties p;
  p.load(in);

  BOOST_CHECK( p.hasProperty("name") );
  BOOST_CHECK( p.hasProperty("cmd") );
  BOOST_CHECK( p.hasProperty("foo") );
  BOOST_CHECK( p.hasProperty("tab") );

  BOOST_CHECK_EQUAL( p.getProperty("name"), std::string("pipo") );
  BOOST_CHECK_EQUAL( p.getProperty("cmd"), std::string("foo=bar") );
  BOOST_CHECK_EQUAL( p.getProperty("foo"), std::string("bar") );
  BOOST_CHECK_EQUAL( p.getProperty("tab"), std::string("\t") );
}

//---------------------------------------------------------------------------

void add_properties_tests(test_suite* test)
{
  test->add( BOOST_TEST_CASE( &setProperty_test ) );
  test->add( BOOST_TEST_CASE( &properties_IO_test ) );
  test->add( BOOST_TEST_CASE( &properties_load_test ) );
  test->add( BOOST_TEST_CASE( &properties_load_file_test ) );
}

//---------------------------------------------------------------------------


