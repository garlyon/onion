#pragma once


namespace Splice_NS
{
  template <typename Core>
  void splice( Leaf_NS::Leaf<Core>& a, Leaf_NS::Leaf<Core>& b )
  {
    b.next().dual().fuse( a.next().dual() );  //  doesn't change *.next() value
    b.fuse( a );                              //  do changes *.next() value
  }
}