//
//  Rev:          $Id: Log.cpp,v 1.4 2005/08/08 14:13:15 evert Exp $
//
//  Author:       Evert Haasdijk
//  Contact:      evert@zukkespijkers.nl
//
//  copyright (c) 2003 - 2004 Zukke Spijkers BV
//
//  Simple logging by redirecting cout, cerr and clog to a file.
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
               
static const char* sccsid = "$Id: Log.cpp,v 1.4 2005/08/08 14:13:15 evert Exp $";

#include <zsu/Log.h>

#include <iostream>

//---------------------------------------------------------------------------

using zsu::Log;

//---------------------------------------------------------------------------
Log::Log(const std::string logName, bool append, StreamID whichStreams) :
  cerrBuf_(0),
  clogBuf_(0),
  coutBuf_(0)
{
  //
  // let cerr, clog and cout write to a file
  //
  if (append)
  {
    log_.open(logName.c_str(), std::ios_base::out|std::ios_base::app);
  }
  else
  {
    log_.open(logName.c_str());
  }

  if (log_.fail())
  {
    return;
  }

  if (whichStreams & StdOut)
  {
    coutBuf_ = std::cout.rdbuf(log_.rdbuf());
  }
  if (whichStreams & StdErr)
  {
    cerrBuf_ = std::cerr.rdbuf(log_.rdbuf());
  }
  if (whichStreams & StdLog)
  {
    clogBuf_ = std::clog.rdbuf(log_.rdbuf());
  }
}

//---------------------------------------------------------------------------
Log::~Log(void)
{
  //
  // restore cerr, clog, cout buffers
  //
  if (coutBuf_) std::cout.rdbuf(coutBuf_);
  if (cerrBuf_) std::cerr.rdbuf(cerrBuf_);
  if (clogBuf_) std::clog.rdbuf(clogBuf_);

  log_.close();
}
//---------------------------------------------------------------------------
