#pragma once

#include <algorithm>

namespace QuadEdge_NS
{
  class Ring
  {
    Ring* d_next;
    void* d_data;

    Ring();
    Ring( const Ring& );
    Ring& operator = ( const Ring& );

  public:

    explicit Ring( Ring* i_next ) : d_next( i_next ), d_data( nullptr ) {}

    Ring& next() { return *d_next; }
    Ring& rot() { return *( this + rotId() ); }

    void* data() { return d_data; }
    
    void swap( Ring& rhs ) { std::swap( d_next, rhs.d_next ); }
    void data( void* i_data ) { Ring* p = this; do { p->d_data = i_data; } while( ( p = p->d_next ) != this ); }

  private:

    ptrdiff_t id( const Ring* i_head = nullptr ) const { return this - i_head; }
    ptrdiff_t rotId() const { return pos( id() + 1 ) - pos( id() ); }

    static ptrdiff_t pos( ptrdiff_t i_id ) { return i_id & 3; }
  };

  inline void swap( Ring& a, Ring& b ) { a.swap( b ); }

  /////////////////////////////////////////////////////////////////////////////

  class Quad
  {
    Ring o, r, d, l;

    Quad( const Quad& );
    Quad& operator = ( const Quad& );
    
  public:

    Quad() : o( &o ), d( &d ), r( &l ), l( &r ) {}
  };

  /////////////////////////////////////////////////////////////////////////////

  inline void splice( Ring& a, Ring& b )
  {
    Ring& c = a.next().rot();
    Ring& d = b.next().rot();

    swap( a, b );
    b.data( a.data() == b.data() ? nullptr : a.data() );

    swap( c, d );
    d.data( c.data() == d.data() ? nullptr : c.data() );
  }
}