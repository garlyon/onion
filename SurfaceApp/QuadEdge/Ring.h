#pragma once

#include <algorithm>
#include <memory>
#include <unordered_set>

namespace QuadEdge_NS
{
  template <typename T> class Core;

  template <typename T, size_t id>
  class Reg : private std::unordered_set<Core<T>*>
  {
    typedef std::unordered_set<Core<T>*> set;

    Reg(){}

    Reg( const Reg& );
    Reg& operator = ( const Reg& );

  public:

    static Reg& get() { static Reg s_this; return s_this; }

    using set::begin;
    using set::end;
    using set::find;
    using set::size;
    using set::empty;

    void reg  ( Core<T>* i_core ) { insert( i_core ); }
    void unreg( Core<T>* i_core ) { erase ( i_core ); }
  };

  /////////////////////////////////////////////////////////////////////////////

  template <typename T> class Ring;

  template <typename T>
  class Core : public T
  {
    Core();
    Core( const Core& );
    Core& operator = ( const Core& );

  public:

    Core( Ring<T>& i_ring ) : d_ring( i_ring ) { T::Reg::get().reg( this ); }
    ~Core()                                    { T::Reg::get().unreg( this ); }

    const T* operator -> () const { return this; }
    T*       operator -> ()       { return this; }

    const Ring<T>& ring() const { return d_ring; }
    Ring<T>&       ring()       { return d_ring; }

  private:

    Ring<T>& d_ring;
  };

  /////////////////////////////////////////////////////////////////////////////

  template <typename T>
  class Ring
  {
  public:

    typedef Core<T>                      Data;
    typedef Ring<typename T::Dual>       Dual;

    Ring( Ring& i_next, Dual& i_dual ) : d_next( &i_next ), d_dual( &i_dual ) {}

    //  iterate edges in the ring
    const Ring& next() const { return *d_next; }
    Ring&       next()       { return *d_next; }
    
    //  get counter-part of edge as next ring in the parent quad-edge structure
    const Dual& dual() const { return *d_dual; }
    Dual&       dual()       { return *d_dual; }

    //  access ring user data for read/write purposes
    const Data& operator -> () const { return *d_data; }
    Data&       operator -> ()       { return *d_data; }

    bool operator == ( const Ring& i_ring ) const { return d_data == i_ring.d_data; }

    template <typename T> friend void splice( Ring<T>& a, Ring<T>& b );
    template <typename T> friend class Quad;

  private:

    Ring();
    Ring( const Ring& );
    Ring& operator = ( const Ring& );

  private:

    typedef std::shared_ptr<Data> shared_ptr;

    //  merge/tear the edge ring [i_ring] to/from [this] edge ring
    void swap( Ring& i_ring ) { std::swap( d_next, i_ring.d_next ); }

    //  merge/tear the ring data [i_ring] to/from [this] ring data
    void fuse( Ring& i_ring ) { i_ring.data( i_ring == *this ? i_ring.create() : d_data ); }

    //  set new data to the ring
    void data( shared_ptr i_data ) { Ring* p = this; do { p->d_data = i_data; } while( ( p = p->d_next ) != this ); }
    
    //  create new data instance for decoupled ring
    shared_ptr create() { return shared_ptr( new Data( *this ) ); }

  private:

    Ring*       d_next;
    Dual*       d_dual;
    shared_ptr  d_data;
  };

  /////////////////////////////////////////////////////////////////////////////

  template <typename T>
  void splice( Ring<T>& a, Ring<T>& b )
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

  template <typename T>
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
      o().data( o().create() );
      d().data( d().create() );
      r().data( r().create() );  //  l = r
    }
    
  public:

    typedef Ring<T>                     Prim;
    typedef typename Ring<T>::Dual      Dual;

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