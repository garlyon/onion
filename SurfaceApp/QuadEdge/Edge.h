#pragma once


#include "Leaf.h"
#include "Splice.h"


namespace Edge_NS
{
  template <typename Core>
  class Edge
  {
  public:

    using Vert = Core;
    using Face = typename Core::Dual;
    using Dual = Edge<Face>;

    Edge( const Edge& ) = default;
    Edge& operator = ( const Edge& ) = delete;

    Edge( Leaf_NS::Leaf<Core>& ref ) : d_leaf( ref ) {}

    Edge oNext() const { return d_leaf.next(); }
    Edge oPrev() const { return d_leaf.dual().next().dual(); }

    Edge dNext() const { return d_leaf.dual().dual().next().dual().dual(); }
    Edge dPrev() const { return d_leaf.dual().dual().dual().next().dual().dual().dual(); }

    Edge lNext() const { return d_leaf.dual().dual().dual().next().dual(); }
    Edge lPrev() const { return d_leaf.next().dual().dual(); }

    Edge rNext() const { return d_leaf.dual().next().dual().dual().dual(); }
    Edge rPrev() const { return d_leaf.dual().dual().next(); }

    Dual rot()   const { return d_leaf.dual(); }
    Edge sym()   const { return d_leaf.dual().dual(); }

    const Vert& o() const { return d_leaf.core(); }
    Vert&       o()       { return d_leaf.core(); }

    const Vert& d() const { return sym().o(); }
    Vert&       d()       { return sym().o(); }

    const Face& l() const { return sym().rot().o(); }
    Face&       l()       { return sym().rot().o(); }

    const Face& r() const { return rot().o(); }
    Face&       r()       { return rot().o(); }

    friend void splice( Edge a, Edge b ) { Splice_NS::splice( a.d_leaf, b.d_leaf ); }

  private:

    Leaf_NS::Leaf<Core>& d_leaf;
  };
}