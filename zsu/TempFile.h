//
//  Rev:          $Id: TempFile.h,v 1.3 2004/03/04 07:53:30 evert Exp $
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

#ifndef TEMPFILE_H
#define TEMPFILE_H

#include <string>

#include <zsu/config.h>

#ifndef __BORLANDC__
#  error "Class zsu::TempFile currently only works with Borland compilers "
#endif
 
//---------------------------------------------------------------------------
namespace zsu
{

//---------------------------------------------------------------------------
/**
  Class to create and automatically destroy a temporary file.

  \note Borland specific!

  \todo make portable and use boost::FileSystem
 */
class ZSU_CLASS TempFile
{
	public:
    /** default constructor.
      Does not create a file; call createFile() before actually using a TempFile
      created with this constructor.
    */
		TempFile(void);

    /** constructor.
      Create a temporary file with unique filename. The file will be deleted
      by ~TempFile.

      @param prefix reference to the string used as prefix for the temp filename
    */
		TempFile(const std::string prefix);

    /** destructor.
      Removes the temporary file.
    */
    ~TempFile(void) throw();

    /** createFile.
      Creates a new temporary file. If another file was associated to the
      instance, that will be removed first.

      @param prefix reference to the string used as prefix for the temp filename
    */
		void createFile(const std::string prefix);

    /// returns the temporary file name
		operator const std::string&(void) const;

    /// returns the temporary file name
		std::string getName(void) const;

	private:
		std::string tempFileName_;

    /// deletes the temporary file and resets the name
		void reset(void);
};

//---------------------------------------------------------------------------
}
#endif

