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
    using Ring = Ring_NS::Ring<Core>;

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

    const Ring& ring() const { return d_ptr->ring(); }
    Ring&       ring()       { return d_ptr->ring(); }

    const Ring& operator -> ( ) const { return d_ptr->ring(); }
    Ring&       operator -> ( )       { return d_ptr->ring(); }

    friend void splice( Edge a, Edge b ) { Splice_NS::splice( *a.d_ptr, *b.d_ptr ); }

  private:

    Leaf_NS::Leaf<Core>* d_ptr;
  };

  
  /////////////////////////////////////////////////////////////////////////////
}