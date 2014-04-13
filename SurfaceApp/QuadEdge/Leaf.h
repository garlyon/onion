#pragma once


//
//  class Leaf
//  {
//    Core* core  //  all lifs in a list refer to the same core
//    Leaf* next
//    Leaf* dual
//  }
//


#include <memory>


namespace Quad_NS
{
  template <typename Core>
  class Leaf
  {
  public:

    using Dual = Leaf<typename Core::Dual>;

    Leaf( Dual& i_dual ) : d_next( this ), d_dual( i_dual ), d_core( std::make_shared<Core>() ) {}

    //  topology accessors

    const Leaf& next() const { return *d_next; }
    Leaf&       next()       { return *d_next; }

    const Dual& dual() const { return d_dual; }
    Dual&       dual()       { return d_dual; }

    const Core& core() const { return *d_core; }
    Core&       core()       { return *d_core; }

    //  exchange links
    void swap( Leaf& o ) { std::swap( d_next, o.d_next ); }

    //  take other's leaf core
    void reset( Leaf& o ) { core( o.d_core ); }

    //  take unique core
    void reset() { core( std::make_shared<Core>() ); }

    //  half of edge splice operation, changes own core
    void fuse( Leaf& o )
    {
      if( d_core == o.d_core )
      {
        //  detach this leaf from other leaf
        swap( o );
        reset();
      }
      else
      {
        //  attach this leaf to other leaf
        reset( o );
        swap( o );
      }
    }

  private:

    using Ptr = std::shared_ptr<Core>;

    void core( Ptr i_core ) { Leaf* f = this; do { f->d_core = i_core; } while( ( f = f->d_next ) != this ); }

  private:

    Leaf*   d_next;
    Dual&   d_dual;
    Ptr     d_core;

  public:

    //  derived navigation

    const Leaf& oNext() const { return next(); }
    Leaf&       oNext()       { return next(); }
    
    const Leaf& oPrev() const { return dual().next().dual(); }
    Leaf&       oPrev()       { return dual().next().dual(); }

    const Leaf& dNext() const { return dual().dual().next().dual().dual(); }
    Leaf&       dNext()       { return dual().dual().next().dual().dual(); }

    const Leaf& dPrev() const { return dual().dual().dual().next().dual().dual().dual(); }
    Leaf&       dPrev()       { return dual().dual().dual().next().dual().dual().dual(); }

    const Leaf& lNext() const { return dual().dual().dual().next().dual(); }
    Leaf&       lNext()       { return dual().dual().dual().next().dual(); }

    const Leaf& lPrev() const { return next().dual().dual(); }
    Leaf&       lPrev()       { return next().dual().dual(); }

    const Leaf& rNext() const { return dual().next().dual().dual().dual(); }
    Leaf&       rNext()       { return dual().next().dual().dual().dual(); }
    
    const Leaf& rPrev() const { return dual().dual().next(); }
    Leaf&       rPrev()       { return dual().dual().next(); }

    const Dual& rot() const { return dual(); }
    Dual&       rot()       { return dual(); }
    
    const Leaf& sym() const { return dual().dual(); }
    Leaf&       sym()       { return dual().dual(); }

    using Vert = Core;
    using Face = typename Core::Dual;

    const Vert& o() const { return core(); }
    Vert&       o()       { return core(); }

    const Face& r() const { return rot().core(); }
    Face&       r()       { return rot().core(); }

    const Vert& d() const { return rot().rot().core(); }
    Vert&       d()       { return rot().rot().core(); }

    const Face& l() const { return rot().rot().rot().core(); }
    Face&       l()       { return rot().rot().rot().core(); }

  private:

    Leaf() = delete;
    Leaf( const Leaf& ) = delete;
    Leaf( Leaf&& ) = delete;
    Leaf& operator = ( const Leaf& ) = delete;
    Leaf& operator = ( Leaf&& ) = delete;
  };


  template <typename Core>
  void splice( Leaf<Core>& a, Leaf<Core>& b )
  {
    b.next().dual().fuse( a.next().dual() );  //  doesn't change *.next() value
    b.fuse( a );                              //  do changes *.next() value
  }
}