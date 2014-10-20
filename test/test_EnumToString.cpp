//
//  Rev:          $Id: test_EnumToString.cpp,v 1.2 2005/08/08 14:13:15 evert Exp $
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

#include <boost/test/unit_test.hpp>
#include <zsu/UIMapper.h>

using namespace boost::unit_test_framework;

//---------------------------------------------------------------------------
namespace UIMApper_test
{           
//---------------------------------------------------------------------------
enum Fruit {apple = 0, orange, banana};
Fruit fruits[] = {apple, orange, banana};
std::string labels[] = {"pomme", "orange", "banane"};

typedef zsu::UIMapper<Fruit> FruitMapper;
template<>
FruitMapper FruitMapper::instance_(3, fruits, labels);
//---------------------------------------------------------------------------

void FruitMapper_test(void)
{
  BOOST_CHECK_EQUAL(FruitMapper::get().get("pomme"), apple);
  BOOST_CHECK_EQUAL(FruitMapper::get().get(banana), "banane");
}
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------

void add_EnumToString_tests(test_suite* test)
{
  test->add( BOOST_TEST_CASE( &UIMApper_test::FruitMapper_test ) );
}
//---------------------------------------------------------------------------






