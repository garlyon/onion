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
    
    //  merge/tear the [i_ring] to/from [this]
    //  [this] ring data does not change
    void fuse( Ring& i_ring )
    {
      std::swap( d_next, i_ring.d_next );
      i_ring.data( i_ring.d_data == d_data ? Data( new V ) : d_data );
    }

  private:

    Ring();
    Ring( const Ring& );
    Ring& operator = ( const Ring& );

  private:

    void data( Data i_data ) { Ring* p = this; do { p->d_data = i_data; } while( ( p = p->d_next ) != this ); }

  private:

    Ring* d_next;
    Dual* d_dual;
    Data  d_data;
  };

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