//
//  Rev:          $Id: test_StringUtils.cpp,v 1.7 2005/08/08 14:13:15 evert Exp $
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

#include <iostream>
#include <sstream>
#include <exception>

#include <zsu/StringUtils.h>
#include <boost/test/unit_test.hpp>

using namespace boost::unit_test_framework;
using namespace std;

//---------------------------------------------------------------------------
void testStringUtils(void)
{
  string one = "tab:\t newline:\n carriage return:\r quote:\" backslash: \\ ";
  string escaped = zsu::escape(one);
  BOOST_CHECK_EQUAL(escaped, "tab:\\t newline:\\n carriage return:\\r quote:\\\" backslash: \\\\ ");
  BOOST_CHECK_EQUAL(one, zsu::unEscape(escaped));

  string quoted = zsu::quote(escaped);
  BOOST_CHECK_EQUAL(quoted, "\"tab:\\t newline:\\n carriage return:\\r quote:\\\" backslash: \\\\ \"");
  BOOST_CHECK_EQUAL(escaped, zsu::unQuote(quoted));

  istringstream qStr(quoted);
  string yas;
  zsu::readQuoted(yas, qStr);
  BOOST_CHECK_EQUAL(escaped, yas);

  quoted += "  \t\n";
  istringstream foo(quoted);
  zsu::readString(yas, foo);
  BOOST_CHECK_EQUAL(one, yas);   
}  
//---------------------------------------------------------------------------

void testStripFunction(void)
{
  string initial = string("Boog, F. van der");
  string expected = string("Boog, F. van der");
  string got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("    Boog, F. van der");
  expected = string("Boog, F. van der");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("Boog, F. van der    ");
  expected = string("Boog, F. van der");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("   Boog, F. van der    ");
  expected = string("Boog, F. van der");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  /*
  initial = string("\"Boog, F. van der\"");
  expected = string("Boog, F. van der");
  got = zsu::strip(initial, "\"");
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("\"    Boog, F. van der\"");
  expected = string("Boog, F. van der");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("\"Boog, F. van der    \"");
  expected = string("Boog, F. van der");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("\"   Boog, F. van der    \"");
  expected = string("Boog, F. van der");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("   \"    Boog, F. van der\"");
  expected = string("Boog, F. van der");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("\"Boog, F. van der    \"   ");
  expected = string("Boog, F. van der");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("  \"   Boog, F. van der    \"    ");
  expected = string("Boog, F. van der");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  // some special cases!
  initial = string("");
  expected = string("");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("  ");
  expected = string("");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("\"\"");
  expected = string("");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("\" \"");
  expected = string("");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("\"");
  expected = string("\"");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("\"\"\"");
  expected = string("\"");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("a");
  expected = string("a");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string(" a");
  expected = string("a");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("a ");
  expected = string("a");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string(" a ");
  expected = string("a");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("\"a\"");
  expected = string("a");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string(" \"a\"");
  expected = string("a");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("\"a\" ");
  expected = string("a");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string(" \"a\" ");
  expected = string("a");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("\" a\"");
  expected = string("a");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("\"a \"");
  expected = string("a");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("\" a \"");
  expected = string("a");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string(" \" a \" ");
  expected = string("a");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  // tests when the quote character is <'>
  initial = string("'Boog, F. van der'");
  expected = string("Boog, F. van der");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("'    Boog, F. van der'");
  expected = string("Boog, F. van der");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("'Boog, F. van der    '");
  expected = string("Boog, F. van der");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("'   Boog, F. van der    '");
  expected = string("Boog, F. van der");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("   '    Boog, F. van der'");
  expected = string("Boog, F. van der");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("'Boog, F. van der    '   ");
  expected = string("Boog, F. van der");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("  '   Boog, F. van der    '    ");
  expected = string("Boog, F. van der");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("'a'");
  expected = string("a");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string(" 'a'");
  expected = string("a");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("'a' ");
  expected = string("a");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string(" 'a' ");
  expected = string("a");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("' a'");
  expected = string("a");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("'a '");
  expected = string("a");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("' a '");
  expected = string("a");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string(" ' a ' ");
  expected = string("a");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("''");
  expected = string("");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("' '");
  expected = string("");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("'");
  expected = string("'");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);

  initial = string("'''");
  expected = string("'");
  got = zsu::strip(initial);
  BOOST_CHECK_EQUAL(expected, got);
  */
}

//---------------------------------------------------------------------------

void testKeyValue(void)
{
  char two[] = "key=123 key={1 2 3}";
  istringstream test(two);

  string key = "key";
  string entry;
  vector<string> entries;

  BOOST_CHECK(zsu::readEntry(key, entry, test));
  BOOST_CHECK_EQUAL(entry, "123");

  BOOST_CHECK(zsu::readEntry(key, entries, test));
  BOOST_CHECK_EQUAL(entries[0], "1");
  BOOST_CHECK_EQUAL(entries[1], "2");
  BOOST_CHECK_EQUAL(entries[2], "3");
}
//---------------------------------------------------------------------------

void testExceptionLogging ()
{
  std::invalid_argument e("testing std::invalid_argument");

 /* try
  {
    throw e;
  }
  catch (const std::exception& e)
  {     */
    ostringstream os;
    os << e;
    BOOST_CHECK(os.good());
 /* } */
}
                                                                              
//---------------------------------------------------------------------------
void testMaskedSubStr()
{
  BOOST_CHECK_EQUAL(zsu::maskedSubstr("20041201", "YYYYMMDD", 'Y'), "2004");
  BOOST_CHECK_EQUAL(zsu::maskedSubstr("20  041201", "YYXXYYMMDD", 'Y'), "2004");
  BOOST_CHECK_EQUAL(zsu::maskedSubstr("20  041201", "YYXXYYMMDD", 'Z'), "");
  BOOST_CHECK_EQUAL(zsu::maskedSubstr("2004", "YYYY", 'Y'), "2004");
}
//---------------------------------------------------------------------------
void test_removeMatchingQuotes()
{
  BOOST_CHECK_EQUAL(zsu::removeMatchingQuotes("'foo'"), "foo");
  BOOST_CHECK_EQUAL(zsu::removeMatchingQuotes(" 'foo' bar"), " foo bar");
  BOOST_CHECK_EQUAL(zsu::removeMatchingQuotes("'\"foo\"'"), "\"foo\"");
  BOOST_CHECK_EQUAL(zsu::removeMatchingQuotes("\"'foo'\""), "'foo'");
  BOOST_CHECK_EQUAL(zsu::removeMatchingQuotes("'foo\""), "'foo\"");
  BOOST_CHECK_EQUAL(zsu::removeMatchingQuotes("'foo"), "'foo");
  BOOST_CHECK_EQUAL(zsu::removeMatchingQuotes("foo"), "foo");
  BOOST_CHECK_EQUAL(zsu::removeMatchingQuotes(""), "");
  BOOST_CHECK_EQUAL(zsu::removeMatchingQuotes("''"), "");
}
//---------------------------------------------------------------------------
void test_strip(void)
{
  BOOST_CHECK_EQUAL(zsu::stripLeft("##foo#bar##", '#'), "foo#bar##");
  BOOST_CHECK_EQUAL(zsu::stripLeft(" ##foo#bar##", '#'), " ##foo#bar##");
  BOOST_CHECK_EQUAL(zsu::stripLeft("foo", ' '), "foo");
  BOOST_CHECK_EQUAL(zsu::stripLeft("", 'a'), "");
  
  BOOST_CHECK_EQUAL(zsu::stripRight("##foo#bar##", '#'), "##foo#bar");
  BOOST_CHECK_EQUAL(zsu::stripRight("##foo#bar## ", '#'), "##foo#bar## ");
  BOOST_CHECK_EQUAL(zsu::stripRight("foo", ' '), "foo");
  BOOST_CHECK_EQUAL(zsu::stripRight("", 'a'), "");
  
  BOOST_CHECK_EQUAL(zsu::strip("##foo#bar##", '#'), "foo#bar");
  BOOST_CHECK_EQUAL(zsu::strip(" ##foo#bar##", '#'), " ##foo#bar");
  BOOST_CHECK_EQUAL(zsu::strip("foo", ' '), "foo");
  BOOST_CHECK_EQUAL(zsu::strip("", 'a'), "");

  string retval;
  retval = zsu::stripLeft("foo ");
  BOOST_CHECK_EQUAL(zsu::stripLeft("foo "), "foo ");
  BOOST_CHECK_EQUAL(zsu::stripLeft(" foo"), "foo");
  BOOST_CHECK_EQUAL(zsu::stripLeft(""), "");
  BOOST_CHECK_EQUAL(zsu::stripLeft(" "), "");
  BOOST_CHECK_EQUAL(zsu::stripLeft("  f f "), "f f ");
  
  BOOST_CHECK_EQUAL(zsu::stripRight("foo "), "foo");
  BOOST_CHECK_EQUAL(zsu::stripRight(""), "");
  BOOST_CHECK_EQUAL(zsu::stripRight(" "), "");
  BOOST_CHECK_EQUAL(zsu::stripRight("  f f "), "  f f");

  BOOST_CHECK_EQUAL(zsu::strip("foo "), "foo");
  BOOST_CHECK_EQUAL(zsu::strip(""), "");
  BOOST_CHECK_EQUAL(zsu::strip(" "), "");
  BOOST_CHECK_EQUAL(zsu::strip("  f f "), "f f");
}
//---------------------------------------------------------------------------
void add_StringUtils_tests(test_suite* test)
{
  test->add( BOOST_TEST_CASE( &testStringUtils ) );
  test->add( BOOST_TEST_CASE( &testStripFunction ) );
  test->add( BOOST_TEST_CASE( &testKeyValue ) );
  test->add( BOOST_TEST_CASE( &testExceptionLogging ) );
  test->add( BOOST_TEST_CASE( &testMaskedSubStr ) );
  test->add( BOOST_TEST_CASE( &test_removeMatchingQuotes ) );
  test->add( BOOST_TEST_CASE( &test_strip ) );
}

//---------------------------------------------------------------------------

