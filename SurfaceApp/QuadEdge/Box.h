#pragma once


#include "Vector.h"
#include <limits>


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


  using BoxI = Box<VectorI::type>;
  using BoxD = Box<VectorD::type>;
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
  min.x = std::min( min.x, box.min.x );
  min.y = std::min( min.y, box.min.y );
  min.z = std::min( min.z, box.min.z );
  max.x = std::max( max.x, box.max.x );
  max.y = std::max( max.y, box.max.y );
  max.z = std::max( max.z, box.max.z );
  return *this;
}