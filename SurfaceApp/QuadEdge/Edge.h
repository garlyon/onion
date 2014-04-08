#pragma once


#include "Leaf.h"
#include "Ring.h"
#include "Splice.h"


namespace Edge_NS
{
  template <typename Core>
  class Edge
  {
  public:

    using Dual = Edge<typename Core::Dual>;
    using Vert = Ring_NS::Ring<Core>;
    using Face = Ring_NS::Ring<typename Core::Dual>;

    Edge() : d_ptr( nullptr ) {}
    Edge( Leaf_NS::Leaf<Core>& ref ) : d_ptr( &ref ) {}

    Edge oNext() const { return d_ptr->next(); }
    Edge oPrev() const { return d_ptr->dual().next().dual(); }

    Edge dNext() const { return d_ptr->dual().dual().next().dual().dual(); }
    Edge dPrev() const { return d_ptr->dual().dual().dual().next().dual().dual().dual(); }

    Edge lNext() const { return d_ptr->dual().dual().dual().next().dual(); }
    Edge lPrev() const { return d_ptr->next().dual().dual(); }

    Edge rNext() const { return d_ptr->dual().next().dual().dual().dual(); }
    Edge rPrev() const { return d_ptr->dual().dual().next(); }

    Dual rot()   const { return d_ptr->dual(); }
    Edge sym()   const { return d_ptr->dual().dual(); }

    const Vert& o() const { return d_ptr->ring(); }
    Vert&       o()       { return d_ptr->ring(); }

    const Vert& d() const { return sym().o(); }
    Vert&       d()       { return sym().o(); }

    const Face& l() const { return sym().rot().o(); }
    Face&       l()       { return sym().rot().o(); }

    const Face& r() const { return rot().o(); }
    Face&       r()       { return rot().o(); }

    friend void splice( Edge a, Edge b ) { Splice_NS::splice( *a.d_ptr, *b.d_ptr ); }

  private:

    Leaf_NS::Leaf<Core>* d_ptr;
  };
}