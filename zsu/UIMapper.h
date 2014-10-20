//
//  Rev:          $Id: UIMapper.h,v 1.1 2004/11/25 08:39:35 evert Exp $
//
//  Author:       Evert Haasdijk
//  Contact:      evert@zukkespijkers.nl
//
//  copyright (c) 2004 Zukke Spijkers BV
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
#ifndef UI_MAPPER_H
#define UI_MAPPER_H

//---------------------------------------------------------------------------
                             
#include <zsu/config.h>

#include <exception>
#include <map>
#include <string>

//---------------------------------------------------------------------------
namespace zsu
{
//---------------------------------------------------------------------------
/**
  Allows easy UI by automatically mapping enumeration types to string and
  vice versa.

  The idea is to use this class by instantiating a particular specification
  like so:
  \code
  enum Fruit {apple = 0, orange, banana};
  Fruit fruits[] = {apple, orange, banana};
  std::string labels[] = {"pomme", "orange", "banane"};

  typedef zsu::UIMapper<Fruit> FruitMapper;
  template<>
  FruitMapper FruitMapper::instance_(3, fruits, labels);
  \endcode
 */
template<typename T>
class ZSU_CLASS UIMapper
{
  public:
    typedef T enumeration;
    /**
      Destructor.

      Empty, but must be defined for safe inheritance.
     */
    virtual ~UIMapper(void) { /*nix */ }

    /**
      Returns the string representation of \a value.

      \throw \c std::range_error if \a the enumeration value is not mapped to
      any string.
     */
    std::string get(enumeration value) const;

    /**
      Returns the enumeration value identified by \a label

      \throw \c std::range_error if \a label does not denote a known enumeration
      value
    */
    enumeration get(std::string label) const;

    /**
      Provides access to the (singleton) instance.

      \TODO Use Loki::Singleton
     */
    static const UIMapper& get(void) { return instance_; }

  protected:
    /**
      Constructor.
      Only accessible to derived classes. Use \c get() to access the singleton
      instance.
     */
    UIMapper(unsigned n, enumeration* values, std::string* labels);

  private:
    /**
      The singleton instance.
      \TODO Use Loki::Singleton
     */
    static UIMapper<enumeration> instance_;

    /// Map enumeration values to strings
    typedef std::map<enumeration, std::string> ValueMap;
    ValueMap valueMap_;

    /// Map strings to enumeration values
    typedef std::map<std::string, enumeration> StringMap;
    StringMap stringMap_;
};

//---------------------------------------------------------------------------
template <typename T>
T UIMapper<T>::get(std::string str) const
{
  StringMap::const_iterator loc( stringMap_.find(str) );
  if (loc == stringMap_.end())
  {
    throw std::range_error(str);
  }
  // else

  return loc->second;
}
//---------------------------------------------------------------------------
template <typename T>
std::string UIMapper<T>::get(T value) const
{
  ValueMap::const_iterator loc( valueMap_.find(value) );
  if (loc == valueMap_.end())
  {
    throw std::range_error("");
  }
  // else

  return loc->second;
}
//---------------------------------------------------------------------------
template <typename T>
UIMapper<T>::UIMapper(unsigned n, T* values, std::string* labels)
{
  for (unsigned i = 0; i < n; ++i)
  {
    valueMap_[values[i]] = labels[i];
    stringMap_[labels[i]] = values[i];
  }
}          
//---------------------------------------------------------------------------
}  // end namespace        
//---------------------------------------------------------------------------
#endif

