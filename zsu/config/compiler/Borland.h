//
//  Rev:          $Id: Borland.h,v 1.2 2004/03/04 07:53:30 evert Exp $
//
//  Author:       Evert Haasdijk
//  Contact:      evert@zukkespijkers.nl
//
//  Compiler-specific defines and directives for Borland C++ compilers
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

#ifndef __BORLAND_H__
#define __BORLAND_H__

#if defined(__BORLANDC__)
#  if defined(ZSU_DLL_PROJECT)
#    define ZSU_CLASS __declspec(dllexport)
#    define ZSU_EXPORT __declspec(dllexport)
#  else
#    define ZSU_CLASS                       
#    define ZSU_EXPORT
#  endif
#endif

#endif  // __BORLAND_H__

