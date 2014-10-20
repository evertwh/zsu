//
//  Rev:          $Id: test_Diff.cpp,v 1.1 2005/08/08 14:13:15 evert Exp $
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

#include <algorithm>
#include <ctype>
#include <functional>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>

#include <boost/test/unit_test.hpp>
#include <boost/iterator/filter_iterator.hpp>

#include <zsu/diff.h>

using namespace boost::unit_test_framework;
using namespace zsu;
using std::string;
using std::istringstream;

//---------------------------------------------------------------------------
namespace test_Diff
{
//---------------------------------------------------------------------------
struct is_not_space
{
  bool operator()(char x) { return !(std::isspace(x)); }
};
//---------------------------------------------------------------------------
template <class charT>
struct equal_to_ignore_caps
{
  bool operator()(charT x, charT y) { return std::equal_to<charT>()( std::toupper(x), std::toupper(y) ); }
};
//---------------------------------------------------------------------------
void diff_iterators_test(void)
{
  string content1("hello world");
  string content2("hello world");
  string content3("helloworld");
  string content4("hello\t world");
  string content5("hello\n world");
  string content6("hi there");
  string content7("");
  string content8("");
  string content9("hello world!");    
  string content10("hello world  ");  
  string content11("heLLo world");

  typedef string::const_iterator iterator;

  // vanilla diff
  std::equal_to<char> vanillaComparison;
  BOOST_CHECK( diff(content1.begin(), content1.end(), content1.begin(), content1.end(), vanillaComparison) );
  BOOST_CHECK( diff(content1.begin(), content1.end(), content2.begin(), content2.end(), vanillaComparison) );
  BOOST_CHECK( !diff(content1.begin(), content1.end(), content3.begin(), content3.end(), vanillaComparison) );
  BOOST_CHECK( !diff(content1.begin(), content1.end(), content4.begin(), content4.end(), vanillaComparison) );
  BOOST_CHECK( !diff(content1.begin(), content1.end(), content6.begin(), content6.end(), vanillaComparison) );
  BOOST_CHECK( !diff(content1.begin(), content1.end(), content7.begin(), content7.end(), vanillaComparison) );
  BOOST_CHECK( diff(content7.begin(), content7.end(), content8.begin(), content8.end(), vanillaComparison) );
  BOOST_CHECK( !diff(content1.begin(), content1.end(), content9.begin(), content9.end(), vanillaComparison) );
  BOOST_CHECK( !diff(content1.begin(), content1.end(), content10.begin(), content10.end(), vanillaComparison) );
  BOOST_CHECK( !diff(content1.begin(), content1.end(), content11.begin(), content11.end(), vanillaComparison) );

  // ignore caps diff
  equal_to_ignore_caps<char> noCapsComparison;
  BOOST_CHECK( diff(content1.begin(), content1.end(), content1.begin(), content1.end(), noCapsComparison) );
  BOOST_CHECK( diff(content1.begin(), content1.end(), content2.begin(), content2.end(), noCapsComparison) );
  BOOST_CHECK( !diff(content1.begin(), content1.end(), content3.begin(), content3.end(), noCapsComparison) );
  BOOST_CHECK( !diff(content1.begin(), content1.end(), content4.begin(), content4.end(), noCapsComparison) );
  BOOST_CHECK( !diff(content1.begin(), content1.end(), content6.begin(), content6.end(), noCapsComparison) );
  BOOST_CHECK( !diff(content1.begin(), content1.end(), content7.begin(), content7.end(), noCapsComparison) );
  BOOST_CHECK( diff(content7.begin(), content7.end(), content8.begin(), content8.end(), noCapsComparison) );
  BOOST_CHECK( !diff(content1.begin(), content1.end(), content9.begin(), content9.end(), noCapsComparison) );
  BOOST_CHECK( !diff(content1.begin(), content1.end(), content10.begin(), content10.end(), noCapsComparison) );  
  BOOST_CHECK( diff(content1.begin(), content1.end(), content11.begin(), content11.end(), noCapsComparison) );

  // using filter_iterator to skip whitespace
  typedef boost::filter_iterator<is_not_space, iterator> skip_whitespace;
  BOOST_CHECK( diff(skip_whitespace(content1.begin()), skip_whitespace(content1.end()), skip_whitespace(content1.begin()), skip_whitespace(content1.end()), vanillaComparison) );
  BOOST_CHECK( diff(skip_whitespace(content1.begin()), skip_whitespace(content1.end()), skip_whitespace(content2.begin()), skip_whitespace(content2.end()), vanillaComparison) );
  BOOST_CHECK( diff(skip_whitespace(content1.begin()), skip_whitespace(content1.end()), skip_whitespace(content3.begin()), skip_whitespace(content3.end()), vanillaComparison) );
  BOOST_CHECK( diff(skip_whitespace(content1.begin()), skip_whitespace(content1.end()), skip_whitespace(content4.begin()), skip_whitespace(content4.end()), vanillaComparison) );
  BOOST_CHECK( !diff(skip_whitespace(content1.begin()), skip_whitespace(content1.end()), skip_whitespace(content6.begin()), skip_whitespace(content6.end()), vanillaComparison) );
  BOOST_CHECK( !diff(skip_whitespace(content1.begin()), skip_whitespace(content1.end()), skip_whitespace(content7.begin()), skip_whitespace(content7.end()), vanillaComparison) );
  BOOST_CHECK( diff(skip_whitespace(content7.begin()), skip_whitespace(content7.end()), skip_whitespace(content8.begin()), skip_whitespace(content8.end()), vanillaComparison) );
  BOOST_CHECK( !diff(skip_whitespace(content1.begin()), skip_whitespace(content1.end()), skip_whitespace(content9.begin()), skip_whitespace(content9.end()), vanillaComparison) );
  BOOST_CHECK( diff(skip_whitespace(content1.begin()), skip_whitespace(content1.end()), skip_whitespace(content10.begin()), skip_whitespace(content10.end()), vanillaComparison) );
}

//---------------------------------------------------------------------------     
} // end namespace test_Diff
//---------------------------------------------------------------------------

void add_Diff_tests(test_suite* test)
{
  test->add( BOOST_TEST_CASE( &test_Diff::diff_iterators_test ) );
}

//---------------------------------------------------------------------------

             
