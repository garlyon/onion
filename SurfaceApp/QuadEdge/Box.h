#pragma once


#include "Types.h"
#include "Vector.h"
#include <limits>
#include <algorithm>


namespace Math_NS
{
  template <typename T>
  struct Box
  {
    Vector<T> min{ std::numeric_limits<T>::max(), std::numeric_limits<T>::max(), std::numeric_limits<T>::max() };
    Vector<T> max{ std::numeric_limits<T>::lowest(), std::numeric_limits<T>::lowest(), std::numeric_limits<T>::lowest() };

    using type = T;

    Box() = default;
    Box( const Vector<T>& min, const Vector<T>& max ) : min{ min }, max{ max } {}

    const bool empty() const { return min.x > max.x || min.y > max.y || min.z > max.z; }

    Box& operator += ( const Vector<T>& );
    Box& operator += ( const Box& );
  };


  using BoxI = Box<I>;
  using BoxD = Box<D>;
}


///////////////////////////////////////////////////////////////////////////////


template <typename T> Math_NS::Box<T>& Math_NS::Box<T>::operator += ( const Vector<T>& v )
{
  min.x = std::min( min.x, v.x );
  min.y = std::min( min.y, v.y );
  min.z = std::min( min.z, v.z );
  max.x = std::max( max.x, v.x );
  max.y = std::max( max.y, v.y );
  max.z = std::max( max.z, v.z );
  return *this;
}


template <typename T> Math_NS::Box<T>& Math_NS::Box<T>::operator += ( const Box<T>& b )
{
  min.x = std::min( min.x, b.min.x );
  min.y = std::min( min.y, b.min.y );
  min.z = std::min( min.z, b.min.z );
  max.x = std::max( max.x, b.max.x );
  max.y = std::max( max.y, b.max.y );
  max.z = std::max( max.z, b.max.z );
  return *this;
}