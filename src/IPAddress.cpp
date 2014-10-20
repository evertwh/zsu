//
//  Rev:          $Id: IPAddress.cpp,v 1.3 2005/08/08 14:13:15 evert Exp $
//
//  Author:       Evert Haasdijk
//  Contact:      evert@zukkespijkers.nl
//
//  Class that parses, stores and manipulates IP addresses.
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
                 
static const char* sccsid = "$Id: IPAddress.cpp,v 1.3 2005/08/08 14:13:15 evert Exp $";

#include <algorithm>
#include <vector>

#include <boost/tokenizer.hpp>

#include <zsu/IPAddress.h>

//---------------------------------------------------------------------------

using zsu::IPAddress;
using std::string;

//---------------------------------------------------------------------------

IPAddress::IPAddress(const string address)
{
  parse(address);
}                
//---------------------------------------------------------------------------

IPAddress& IPAddress::operator=(const string address)
{
  parse(address);

  return *this;
}

//---------------------------------------------------------------------------

string IPAddress::getRoot(void) const
{
  return root_;
}
//---------------------------------------------------------------------------

void IPAddress::setRoot(const string root)
{
  root_ = root;
}
//---------------------------------------------------------------------------

string IPAddress::getDomain(void) const
{
  return domain_;
}
//---------------------------------------------------------------------------

void IPAddress::setDomain(const string domain)
{
  domain_ = domain;
}
//---------------------------------------------------------------------------
string IPAddress::getSubDomain(void) const
{
  return subDomain_;
}
//---------------------------------------------------------------------------
void IPAddress::setSubDomain(const string subDomain)
{
  subDomain_ = subDomain;
}
//---------------------------------------------------------------------------
string IPAddress::getHost(void) const
{
  return host_;
}
//---------------------------------------------------------------------------
void IPAddress::setHost(const string host)
{
  host_ = host;
}
//---------------------------------------------------------------------------

bool operator<(const IPAddress& lhs, const IPAddress& rhs)
{
  if (lhs.getRoot() < rhs.getRoot()) return true;
  // else
  if (lhs.getRoot() > rhs.getRoot()) return false;
  // else
  if (lhs.getDomain() < rhs.getDomain()) return true;
  // else
  if (lhs.getDomain() > rhs.getDomain()) return false;
  // else
  if (lhs.getSubDomain() < rhs.getSubDomain()) return true;
  // else
  if (lhs.getSubDomain() > rhs.getSubDomain()) return false;
  // else
  return lhs.getHost() < rhs.getHost();
}
//---------------------------------------------------------------------------

string IPAddress::getFQDN(void) const
{
  string retVal;

  if (!host_.empty())
  {
    retVal += host_ + ".";
  }
  if (!subDomain_.empty())
  {
    retVal += subDomain_ + ".";
  }
  if (!domain_.empty())
  {
    retVal += domain_ + ".";
  }

  retVal += root_;

  return retVal;
}
//---------------------------------------------------------------------------
void IPAddress::erase(void)
{
  host_ = string();
  subDomain_ = string();
  domain_ = string();
  root_ = string();
}
//---------------------------------------------------------------------------
void IPAddress::parse(const string address)
{
  erase();
  
  typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
  boost::char_separator<char> sep(".");

  tokenizer tokens(address, sep);
  //
  // use intermediate vector, because we have to loop over the tokens in
  // reverse.
  //
  std::vector<string> tokenVector(tokens.begin(), tokens.end());
  std::vector<string>::reverse_iterator i = tokenVector.rbegin();

  //
  // Provisionally read root - it may actually be the host name
  //
  string hostOrRoot;
  if (i != tokenVector.rend())
  {
    hostOrRoot = *i;
    ++i;
  }

  if (i != tokenVector.rend())
  {
    setDomain(*i);
    ++i;
  }

  if (domain_.empty())
  {
    setHost(hostOrRoot);
    return;
  }
  // else
  
  setRoot(hostOrRoot);

  //
  // read third part provisionally: it may be the subdomain or the host
  // we'll determine that later
  //
  string hostOrSubDomain;
  if (i != tokenVector.rend())
  {
    hostOrSubDomain = *i;
    ++i;
  }

  if (i != tokenVector.rend())
  {
    setHost(*i);
  }

  if (host_.empty())   // no fourth entry was found - use tmp for host
  {
    setHost(hostOrSubDomain);
  }
  else                    // four-part address - use tmp for subdomain
  {
    setSubDomain(hostOrSubDomain);
  }                        
}
//---------------------------------------------------------------------------
void IPAddress::validate(const std::string addressPart)
{
  // TODO: check for illegal characters.
}
//---------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const zsu::IPAddress& address)
{
  const char dot('.');
  if (!address.getHost().empty())
    os << address.getHost() << dot;
  if (!address.getSubDomain().empty())
    os << address.getSubDomain() << dot;
  if (!address.getDomain().empty())
    os << address.getDomain() << dot;

  return os << address.getRoot();
}
//---------------------------------------------------------------------------


