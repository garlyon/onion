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

  protected:

    Ring() : d_next( this )             {}

  private:
    
    Ring( const Ring& );
    Ring& operator = ( const Ring& );

  public:

    typedef     Ring<N>                 Next;

    const Ring& next()            const { return *d_next; }
    const Next& rot()             const;

    Ring&       next()                  { return *d_next; }
    Next&       rot();

    //  swap the links on next element in a ring
    void        swap( Ring& rhs )       { std::swap( d_next, rhs.d_next ); }
  };

  typedef Ring<O> ORing;
  typedef Ring<R> RRing;
  typedef Ring<D> DRing;
  typedef Ring<L> LRing;

  /////////////////////////////////////////////////////////////////////////////

  class Quad : public ORing, public RRing, public DRing, public LRing
  {
  public:

    Quad() { l().swap( r().rot().rot() ); }

  public:

    const ORing& o() const { return *this; }
    const RRing& r() const { return *this; }
    const DRing& d() const { return *this; }
    const LRing& l() const { return *this; }

    ORing& o() { return *this; }
    RRing& r() { return *this; }
    DRing& d() { return *this; }
    LRing& l() { return *this; }
  };

  /////////////////////////////////////////////////////////////////////////////

  template <int T>
  inline typename const Ring<T>::Next& Ring<T>::rot() const { return static_cast<const Quad&>( *this ); }

  template <int T>
  inline typename       Ring<T>::Next& Ring<T>::rot()       { return static_cast<Quad&>( *this ); }

  /////////////////////////////////////////////////////////////////////////////

  template <int T>
  void splice( Ring<T>& a, Ring<T>& b )
  {
    a.next().rot().swap( b.next().rot() );
    a.swap( b );
  }
}