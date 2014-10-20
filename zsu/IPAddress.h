//
//  Rev:          $Id: IPAddress.h,v 1.4 2005/08/08 14:13:15 evert Exp $
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

#ifndef IPAddressH
#define IPAddressH
//---------------------------------------------------------------------------

#include <exception>
#include <string>
#include <iostream>
      
#include <zsu/config.h>

//---------------------------------------------------------------------------

namespace zsu
{
//---------------------------------------------------------------------------

/// Doens't work for numeric IP address tuples.
class ZSU_CLASS IPAddress
{
  public:
    /// default constructor
    IPAddress(void) {};       

    /// destructor, virtual for safe inheritance
    virtual ~IPAddress(void) {};

    IPAddress(const std::string address);
    IPAddress& operator=(const std::string address);

    /// returns the fully qualified domain name
    std::string getFQDN(void) const;

    std::string getRoot(void) const;
    void setRoot(const std::string);
    std::string getDomain(void) const;
    void setDomain(const std::string);
    std::string getSubDomain(void) const;
    void setSubDomain(const std::string);
    std::string getHost(void) const;
    void setHost(const std::string);

    void erase(void);

  private:
    void parse(const std::string address);
    void validate(const std::string addressPart);

    std::string host_;
    std::string subDomain_;
    std::string domain_;
    std::string root_;
};
//---------------------------------------------------------------------------
}  // namespace
                                                                             
//---------------------------------------------------------------------------

/**
 Comparison operator. Provides lexical comparison on root, (sub-)domain and
 host name, in that order. For instance,
 \li zz.foo.com < aa.foo.org
 \li aa.foo.org < bb.foo.org
 \li zz.foo.org < aa.aa.foo.org
 */
bool ZSU_EXPORT operator<(const zsu::IPAddress& lhs, const zsu::IPAddress& rhs);

/**
  Output an IPAddress.
 */
std::ostream& ZSU_EXPORT operator<<(std::ostream& os, const zsu::IPAddress& address);

//---------------------------------------------------------------------------
#endif
