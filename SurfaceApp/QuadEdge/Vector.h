#pragma once


#include "Types.h"


namespace Math_NS
{
  template <typename T>
  struct Vector
  {
    T x{ 0 };
    T y{ 0 };
    T z{ 0 };

    using type = T;

    Vector() = default;
    Vector( const Vector& ) = default;

    Vector( T x, T y, T z ) : x{ x }, y{ y }, z{ z } {}

    template <typename O>
    explicit Vector( const Vector<O>& v ) : Vector( v.x, v.y, v.z ) {}

    Vector& operator += ( const Vector& );
    Vector& operator -= ( const Vector& );

    Vector& operator *= ( const T );
    Vector& operator /= ( const T );

    const T length() const;
    const T lengthSqr() const;
  };


  using VectorI = Vector<I>;
  using VectorD = Vector<double>;


  template <typename T> const Vector<T> operator + ( const Vector<T>&, const Vector<T>& );
  template <typename T> const Vector<T> operator - ( const Vector<T>&, const Vector<T>& );
  template <typename T> const Vector<T> operator ^ ( const Vector<T>&, const Vector<T>& );

  template <typename T> const Vector<T> operator * ( const Vector<T>&, const T );
  template <typename T> const Vector<T> operator * ( const T, const Vector<T>& );
  template <typename T> const Vector<T> operator / ( const Vector<T>&, const T );

  template <typename T> const T operator * ( const Vector<T>&, const Vector<T>& );

  template <typename T> const Vector<T> operator - ( const Vector<T>& );

  template <typename T> const bool operator == ( const Vector<T>&, const Vector<T>& );
  template <typename T> const bool operator != ( const Vector<T>&, const Vector<T>& );
}


///////////////////////////////////////////////////////////////////////////////


template <typename T> Math_NS::Vector<T>& Math_NS::Vector<T>::operator += ( const Vector& v )
{
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}


template <typename T> Math_NS::Vector<T>& Math_NS::Vector<T>::operator -= ( const Vector& v )
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}


template <typename T> Math_NS::Vector<T>& Math_NS::Vector<T>::operator *= ( const T t )
{
  x *= t;
  y *= t;
  z *= t;
  return *this;
}


template <typename T> Math_NS::Vector<T>& Math_NS::Vector<T>::operator /= ( const T t )
{
  x /= t;
  y /= t;
  z /= t;
  return *this;
}


template <typename T> const T Math_NS::Vector<T>::lengthSqr() const { return (*this) * (*this); }
template <typename T> const T Math_NS::Vector<T>::length() const { return std::sqrt( lengthSqr() ); }

template <typename T> const Math_NS::Vector<T> Math_NS::operator + ( const Vector<T>& l, const Vector<T>& r ) { return Vector<T>{ l } += r; }
template <typename T> const Math_NS::Vector<T> Math_NS::operator - ( const Vector<T>& l, const Vector<T>& r ) { return Vector<T>{ l } -= r; }
template <typename T> const Math_NS::Vector<T> Math_NS::operator ^ ( const Vector<T>& l, const Vector<T>& r ) { return { l.y * r.z - l.z * r.y, l.z * r.x - l.x * r.z, l.x * r.y - l.y * r.x }; }

template <typename T> const Math_NS::Vector<T> Math_NS::operator * ( const Vector<T>& v, const T t ) { return Vector<T>{ v } *= t; }
template <typename T> const Math_NS::Vector<T> Math_NS::operator * ( const T t, const Vector<T>& v ) { return Vector<T>{ v } *= t; }
template <typename T> const Math_NS::Vector<T> Math_NS::operator / ( const Vector<T>& v, const T t ) { return Vector<T>{ v } /= t; }

template <typename T> const T Math_NS::operator * ( const Vector<T>& l, const Vector<T>& r ) { return l.x * r.x + l.y * r.y + l.z * r.z; }

template <typename T> const Math_NS::Vector<T> Math_NS::operator - ( const Vector<T>& v ) { return { -v.x, -v.y, -v.z }; }

template <typename T> const bool Math_NS::operator == ( const Vector<T>& l, const Vector<T>& r ) { return l.x == r.x && l.y == r.y && l.z == r.z; }
template <typename T> const bool Math_NS::operator != ( const Vector<T>& l, const Vector<T>& r ) { return !( l == r ); }