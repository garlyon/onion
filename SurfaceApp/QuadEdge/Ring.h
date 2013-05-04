#pragma once

#include <algorithm>

#ifdef _DEBUG
#define MEMORY_CHECKS
#endif

namespace QuadEdge_NS
{
  template <typename V, typename F>
  class Ring
  {
  public:

    typedef Ring<F, V> Dual;
    typedef V          Data;

    Ring( Ring& i_next, Dual& i_dual ) : d_next( &i_next ), d_dual( i_dual ), d_data( nullptr ) {}

    const Ring& next() const { return *d_next; }
    Ring&       next()       { return *d_next; }
    
    const Dual& dual() const { return d_dual; }
    Dual&       dual()       { return d_dual; }

    const Data* data() const { return d_data; }
    Data*       data()       { return d_data; }
    
    void swap( Ring& i_ring ) { std::swap( d_next, i_ring.d_next ); }    
    void data( Data* i_data ) { Ring* p = this; do { p->d_data = i_data; } while( ( p = p->d_next ) != this ); }

    bool operator == ( const Ring& i_ring ) const { return d_data == i_ring.d_data; }
    bool operator != ( const Ring& i_ring ) const { return d_data != i_ring.d_data; }
  
  private:

    Ring();
    Ring( const Ring& );
    Ring& operator = ( const Ring& );

    Ring* d_next;
    Dual& d_dual;
    Data* d_data;
  };

  template <typename V, typename F>
  void swap( Ring<V, F>& a, Ring<V, F>& b ) { a.swap( b ); }

  /////////////////////////////////////////////////////////////////////////////

  template <typename V, typename F>
  class Quad
  {
    Ring<V, F> d_oVert;
    Ring<F, V> d_rFace;
    Ring<V, F> d_dVert;
    Ring<F, V> d_lFace;

    Quad( const Quad& );
    Quad& operator = ( const Quad& );
    
  public:

    Quad() : d_oVert( d_oVert, d_rFace ), d_rFace( d_lFace, d_dVert ), d_dVert( d_dVert, d_lFace ), d_lFace( d_rFace, d_oVert ) {}

    const Ring<V, F>& o() const { return d_oVert; }
    Ring<V, F>&       o()       { return d_oVert; }

    const Ring<F, V>& r() const { return d_rFace; }
    Ring<F, V>&       r()       { return d_rFace; }

    const Ring<V, F>& d() const { return d_dVert; }
    Ring<V, F>&       d()       { return d_dVert; }

    const Ring<F, V>& l() const { return d_lFace; }
    Ring<F, V>&       l()       { return d_lFace; }
  };

  /////////////////////////////////////////////////////////////////////////////

  template <typename V, typename F>
  void weld( Ring<V, F>& a, Ring<V, F>& b )
  {
    //  option 1: attach b ring to a ring; b ring should be empty
    //  option 2: detach b ring from a ring; b ring becomes empty
#ifdef MEMORY_CHECKS
    if( a != b && b.data() != nullptr ) throw std::make_pair( &a, &b );
#endif

    swap( a, b );
    b.data( a.data() == b.data() ? nullptr : a.data() );
  }

  template <typename V, typename F>
  void splice( Ring<V, F>& a, Ring<V, F>& b )
  {
    weld( a.next().dual(), b.next().dual() );
    weld( a, b );
  }
}