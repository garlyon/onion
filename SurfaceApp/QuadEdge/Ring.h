#pragma once

#include <algorithm>
#include <memory>

namespace QuadEdge_NS
{
  template <typename V, typename F>
  class Ring
  {
  public:

    typedef Ring<F, V>          Dual;
    typedef std::shared_ptr<V>  Data;

    Ring( Ring& i_next, Dual& i_dual, Data i_data ) : d_next( &i_next ), d_dual( &i_dual ), d_data( i_data ) {}

    //  iterate edges in the ring
    const Ring& next() const { return *d_next; }
    Ring&       next()       { return *d_next; }
    
    //  get counter-part of edge as next ring in the parent quad-edge structure
    const Dual& dual() const { return *d_dual; }
    Dual&       dual()       { return *d_dual; }

    //  access ring user data for read/write purposes
    const Data  operator -> () const { return d_data; }
    Data        operator -> ()       { return d_data; }

    bool operator == ( const Ring& i_ring ) const { return d_data == i_ring.d_data; }

    template <typename V, typename F> friend void splice( Ring<V, F>& a, Ring<V, F>& b );

  private:

    Ring();
    Ring( const Ring& );
    Ring& operator = ( const Ring& );

  private:

    //  merge/tear the edge ring [i_ring] to/from [this] edge ring
    void swap( Ring& i_ring ) { std::swap( d_next, i_ring.d_next ); }

    //  merge/tear the ring data [i_ring] to/from [this] ring data
    void fuse( Ring& i_ring ) { i_ring.data( i_ring.d_data == d_data ? clone() : d_data ); }

    //  set new data to the ring
    void data( Data i_data ) { Ring* p = this; do { p->d_data = i_data; } while( ( p = p->d_next ) != this ); }
    
    //Data clone() const { return Data( new V( *d_data ) ); }
    Data clone() const { return Data( new V ); }

  private:

    Ring* d_next;
    Dual* d_dual;
    Data  d_data;
  };

  /////////////////////////////////////////////////////////////////////////////

  template <typename V, typename F>
  void splice( Ring<V, F>& a, Ring<V, F>& b )
  {
    //  swap links in L edges ring
    a.next().dual().swap( b.next().dual() );
    //  fuse L ring data
    a.dual().dual().dual().fuse( b.dual().dual().dual() );
    //  swap links in O edges ring
    a.swap( b );
    //  fuse O ring data
    a.fuse( b );
  }

  /////////////////////////////////////////////////////////////////////////////

  template <typename V, typename F>
  class Quad
  {
    Quad( const Quad& );
    Quad& operator = ( const Quad& );
    
  public:

    typedef Ring<V, F>  Prim;
    typedef Ring<F, V>  Dual;

    Quad()
      : d_oVert( d_oVert, d_rFace, Prim::Data( new V ) )
      , d_rFace( d_lFace, d_dVert, Dual::Data( new F ) )
      , d_dVert( d_dVert, d_lFace, Prim::Data( new V ) )
      , d_lFace( d_rFace, d_oVert, d_rFace.operator->() )
    {}

    const Prim& o() const { return d_oVert; }
    Prim&       o()       { return d_oVert; }

    const Dual& r() const { return d_rFace; }
    Dual&       r()       { return d_rFace; }

    const Prim& d() const { return d_dVert; }
    Prim&       d()       { return d_dVert; }

    const Dual& l() const { return d_lFace; }
    Dual&       l()       { return d_lFace; }

  private:

    Prim d_oVert;
    Dual d_rFace;
    Prim d_dVert;
    Dual d_lFace;
  };
}