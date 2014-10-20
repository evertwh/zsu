//
//  Rev:          $Id: Uniquifier.h,v 1.3 2004/03/04 07:53:30 evert Exp $
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

#ifndef UNIQUIFIER_H
#define UNIQUIFIER_H

#include <algorithm>
#include <string>

#include <boost/lexical_cast.hpp>
             
#include <zsu/config.h>

namespace zsu
{
//---------------------------------------------------------------------------
/**
   Simple string decorator. Just appends the \a sequenceNumber (if
   larger than 0) to \a org.
 */
struct ZSU_CLASS SimpleDecorator
{
  /// Does the actual decorating
  std::string operator()(const std::string org, unsigned sequenceNumber) const
  {
    return (sequenceNumber > 0) ?
        org + " " + boost::lexical_cast<std::string>(sequenceNumber)
      :
        org;
  }
};
//---------------------------------------------------------------------------
/**
   String decorator. Prepends "copy of " \a sequenceNumber times to \a org.
 */
struct ZSU_CLASS PrependingDecorator
{
  /// Does the actual decorating
  std::string operator()(const std::string org, unsigned sequenceNumber) const
  {
    std::string retVal;

    for (unsigned i = 0; i < sequenceNumber; ++i)
    {
      retVal += "copy of ";
    }

    return retVal + org;
  }
};
//---------------------------------------------------------------------------

/**
  Class to generate a unique name.

  \param Decorator Policy to generate alternative names.

  \todo I would expect Uniquifier instantiation without a template to work, as
  SimpleDecorator is the default template argument, but BCB5 will not have it.
 */
template <class Decorator = SimpleDecorator>
  struct ZSU_CLASS Uniquifier
  {
    Uniquifier(void)
    {
      decorator_ = Decorator();
    }

    /**
      Based on a proposed name, generates a unique name given a sequence of
      exisiting names.

      This method determines whether \a proposedName can be found in the
      sequence from \a first to \a last. If not, \a proposedName returned as is,
      otherwise, it is decorated using the Decorator policy.

      The default policy is to simply append a sequence number, so if 'foo' is
      in first..last, it will return 'foo 1' (unless that is in the sequence,
      too: in that case it will return 'foo 2' and so on).

      \param proposedName The suggested name.
      \param first Start of the sequence of existing names
      \param last End of the sequence of existing names
      \param startIndex Used internally for recursion

      \return A possibly decorated version of \a proposedName that is guaranteed
      not to be part of the sequence \a first .. \a last.

      \see  SimpleDecorator and PrependingDecorator

      \todo make this work for iterators that do not deref to a string. E.g. by
      having some functor argument to 'cast' to string and then use find_if.
      Maybe simply using explicit cast to std::string will help already. I would
      really like this to work with boost::filesystem::directory_iterator or with
      sequences of named objects.
     */
    template <class InputIterator>
      std::string operator()(const std::string proposedName,
                             InputIterator first,
                             InputIterator last,
                             unsigned startIndex = 0) const
      {
        std::string decoratedName(decorator_(proposedName, startIndex));

        //
        // Check if we're proposing a duplicate name or not
        //
        if (std::find(first, last, decoratedName) == last)
        {
          //
          // decoratedName is unique: return that
          //
          return decoratedName;
        }
        else
        {
          //
          // decoratedName is duplicate: recurse to next proposal
          //
          return this->operator()(proposedName, first, last, ++startIndex);
        }
      }

  private:
    Decorator decorator_;
  };

//---------------------------------------------------------------------------

};
#endif
