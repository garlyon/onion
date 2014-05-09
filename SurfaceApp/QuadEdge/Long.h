#pragma once


#include <cstdint>


namespace Math_NS
{
  template <typename T>
  class Long
  {
  public:

    Long( T hi, T lo ) : hi{ hi }, lo{ lo } {}
    Long( uint32_t u = 0 ) : lo{ u } {}

    Long( const Long& ) = default;
    Long& operator = ( const Long& ) = default;

    Long& operator += ( const Long& v ) { adc( v, 0 ); return *this; }
    Long& operator -= ( const Long& v ) { sbc( v, 0 ); return *this; }
    Long& operator *= ( const Long& v ) { mll( v ); return *this; }

    using C = uint32_t;
    using X = Long<Long<T>>;

    //  add carry flag; return carry flag if overflow still happens
    C carry( C );
    //  addition with carry; returns 0 or 1
    C adc( const Long&, C );
    //  subtraction with carry; returns 0 or 1
    C sbc( const Long&, C );
    //  multiplication, returns only lower part
    void mll( const Long& );
    //  multiplication, results in doubled precision
    static X mul( const Long&, const Long& );

    T lo, hi;
  };


  template <> class Long<uint16_t>;


  using Long32 = Long<uint16_t>;
  using Long64 = Long<Long32>;
  using Long128 = Long<Long64>;


  template <typename T> const Long<T> operator + ( const Long<T>& a, const Long<T>& b ) { return Long<T>( a ) += b; }
  template <typename T> const Long<T> operator - ( const Long<T>& a, const Long<T>& b ) { return Long<T>( a ) -= b; }
  template <typename T> const Long<T> operator * ( const Long<T>& a, const Long<T>& b ) { return Long<T>( a ) *= b; }

  template <typename T> const bool operator == ( const Long<T>& a, const Long<T>& b ) { return a.lo == b.lo && a.hi == b.hi; }
  template <typename T> const bool operator <  ( const Long<T>& a, const Long<T>& b ) { return a.hi < b.hi || ( a.hi == b.hi && a.lo < b.lo ); }
}


///////////////////////////////////////////////////////////////////////////////


template <>
class Math_NS::Long<uint16_t>
{
public:

  Long( uint32_t u = 0 ) : u{ u } {}
    
  Long( const Long& ) = default;
  Long& operator = ( const Long& ) = default;

  Long& operator += ( const Long& v ) { u += v.u; return *this; }
  Long& operator -= ( const Long& v ) { u -= v.u; return *this; }
  Long& operator *= ( const Long& v ) { u *= v.u; return *this; }

  using C = uint32_t;
  using X = Long<Long<uint16_t>>;

  //  add carry flag; return carry flag if overflow still happens
  C carry( C c ) { uint32_t t{ u }; return ( u += c ) < t; }
  //  addition with carry; returns 0 or 1
  C adc( const Long& v, C c ) { uint32_t t{ u }; return ( u += v.u + c ) < t; }
  //  subtraction with carry; returns 0 or 1
  C sbc( const Long& v, C c ) { uint32_t t{ u }; return ( u -= v.u + c ) > t; }
  //  multiplication, results in doubled precision
  static X mul( const Long& a, const Long& b )
  {
    const uint64_t c = static_cast<uint64_t>( a.u ) * static_cast<uint64_t>( b.u );
    return reinterpret_cast<const X&>( c );
  }
    
  uint32_t u;
};


template <> const bool Math_NS::operator == ( const Long32& a, const Long32& b ) { return a.u == b.u; }
template <> const bool Math_NS::operator <  ( const Long32& a, const Long32& b ) { return a.u < b.u; }


///////////////////////////////////////////////////////////////////////////////


template <typename T>
typename Math_NS::Long<T>::C Math_NS::Long<T>::carry( C c )
{
  return hi.carry( lo.carry( c ) );
}


template <typename T>
typename Math_NS::Long<T>::C Math_NS::Long<T>::adc( const Long& v, C c )
{
  return hi.adc( v.hi, lo.adc( v.lo, c ) );
}


template <typename T>
typename Math_NS::Long<T>::C Math_NS::Long<T>::sbc( const Long& v, C c )
{
  return hi.sbc( v.hi, lo.sbc( v.lo, c ) );
}


template <typename T>
void Math_NS::Long<T>::mll( const Long& v )
{
  T p = ( hi * v.lo + lo * v.hi );
  *this = T::mul( lo, v.lo );
  hi += p;
}


template <typename T>
typename Math_NS::Long<T>::X Math_NS::Long<T>::mul( const Long& a, const Long& b )
{
  //  a = a.hi * M + a.lo, max a = M^2 - 1
  //  b = b.hi * M + b.lo, max b = M^2 - 1

  Long hh = T::mul( a.hi, b.hi );  //  max hh = M^2 - 2M + 1
  Long ll = T::mul( a.lo, b.lo );  //  max ll = M^2 - 2M + 1

  T sa = a.hi;
  C ca = sa.adc( a.lo, 0 );  //  a.hi + a.lo = sa + ca * M, max sa = M - 1

  T sb = b.hi;
  C cb = sb.adc( b.lo, 0 );  //  b.hi + b.lo = sb + cb * M, max sb = M - 1

  C c = ca & cb;

  Long ss = T::mul( sa, sb );  //  ( a.hi + a.lo ) * ( b.hi + b.lo ) = ss + ( ca * sb + cb * sa ) * M + c * M^2, max ss = M^2 - 2M + 1

  if( ca ) ca = ss.hi.adc( sb, 0 ); //  ss += ca * sb * M
  if( cb ) cb = ss.hi.adc( sa, 0 ); //  ss += cb * sa * M

  //  ( a.hi + a.lo ) * ( b.hi + b.lo ) = ss + ( ca + cb + cc ) * M^2

  c += ca + cb;
  c -= ss.sbc( hh, 0 ); //  underflow erases one carry flag
  c -= ss.sbc( ll, 0 ); //  underflow erases one carry flag

  //  a.hi * b.lo + a.lo * a.hi = ( a.hi + a.lo ) * ( b.hi + b.lo ) - a.hi * b.hi - a.lo * b.lo
  //  ( a.hi + a.lo ) * ( b.hi + b.lo ) - a.hi * b.hi - a.lo * b.lo = ss + ( ca + cb + cc ) * M^2
  //  , ca + cb + cc = c
  
  //  a.hi * b.lo + a.lo * a.hi < 2 M^2, 0 <= c <= 1

  ca = ll.hi.adc( ss.lo, 0 );
  cb = hh.lo.adc( ss.hi, c + ca );
  hh.hi.carry( cb );
  
  return X( hh, ll );
}





