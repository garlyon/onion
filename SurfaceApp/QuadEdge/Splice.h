#pragma once


#include "Leaf.h"


namespace Quad_NS
{
  //  topology operation
  //  preserves a.o and a.l edge rings
  //  overrides b.o and b.l edge rings
  template <typename Core> void spliceAA( Leaf<Core>& a, Leaf<Core>& b )
  {
    //  preserves a.l, overrides b.l
    b.oNext().rot().fuse( a.oNext().rot() );
    //  preserves a.o, overrides b.o
    b.fuse( a );
  }


  //  topology operation
  //  preserves a.o and b.l edge rings
  //  overrides b.o and a.l edge rings
  template <typename Core> void spliceAB( Leaf<Core>& a, Leaf<Core>& b )
  {
    //  preserves b.l, overrides a.l
    a.oNext().rot().fuse( b.oNext().rot() );
    //  preserves a.o, overrides b.o
    b.fuse( a );
  }


  //  topology operation
  //  preserves b.o and a.l edge rings
  //  overrides a.o and b.l edge rings
  template <typename Core> void spliceBA( Leaf<Core>& a, Leaf<Core>& b )
  {
    //  preserves a.l, overrides b.l
    b.oNext().rot().fuse( a.oNext().rot() );
    //  preserves b.o, overrides a.o
    a.fuse( b );
  }


  //  topology operation
  //  preserves b.o and b.l edge rings
  //  overrides a.o and a.l edge rings
  template <typename Core> void spliceBB( Leaf<Core>& a, Leaf<Core>& b )
  {
    //  preserves b.l, overrides a.l
    a.oNext().rot().fuse( b.oNext().rot() );
    //  preserves b.o, overrides a.o
    a.fuse( b );
  }


  // default version of splice operation
  template <typename Core> void splice( Leaf<Core>& a, Leaf<Core>& b ) { spliceAA( a, b ); }

}