#pragma once


#include "Leaf.h"


namespace Quad_NS
{
  template <typename Core> class ConstEdge;


  template <typename Core>
  class Edge
  {
  public:

    using Vert = Core;
    using Face = typename Core::Dual;
    using Dual = Edge<Face>;

    Edge( const Edge& ) = default;
    Edge& operator = ( const Edge& ) = delete;

    Edge( Leaf<Core>& i_leaf ) : d_leaf( i_leaf ) {}

    Edge oNext() const { return d_leaf.oNext(); }
    Edge oPrev() const { return d_leaf.oPrev(); }

    Edge dNext() const { return d_leaf.dNext(); }
    Edge dPrev() const { return d_leaf.dPrev(); }

    Edge lNext() const { return d_leaf.lNext(); }
    Edge lPrev() const { return d_leaf.lPrev(); }

    Edge rNext() const { return d_leaf.rNext(); }
    Edge rPrev() const { return d_leaf.rPrev(); }

    Dual rot()   const { return d_leaf.rot(); }
    Edge sym()   const { return d_leaf.sym(); }

    const Vert& o() const { return d_leaf.o(); }
    Vert&       o()       { return d_leaf.o(); }

    const Vert& d() const { return d_leaf.d(); }
    Vert&       d()       { return d_leaf.d(); }

    const Face& l() const { return d_leaf.l(); }
    Face&       l()       { return d_leaf.l(); }

    const Face& r() const { return d_leaf.r(); }
    Face&       r()       { return d_leaf.r(); }

    friend void splice( Edge a, Edge b ) { splice( a.d_leaf, b.d_leaf ); }

  private:

    Leaf<Core>& d_leaf;

    friend class ConstEdge<Core>;
  };


  template <typename Core>
  class ConstEdge
  {
  public:

    using Vert = Core;
    using Face = typename Core::Dual;
    using ConstDual = ConstEdge<Face>;

    ConstEdge( const ConstEdge& ) = default;
    ConstEdge& operator = ( const ConstEdge& ) = delete;

    ConstEdge( const Leaf<Core>& i_leaf ) : d_leaf( i_leaf ) {}

    ConstEdge( Edge<Core> e ) : d_leaf( e.d_leaf ) {}

    ConstEdge oNext() const { return d_leaf.oNext(); }
    ConstEdge oPrev() const { return d_leaf.oPrev(); }

    ConstEdge dNext() const { return d_leaf.dNext(); }
    ConstEdge dPrev() const { return d_leaf.dPrev(); }

    ConstEdge lNext() const { return d_leaf.lNext(); }
    ConstEdge lPrev() const { return d_leaf.lPrev(); }

    ConstEdge rNext() const { return d_leaf.rNext(); }
    ConstEdge rPrev() const { return d_leaf.rPrev(); }

    ConstDual rot()   const { return d_leaf.rot(); }
    ConstEdge sym()   const { return d_leaf.sym(); }

    const Vert& o() const { return d_leaf.o(); }
    const Vert& d() const { return d_leaf.d(); }
    const Face& l() const { return d_leaf.l(); }
    const Face& r() const { return d_leaf.r(); }

  private:

    const Leaf<Core>& d_leaf;
  };
}