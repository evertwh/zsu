//
//  Rev:          $Id: TempFile.cpp,v 1.3 2005/08/08 14:13:15 evert Exp $
//
//  Author:       Evert Haasdijk
//  Contact:      evert@zukkespijkers.nl
//
//  copyright (c) 2003 - 2004 Zukke Spijkers BV
//
//  Utility to create temp files. Borland specific.
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
       
static const char* sccsid = "$Id: TempFile.cpp,v 1.3 2005/08/08 14:13:15 evert Exp $";

#include <mem>

#include <dir.h>
#include <windows.h>

#include <zsu/TempFile.h>

//---------------------------------------------------------------------------

using zsu::TempFile;
using std::string;
using std::auto_ptr;

//---------------------------------------------------------------------------
TempFile::TempFile(void)
{
}

//---------------------------------------------------------------------------
TempFile::TempFile(const string prefix)
{
  createFile(prefix);
}

//---------------------------------------------------------------------------
TempFile::~TempFile(void) throw()
{
  try
  {
    reset();
  }
  catch (...)
  {
  }
}

//---------------------------------------------------------------------------
void TempFile::createFile(const string prefix)
{
  reset();

  string actualPrefix(prefix);
  if (prefix.empty()) actualPrefix = "ohm";

  auto_ptr<char> tmpPath(new char[MAXPATH]);
  GetTempPath(MAXPATH, tmpPath.get());

  auto_ptr<char> tmpFileName(new char[MAXPATH]);
  GetTempFileName(tmpPath.get(), actualPrefix.c_str(), 0, tmpFileName.get());

  tempFileName_ = tmpFileName.get();
}

//---------------------------------------------------------------------------
TempFile::operator const string& (void) const
{
  return tempFileName_;
}

//---------------------------------------------------------------------------
void TempFile::reset(void)
{
  if (!tempFileName_.empty()) ::DeleteFile(tempFileName_.c_str());
  tempFileName_.erase();
}

//---------------------------------------------------------------------------
string TempFile::getName(void) const
{
  return tempFileName_;
}

//---------------------------------------------------------------------------

