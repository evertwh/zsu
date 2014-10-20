//
//  Rev:          $Id: TempFile_test.cpp,v 1.3 2005/08/08 14:13:15 evert Exp $
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

#include <string>
#include <fstream>

#include <boost/test/unit_test.hpp>
#include <zsu/TempFile.h>

using namespace boost::unit_test_framework;
using zsu::TempFile;
          
//---------------------------------------------------------------------------

#ifdef __BORLANDC__
void full_test(void)
{
  TempFile* foo( new TempFile("foo") );
  std::string content("hi there");

  // open temp file for writing and write
  std::ofstream os(foo->getName().c_str());
  BOOST_CHECK(os.good());

  os << content;
  BOOST_CHECK(os.good());

  os.close();

  // open temp file for reading and read back
  std::ifstream is(foo->getName().c_str());
  BOOST_CHECK(is.good());

  std::string buf;
  std::getline(is, buf);
  BOOST_CHECK_EQUAL(buf, content);
  is.close();

  std::string fileName(foo->getName());

  // delete TempFile
  delete foo;

  // check that the file is indeed gone
  is.open(fileName.c_str());
  BOOST_CHECK(is.fail());
}
#endif // __BORLANDC__

//---------------------------------------------------------------------------

void add_tempfile_tests(test_suite* test)
{
  #ifdef __BORLANDC__
  test->add( BOOST_TEST_CASE( &full_test ) );
  #endif // __BORLANDC__

}

//---------------------------------------------------------------------------

