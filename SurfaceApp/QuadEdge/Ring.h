#pragma once

#include <algorithm>
#include <memory>

namespace QuadEdge_NS
{
  class Link
  {
    Link* d_next;

  protected:

    Link() : d_next( this ) {}

  private:

    Link( const Link& );
    Link& operator = ( const Link& );

  public:

    Link& next() { return *d_next; }

    void swap( Link& rhs ) { std::swap( d_next, rhs.d_next ); }
  };

  inline void swap( Link& a, Link& b ) { a.swap( b ); }

  /////////////////////////////////////////////////////////////////////////////

  class Quad;

  enum LinkType
  {
    O = 0,
    R = 1,
    D = 2,
    L = 3
  };

  template <int T>
  class Ring : public Link
  {
    static const int N = ( T + 1 ) % 4;

  public:

    typedef Ring<N> Dual;

    Ring& next() { return static_cast< Ring& >( Link::next() ); }

    Dual& rot()  { return quad(); }

    Quad& quad();
  };

  typedef Ring<O> ORing;
  typedef Ring<R> RRing;
  typedef Ring<D> DRing;
  typedef Ring<L> LRing;

  /////////////////////////////////////////////////////////////////////////////

  class Quad : public ORing, public RRing, public DRing, public LRing
  {
  protected:

    Quad() { using QuadEdge_NS::swap; swap( l(), r() ); }

  private:
    
    Quad( const Quad& );
    Quad& operator = ( const Quad& );

  public:

    static std::shared_ptr<Quad> create() { return std::shared_ptr<Quad>( new Quad ); }

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
  inline Quad& Ring<T>::quad() { return static_cast<Quad&>( *this ); }

  /////////////////////////////////////////////////////////////////////////////

  template <int A, int B>
  void splice( Ring<A>& a, Ring<B>& b )
  {
    swap( a.next().rot(), b.next().rot() );
    swap( a, b );
  }
}