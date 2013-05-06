#pragma once

#include <algorithm>
#include <memory>

namespace QuadEdge_NS
{
  template <typename V, typename F>
  class Ring : private std::shared_ptr<V>
  {
    typedef std::shared_ptr<V> shared_ptr;

  public:

    typedef V                   Data;
    typedef Ring<F, V>          Dual;

    Ring( Ring& i_next, Dual& i_dual ) : d_next( &i_next ), d_dual( &i_dual ) {}

    //  iterate edges in the ring
    const Ring& next() const { return *d_next; }
    Ring&       next()       { return *d_next; }
    
    //  get counter-part of edge as next ring in the parent quad-edge structure
    const Dual& dual() const { return *d_dual; }
    Dual&       dual()       { return *d_dual; }

    //  access ring user data for read/write purposes
    using shared_ptr::operator ->;
    using shared_ptr::operator *;

    template <typename V, typename F> friend void splice( Ring<V, F>& a, Ring<V, F>& b );
    template <typename V, typename F> friend class Quad;

  private:

    Ring();
    Ring( const Ring& );
    Ring& operator = ( const Ring& );
    Ring& operator = ( shared_ptr i_data ) { shared_ptr::operator = ( i_data ); return *this; }

  private:

    //  merge/tear the edge ring [i_ring] to/from [this] edge ring
    void swap( Ring& i_ring ) { std::swap( d_next, i_ring.d_next ); }

    //  merge/tear the ring data [i_ring] to/from [this] ring data
    void fuse( Ring& i_ring ) { i_ring.data( i_ring == *this ? clone() : *this ); }

    //  set new data to the ring
    void data( shared_ptr i_data ) { Ring* p = this; do { *p = i_data; } while( ( p = p->d_next ) != this ); }
    
    //  create new data instance for decoupled ring
    shared_ptr clone() const { return shared_ptr( new V ); }

  private:

    Ring* d_next;
    Dual* d_dual;
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

    Quad()
      : d_oVert( d_oVert, d_rFace )
      , d_rFace( d_lFace, d_dVert )
      , d_dVert( d_dVert, d_lFace )
      , d_lFace( d_rFace, d_oVert )
    {
      o().data( Prim::shared_ptr( new V ) );
      d().data( Prim::shared_ptr( new V ) );
      r().data( Dual::shared_ptr( new F ) );  //  l = r
    }
    
  public:

    typedef Ring<V, F>  Prim;
    typedef Ring<F, V>  Dual;

    static std::shared_ptr<Quad> create() { return std::shared_ptr<Quad>( new Quad ); }

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