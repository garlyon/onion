#pragma once


#include <cstdint>


namespace Math_NS
{
  template <size_t n>
  struct Long
  {
    using H = Long<n/2>;
    using L = Long<n/2>;

    Long( H hi, L lo ) : hi{ hi }, lo{ lo } {}
    Long( uint32_t u = 0 ) : lo{ u } {}

    Long( const Long& ) = default;
    Long& operator = ( const Long& ) = default;

    Long& operator += ( const Long& v ) { adc( v, 0 ); return *this; }
    Long& operator -= ( const Long& v ) { sbc( v, 0 ); return *this; }
    Long& operator *= ( const Long& v ) { mll( v ); return *this; }

    friend const Long operator + ( const Long& a, const Long& b ) { return Long( a ) += b; }
    friend const Long operator - ( const Long& a, const Long& b ) { return Long( a ) -= b; }
    friend const Long operator * ( const Long& a, const Long& b ) { return Long( a ) *= b; }

    friend const bool operator == ( const Long& a, const Long& b ) { return a.lo == b.lo && a.hi == b.hi; }
    friend const bool operator <  ( const Long& a, const Long& b ) { return a.hi < b.hi || ( a.hi == b.hi && a.lo < b.lo ); }

    using C = typename Long<n/2>::C;

    //  add carry flag; return carry flag if overflow still happens
    C carry( C );
    //  addition with carry; returns 0 or 1
    C adc( const Long&, C );
    //  subtraction with carry; returns 0 or 1
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
  Long( uint32_t u = 0 ) : u{ u } {}
    
  Long( const Long& ) = default;
  Long& operator = ( const Long& ) = default;

  Long& operator += ( const Long& v ) { u += v.u; return *this; }
  Long& operator -= ( const Long& v ) { u -= v.u; return *this; }
  Long& operator *= ( const Long& v ) { u *= v.u; return *this; }

  friend const Long operator + ( const Long& a, const Long& b ) { return Long( a ) += b; }
  friend const Long operator - ( const Long& a, const Long& b ) { return Long( a ) -= b; }
  friend const Long operator * ( const Long& a, const Long& b ) { return Long( a ) *= b; }

  friend const bool operator == ( const Long& a, const Long& b ) { return a.u == b.u; }
  friend const bool operator <  ( const Long& a, const Long& b ) { return a.u < b.u; }

  using C = uint32_t;

  //  add carry flag; return carry flag if overflow still happens
  C carry( C c ) { auto t = u; return ( u += c ) < t; }
  //  addition with carry; returns 0 or 1
  C adc( const Long& v, C c ) { auto t = u; return ( u += v.u + c ) < t; }
  //  subtraction with carry; returns 0 or 1
  C sbc( const Long& v, C c ) { auto t = u; return ( u -= v.u + c ) > t; }
  //  multiplication, returns only lower part
  void mll( const Long& v ) { u *= v.u; }
    
  uint32_t u;
};


///////////////////////////////////////////////////////////////////////////////


template <size_t n>
typename Math_NS::Long<n>::C Math_NS::Long<n>::carry( C c )
{
  return hi.carry( lo.carry( c ) );
}


template <size_t n>
typename Math_NS::Long<n>::C Math_NS::Long<n>::adc( const Long& v, C c )
{
  return hi.adc( v.hi, lo.adc( v.lo, c ) );
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
  C ca = sa.adc( a.lo, 0 );  //  a.hi + a.lo = sa + ca * M, max sa = M - 1

  auto sb = b.hi;
  C cb = sb.adc( b.lo, 0 );  //  b.hi + b.lo = sb + cb * M, max sb = M - 1

  C c = ca & cb;

  L ss = mul( sa, sb );  //  ( a.hi + a.lo ) * ( b.hi + b.lo ) = ss + ( ca * sb + cb * sa ) * M + c * M^2, max ss = M^2 - 2M + 1

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
  
  return Long<2*n>( hh, ll );
}


//  multiplication, results in doubled precision
template <>
const Math_NS::Long64 Math_NS::mul( const Long32& a, const Long32& b )
{
  const uint64_t c = static_cast<uint64_t>( a.u ) * static_cast<uint64_t>( b.u );
  return Long64( static_cast<uint32_t>( c >> 32 ), static_cast<uint32_t>( c ) );
}



