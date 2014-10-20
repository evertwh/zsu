//
//  Rev:          $Id: diff.h,v 1.1 2005/08/08 14:13:15 evert Exp $
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

#ifndef DiffH
#define DiffH        

namespace zsu
{

//---------------------------------------------------------------------------
/**
  Returns \c true if applying \c BinaryPredicate to each pair <lhs, rhs> in the
  range \c [lhsFirst,lhsLast) and \c [rhsFirst,rhsLast).
*/
template <class InputIterator, class BinaryPredicate>
bool diff(InputIterator lhsFirst, InputIterator lhsLast, InputIterator rhsFirst, InputIterator rhsLast, BinaryPredicate predicate)
{
  for (; lhsFirst != lhsLast && rhsFirst != rhsLast; ++lhsFirst, ++rhsFirst)
    if (!predicate(*lhsFirst, *rhsFirst))
      return false;
    // else
  return lhsFirst == lhsLast && rhsFirst == rhsLast;
}
//---------------------------------------------------------------------------

}
#endif
