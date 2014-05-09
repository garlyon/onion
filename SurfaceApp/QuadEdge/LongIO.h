#pragma once


#include "Long.h"
#include <iostream>
#include <iomanip>


namespace Math_NS
{
  template <typename T> std::ostream& operator << ( std::ostream& s, const Long<T>& v ) { return s << v.hi << ' ' << v.lo; }
  template <typename T> std::istream& operator >> ( std::istream& s,       Long<T>& v ) { return s >> v.hi >> v.lo; }

  template <typename T> std::wostream& operator << ( std::wostream& s, const Long<T>& v ) { return s << v.hi << L' ' << v.lo; }
  template <typename T> std::wistream& operator >> ( std::wistream& s, Long<T>& v )       { return s >> v.hi >> v.lo; }
}


template <> std::ostream& Math_NS::operator << ( std::ostream& s, const Long32& v )
{
  return s << std::hex << std::setw( 8 ) << std::setfill( '0' ) << v.u;
}

template <> std::istream& Math_NS::operator >> ( std::istream& s, Long32& v )
{
  return s >> std::hex >> v.u;
}


template <> std::wostream& Math_NS::operator << ( std::wostream& s, const Long32& v )
{
  return s << std::hex << std::setw( 8 ) << std::setfill( L'0' ) << v.u;
}

template <> std::wistream& Math_NS::operator >> ( std::wistream& s, Long32& v )
{
  return s >> std::hex >> v.u;
}