#pragma once

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

    typedef Ring<N> Next;

    explicit Ring( Ring* i_next ) : d_next( i_next ) {}

    Ring& next() { return *d_next; }
    Next& rot()  { return *reinterpret_cast<Next*>( this + R ); }
  };

  typedef Ring<O> ORing;
  typedef Ring<R> RRing;
  typedef Ring<D> DRing;
  typedef Ring<L> LRing;
}