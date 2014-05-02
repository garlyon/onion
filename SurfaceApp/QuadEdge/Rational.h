#pragma once


#include "Types.h"


namespace Math_NS
{
  template <typename T>
  struct Rational
  {
    //  r = ( n / d )
    T n;
    T d;

    using type = T;

    Rational( T n = 0, T d = 1 ) : n{ n }, d{ d } {}

    Rational& operator += ( const Rational& );
    Rational& operator -= ( const Rational& );
    Rational& operator *= ( const Rational& );
    Rational& operator /= ( const Rational& );

    const Rational<T> inv() const { return { d, n }; }
  };


  using R = Rational<I>;


  template <typename T> const Rational<T> operator + ( const Rational<T>&, const Rational<T>& );
  template <typename T> const Rational<T> operator - ( const Rational<T>&, const Rational<T>& );
  template <typename T> const Rational<T> operator * ( const Rational<T>&, const Rational<T>& );
  template <typename T> const Rational<T> operator / ( const Rational<T>&, const Rational<T>& );

  template <typename T> const Rational<T> operator - ( const Rational<T>& );

  template <typename T> const bool operator == ( const Rational<T>&, const Rational<T>& );
  template <typename T> const bool operator != ( const Rational<T>&, const Rational<T>& );
}


///////////////////////////////////////////////////////////////////////////////


template <typename T> Math_NS::Rational<T>& Math_NS::Rational<T>::operator += ( const Rational& v )
{
  if( d == v.d ) { n += v.n; return *this; }

  n *= v.d;
  n += v.n * d;
  d *= v.d;

  return *this;
}


template <typename T> Math_NS::Rational<T>& Math_NS::Rational<T>::operator -= ( const Rational& v )
{
  if( d == v.d ) { n -= v.n; return *this; }
  
  n *= v.d;
  n -= v.n * d;
  d *= v.d;

  return *this;
}


template <typename T> Math_NS::Rational<T>& Math_NS::Rational<T>::operator *= ( const Rational& v )
{
  if( n == v.d ) { n = v.n; return *this; }
  if( d == v.n ) { d = v.d; return *this; }

  n *= v.n;
  d *= v.d;

  return *this;
}


template <typename T> Math_NS::Rational<T>& Math_NS::Rational<T>::operator /= ( const Rational& v )
{
  return ( *this ) *= ( v.inv() );
}


template <typename T> const Math_NS::Rational<T> Math_NS::operator + ( const Rational<T>& l, const Rational<T>& r ) { return Rational<T>{ l } += r; }
template <typename T> const Math_NS::Rational<T> Math_NS::operator - ( const Rational<T>& l, const Rational<T>& r ) { return Rational<T>{ l } -= r; }
template <typename T> const Math_NS::Rational<T> Math_NS::operator * ( const Rational<T>& l, const Rational<T>& r ) { return Rational<T>{ l } *= r; }
template <typename T> const Math_NS::Rational<T> Math_NS::operator / ( const Rational<T>& l, const Rational<T>& r ) { return Rational<T>{ l } /= r; }


template <typename T> const Math_NS::Rational<T> Math_NS::operator - ( const Rational<T>& v ) { return Rational<T>{ -v.n, v.d }; }


template <typename T> const bool Math_NS::operator == ( const Rational<T>& l, const Rational<T>& r ) { return ( l.n == r.n && l.d == r.d ) || ( l.n * r.d == r.n * l.d ); }
template <typename T> const bool Math_NS::operator != ( const Rational<T>& l, const Rational<T>& r ) { return !( l == r ); }