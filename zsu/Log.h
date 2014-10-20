//
//  Rev:          $Id: Log.h,v 1.3 2004/03/04 07:53:30 evert Exp $
//
//  Author:       Evert Haasdijk
//  Contact:      evert@zukkespijkers.nl
//
//  Simple logging by redirecting cout, cerr and clog to a file.
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

#ifndef LOG_H
#define LOG_H

//---------------------------------------------------------------------------
#include <string>
#include <streambuf>
#include <fstream>
           
#include <zsu/config.h>

//---------------------------------------------------------------------------
namespace zsu
{

//---------------------------------------------------------------------------
/**
  Redirects cerr, clog and cout to a file.
*/
class ZSU_CLASS Log
{
  public:
    /**
      Tells a Log instance which standard streams to redirect. Values can be
      combined to log multiple standard streams to a Log.
    */
    enum StreamID {
      /// None: no redirection
      None = 0x00,
      /// Redirect stdout
      StdOut = 0x01,
      /// Redirect stderr
      StdErr = 0x02,
      /// Redirect stdlog
      StdLog = 0x04
    };
    
    /**
      Creates an ofstream and redirects output to cerr, clog and cout to that
      file.

      @param logName Name of the logfile.
      @param append If true, the file will be appended to, if false, it will be
        overwritten
      @param whichStreams StreamID specifies which standard streams to redirect.
        Defaults to StdOut | StdErr | StdLog (i.e. all standard output streams).
      @pre logName is a valid filename

      @todo use boost::FileSystem::path
    */
    Log(const std::string logName,
        bool append = false,
        StreamID whichStreams = StreamID(StdOut | StdErr | StdLog) );

    /** Destructor.

      Closes the log file and redirects the selected output streams to
      their original buffers.
    */
    virtual ~Log(void);

  private:
    std::ofstream log_;
    std::streambuf *cerrBuf_;
    std::streambuf *clogBuf_;
    std::streambuf *coutBuf_;
};

//---------------------------------------------------------------------------
} // end namespace

//---------------------------------------------------------------------------
#endif
