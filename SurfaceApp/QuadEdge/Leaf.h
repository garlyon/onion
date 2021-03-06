#pragma once


#include <memory>


//
//  class Leaf
//  {
//    Core* core  //  all leafs in a list refer to the same core
//    Leaf* next
//    Leaf* dual
//  }
//


namespace Quad_NS
{
  template <typename Core>
  class Leaf : public Core::Edge
  {
  public:

    //
    //  neighbor edges
    //

    using Dual = Leaf<typename Core::Dual>;

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

    //
    //  conjugated edges
    //

    const Dual& rot() const { return dual(); }
    Dual&       rot()       { return dual(); }

    const Leaf& sym() const { return dual().dual(); }
    Leaf&       sym()       { return dual().dual(); }

    const Dual& inv() const { return dual().dual().dual(); }
    Dual&       inv()       { return dual().dual().dual(); }

    //
    //  node data
    //

    using Vert = Core;
    using Face = typename Core::Dual;

    const Vert& o() const { return core(); }
    Vert&       o()       { return core(); }

    const Face& r() const { return dual().core(); }
    Face&       r()       { return dual().core(); }

    const Vert& d() const { return dual().dual().core(); }
    Vert&       d()       { return dual().dual().core(); }

    const Face& l() const { return dual().dual().dual().core(); }
    Face&       l()       { return dual().dual().dual().core(); }

    //
    //  topology helper function, a half-splice
    //  changes own O edge ring, do not touch other' O ring
    //

    void fuse( Leaf& );

    //  the only constructor, used by Quad
    Leaf( Dual& i_dual ) : d_next( this ), d_dual( i_dual ), d_core( std::make_shared<Core>() ) {}

  private:

    //  basic topology accessors

    const Leaf& next() const { return *d_next; }
    Leaf&       next()       { return *d_next; }

    const Dual& dual() const { return d_dual; }
    Dual&       dual()       { return d_dual; }

    const Core& core() const { return *d_core; }
    Core&       core()       { return *d_core; }

    using Ptr = std::shared_ptr<Core>;

    void core( Ptr i_core ) { Leaf* f = this; do { f->d_core = i_core; } while( ( f = f->d_next ) != this ); }

    friend class Dual;

  private:

    Leaf*   d_next;
    Dual&   d_dual;
    Ptr     d_core;

    Leaf() = delete;
    Leaf( const Leaf& ) = delete;
    Leaf( Leaf&& ) = delete;
    Leaf& operator = ( const Leaf& ) = delete;
    Leaf& operator = ( Leaf&& ) = delete;
  };


  /////////////////////////////////////////////////////////////////////////////


  template <typename Core>
  void Leaf<Core>::fuse( Leaf& o )
  {
    if( d_core == o.d_core )
    {
      //  detach this leaf from other leaf
      std::swap( d_next, o.d_next );
      core( std::make_shared<Core>() );
    }
    else
    {
      //  attach this leaf to other leaf
      core( o.d_core );
      std::swap( d_next, o.d_next );
    }
  }
}