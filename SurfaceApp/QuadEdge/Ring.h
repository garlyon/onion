#pragma once

#include <algorithm>

namespace QuadEdge_NS
{
  enum RingType
  {
    O = 0,
    R = 1,
    D = 2,
    L = 3
  };

  template <int T>
  class Ring
  {
    Ring* d_next;

    static const int N = ( T + 1 ) % 4;
    static const int R = N - T;

  public:

    Ring() : d_next( this )             {}

    typedef     Ring<N>                 Next;

    const Ring& next()            const { return *d_next; }
    const Next& rot()             const { return *reinterpret_cast<const Next*>( this + R ); }

    Ring&       next()                  { return *d_next; }
    Next&       rot()                   { return *reinterpret_cast<Next*>( this + R ); }

    //  swap the links on next element in a ring
    void        swap( Ring& rhs )       { std::swap( d_next, rhs.d_next ); }
  };

  typedef Ring<O> ORing;
  typedef Ring<R> RRing;
  typedef Ring<D> DRing;
  typedef Ring<L> LRing;
}