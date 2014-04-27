#pragma once


#include "Leaf.h"


namespace Quad_NS
{
  //  topology operation
  //  preserves a.o and a.l edge rings
  //  overrides b.o and b.l edge rings
  template <typename Core> void spliceAA( Leaf<Core>& a, Leaf<Core>& b )
  {
    b.oNext().rot().fuse( a.oNext().rot() );
    b.fuse( a );
  }


  //  topology operation
  //  preserves a.o and b.l edge rings
  //  overrides b.o and a.l edge rings
  template <typename Core> void spliceAB( Leaf<Core>& a, Leaf<Core>& b )
  {
    a.oNext().rot().fuse( b.oNext().rot() );
    b.fuse( a );
  }


  /// default splice operation
  template <typename Core> void splice( Leaf<Core>& a, Leaf<Core>& b ) { spliceAA( a, b ); }

}