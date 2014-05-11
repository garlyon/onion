#pragma once


#include <cstdint>
#include <initializer_list>
#include <utility>


namespace Math_NS
{
  template <size_t n>
  struct Long
  {
    using H = Long<n / 2>;
    using L = Long<n / 2>;

    Long( H hi, L lo ) : hi{ hi }, lo{ lo } {}
    Long( uint32_t u = 0 ) : lo{ u } {}

    //Long( const std::initializer_list<uint32_t>& v );

    Long( const Long& ) = default;
    Long& operator = ( const Long& ) = default;

    Long& operator += ( const Long& v ) { add( v ); return *this; }
    Long& operator -= ( const Long& v ) { sub( v ); return *this; }
    Long& operator *= ( const Long& v ) { mll( v ); return *this; }

    friend const Long operator + ( const Long& a, const Long& b ) { return Long( a ) += b; }
    friend const Long operator - ( const Long& a, const Long& b ) { return Long( a ) -= b; }
    friend const Long operator * ( const Long& a, const Long& b ) { return Long( a ) *= b; }

    friend const bool operator == ( const Long& a, const Long& b ) { return a.lo == b.lo && a.hi == b.hi; }
    friend const bool operator <  ( const Long& a, const Long& b ) { return a.hi < b.hi || ( a.hi == b.hi && a.lo < b.lo ); }

    using C = typename Long<n/2>::C;

    //  addition without carry
    C add( const Long& );
    //  addition with carry
    C adc( const Long&, C );
    //  subtraction without carry
    C sub( const Long& );
    //  subtraction with carry
    C sbc( const Long&, C );
    //  multiplication, returns only lower part
    void mll( const Long& );

    L lo;
    H hi;
  };


  template <> struct Long<32>;


  using Long32    = Long<32>;
  using Long64    = Long<64>;
  using Long128   = Long<128>;


  //  multiplication, results in doubled precision
  template <size_t n> const Long<2*n> mul( const Long<n>&, const Long<n>& );
}


///////////////////////////////////////////////////////////////////////////////


template <>
struct Math_NS::Long<32>
{
  using T = uint32_t;

  Long( T u = 0 ) : u{ u } {}
    
  Long( const Long& ) = default;
  Long& operator = ( const Long& ) = default;

  Long& operator += ( const Long& v ) { u += v.u; return *this; }
  Long& operator -= ( const Long& v ) { u -= v.u; return *this; }
  Long& operator *= ( const Long& v ) { u *= v.u; return *this; }

  friend const Long operator + ( const Long& a, const Long& b ) { return a.u + b.u; }
  friend const Long operator - ( const Long& a, const Long& b ) { return a.u - b.u; }
  friend const Long operator * ( const Long& a, const Long& b ) { return a.u * b.u; }

  friend const bool operator == ( const Long& a, const Long& b ) { return a.u == b.u; }
  friend const bool operator <  ( const Long& a, const Long& b ) { return a.u < b.u; }

  operator const T () const { return u; }

  using C = uint32_t;

  //  addition without carry flag; returns carry flag for the high part
  //  returns +1 for overflow
  //  returns -1 for underflow
  C add( T v )
  {
    T w = u;
    u += v;
    return ( v > 0 && u < w ) - ( v < 0 && u > w );
  }
  
  //  addition with carry flag; returns carry flag for the high part
  C adc( T v, C c )
  {
    //  this += v + c
    return add( v ) + add( c );
  }

  //  subtraction without carry flag; returns carry flag for the high part
  //  returns +1 for underflow
  //  returns -1 for overflow
  C sub( T v )
  {
    T w = u;
    u -= v;
    return ( v > 0 && u > w ) - ( v < 0 && u < w );
  }
  
  //  subtraction with carry flag; returns carry flag for the high part
  C sbc( const Long& v, C c )
  {
    //  this -= v + c
    return sub( v ) + sub( c );
  }

  //  multiplication, returns only lower part
  void mll( T v ) { u *= v; }
    
  T u;
};


///////////////////////////////////////////////////////////////////////////////


template <size_t n>
typename Math_NS::Long<n>::C Math_NS::Long<n>::add( const Long& v )
{
  return hi.adc( v.hi, lo.add( v.lo ) );
}


template <size_t n>
typename Math_NS::Long<n>::C Math_NS::Long<n>::adc( const Long& v, C c )
{
  return hi.adc( v.hi, lo.adc( v.lo, c ) );
}


template <size_t n>
typename Math_NS::Long<n>::C Math_NS::Long<n>::sub( const Long& v )
{
  return hi.sbc( v.hi, lo.sub( v.lo ) );
}


template <size_t n>
typename Math_NS::Long<n>::C Math_NS::Long<n>::sbc( const Long& v, C c )
{
  return hi.sbc( v.hi, lo.sbc( v.lo, c ) );
}


template <size_t n>
void Math_NS::Long<n>::mll( const Long& v )
{
  auto p = ( hi * v.lo + lo * v.hi );
  *this = mul( lo, v.lo );
  hi += p;
}


///////////////////////////////////////////////////////////////////////////////


template <size_t n>
const Math_NS::Long<2*n> Math_NS::mul( const Long<n>& a, const Long<n>& b )
{
  using L = Long<n>;
  using C = typename L::C;

  //  a = a.hi * M + a.lo, max a = M^2 - 1
  //  b = b.hi * M + b.lo, max b = M^2 - 1

  L hh = mul( a.hi, b.hi );  //  max hh = M^2 - 2M + 1
  L ll = mul( a.lo, b.lo );  //  max ll = M^2 - 2M + 1

  auto sa = a.hi;
  C ca = sa.add( a.lo );  //  a.hi + a.lo = sa + ca * M, max sa = M - 1

  auto sb = b.hi;
  C cb = sb.add( b.lo );  //  b.hi + b.lo = sb + cb * M, max sb = M - 1

  C c = ca & cb;

  L ss = mul( sa, sb );  //  ( a.hi + a.lo ) * ( b.hi + b.lo ) = ss + ( ca * sb + cb * sa ) * M + c * M^2, max ss = M^2 - 2M + 1

  if( ca ) ca = ss.hi.add( sb ); //  ss += ca * sb * M
  if( cb ) cb = ss.hi.add( sa ); //  ss += cb * sa * M

  //  ( a.hi + a.lo ) * ( b.hi + b.lo ) = ss + ( ca + cb + cc ) * M^2

  c += ca + cb;
  c -= ss.sub( hh ); //  underflow erases one carry flag
  c -= ss.sub( ll ); //  underflow erases one carry flag

  //  a.hi * b.lo + a.lo * a.hi = ( a.hi + a.lo ) * ( b.hi + b.lo ) - a.hi * b.hi - a.lo * b.lo
  //  ( a.hi + a.lo ) * ( b.hi + b.lo ) - a.hi * b.hi - a.lo * b.lo = ss + ( ca + cb + cc ) * M^2
  //  , ca + cb + cc = c
  
  //  a.hi * b.lo + a.lo * a.hi < 2 M^2, 0 <= c <= 1

  ca = ll.hi.add( ss.lo );
  cb = hh.lo.adc( ss.hi, c + ca );
  hh.hi.add( cb );
  
  return Long<2*n>( hh, ll );
}


//  multiplication, results in doubled precision
template <>
const Math_NS::Long64 Math_NS::mul( const Long32& a, const Long32& b )
{
  const uint64_t c = static_cast<uint64_t>( a.u ) * static_cast<uint64_t>( b.u );
  return Long64( static_cast<uint32_t>( c >> 32 ), static_cast<uint32_t>( c ) );
}



