//
//  Rev:          $Id: test_IPAddress.cpp,v 1.3 2005/08/08 14:13:15 evert Exp $
//
//  Author:       Evert Haasdijk
//  Contact:      evert@zukkespijkers.nl
//
//  Test cases for zsu::IPAddress
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

#include <string>
#include <fstream>

#include <boost/test/unit_test.hpp>
#include <zsu/IPAddress.h>

using namespace boost::unit_test_framework;
using boost::test_toolbox::output_test_stream;
using zsu::IPAddress;
using std::string;

//---------------------------------------------------------------------------
namespace test_IPAddress
{
//---------------------------------------------------------------------------

void assign_test(void)
{
  string h("www.zukkespijkers.nl");

  IPAddress home(h);
  BOOST_CHECK_EQUAL(home.getFQDN(), h);

  home.setSubDomain(string("sub"));
  BOOST_CHECK_EQUAL(home.getFQDN(), string("www.sub.zukkespijkers.nl"));

  const IPAddress foo = home;
  BOOST_CHECK_EQUAL(foo.getFQDN(), string("www.sub.zukkespijkers.nl"));
  BOOST_CHECK_EQUAL(foo.getHost(), string("www"));
  BOOST_CHECK_EQUAL(foo.getSubDomain(), string("sub"));
  BOOST_CHECK_EQUAL(foo.getDomain(), string("zukkespijkers"));
  BOOST_CHECK_EQUAL(foo.getRoot(), string("nl"));

  home = string("foo.bar.org");
  BOOST_CHECK_EQUAL(home.getFQDN(), string("foo.bar.org"));

  home.erase();
  home.setRoot(string("nl"));
  home.setDomain(string("zukkespijkers"));
  home.setHost(string("www"));
  BOOST_CHECK_EQUAL(home.getFQDN(), h);

  home = string("foo.com");
  BOOST_CHECK_EQUAL(home.getHost(), string(""));
  BOOST_CHECK_EQUAL(home.getSubDomain(), string(""));
  BOOST_CHECK_EQUAL(home.getDomain(), string("foo"));
  BOOST_CHECK_EQUAL(home.getRoot(), string("com"));

  home.setSubDomain(string("sub"));
  BOOST_CHECK_EQUAL(home.getHost(), string(""));
  BOOST_CHECK_EQUAL(home.getSubDomain(), string("sub"));

  home = string("perspicutron");
  BOOST_CHECK_EQUAL(home.getHost(), string("perspicutron"));
}
//---------------------------------------------------------------------------

void os_test(void)
{
  string h("www.zukkespijkers.nl");
  IPAddress home(h);

  output_test_stream output;
  output << home;
  BOOST_CHECK( output.is_equal( h ) );
}
//---------------------------------------------------------------------------
void compare_test(void)
{
  IPAddress zz(string("zz.foo.com"));   // IPAddresses are listed in sort order
  IPAddress yy(string("yy.bar.org"));
  IPAddress foo(string("foo.org"));
  IPAddress aa(string("aa.foo.org"));
  IPAddress bb(string("bb.foo.org"));
  IPAddress aaaa(string("aa.aa.foo.org"));

  BOOST_CHECK(!(aa < zz));

  BOOST_CHECK_PREDICATE( std::less<IPAddress>(), 2, (zz, aa) );
  BOOST_CHECK_PREDICATE( std::less<IPAddress>(), 2, (yy, aa) );
  BOOST_CHECK_PREDICATE( std::less<IPAddress>(), 2, (aa, bb) );
  BOOST_CHECK_PREDICATE( std::less<IPAddress>(), 2, (zz, bb) );
  BOOST_CHECK_PREDICATE( std::less<IPAddress>(), 2, (aa, aaaa) );
  BOOST_CHECK_PREDICATE( std::less<IPAddress>(), 2, (bb, aaaa) );
  BOOST_CHECK_PREDICATE( std::less<IPAddress>(), 2, (foo, aa) );
}

//---------------------------------------------------------------------------
} // namespace
//---------------------------------------------------------------------------

void add_IPAddress_tests(test_suite* test)
{
  test->add( BOOST_TEST_CASE( &test_IPAddress::assign_test ) );
  test->add( BOOST_TEST_CASE( &test_IPAddress::os_test ) );
  test->add( BOOST_TEST_CASE( &test_IPAddress::compare_test ) );
}

//---------------------------------------------------------------------------

 