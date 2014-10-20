//
//  Rev:          $Id: test_Log.cpp,v 1.3 2004/03/04 07:53:30 evert Exp $
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
#include <zsu/CompareFiles.h>

//---------------------------------------------------------------------------
        /*
static bool fc(string f1, string f2)
{
  ifstream s1(f1.c_str());
  ifstream s2(f2.c_str());

  CharT c1 = getter.getNextSignificantChar(s1);
  CharT c2 = getter.getNextSignificantChar(s2);

  while (s1 && s2)
    if (s1.get() != s2.get())
      return false;
    // else

  return (!s1) && (!s2);
}    */
