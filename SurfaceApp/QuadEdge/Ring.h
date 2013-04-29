#pragma once

#include <algorithm>

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

  enum RingType { O, R, D, L };

  template <RingType T> class Ring;

  template <RingType T> struct DualRingType;
  template <> struct DualRingType<O> { typedef Ring<R> Dual; };
  template <> struct DualRingType<R> { typedef Ring<D> Dual; };
  template <> struct DualRingType<D> { typedef Ring<L> Dual; };
  template <> struct DualRingType<L> { typedef Ring<O> Dual; };

  template <RingType T>
  class Ring : public Link
  {
  public:

    typedef typename DualRingType<T>::Dual Dual;

    Ring& next() { return static_cast< Ring& >( Link::next() ); }
    Dual& rot();
  };

  typedef Ring<O> ORing;
  typedef Ring<R> RRing;
  typedef Ring<D> DRing;
  typedef Ring<L> LRing;

  /////////////////////////////////////////////////////////////////////////////

  class Quad : private ORing, private RRing, private DRing, private LRing
  {
  protected:

    Quad() { QuadEdge_NS::swap( (LRing&)*this, (RRing&)*this ); }

  public:

    static Quad* create() { return new Quad; }

    ORing& edge() { return *this; }

  public:

    template<RingType T>
    static typename Ring<T>::Dual& rot( Ring<T>& ring ) { return static_cast<Quad&>( ring ); }
  };

  /////////////////////////////////////////////////////////////////////////////

  template <RingType T> inline typename Ring<T>::Dual& Ring<T>::rot() { return Quad::rot( *this ); }

  /////////////////////////////////////////////////////////////////////////////

  template <RingType T>
  void splice( Ring<T>& a, Ring<T>& b )
  {
    swap( a.next().rot(), b.next().rot() );
    swap( a, b );
  }

  template <RingType T>
  void splice( Ring<T>& a, typename Ring<T>::Dual::Dual& b )
  {
    swap( a.next().rot(), b.next().rot() );
    swap( a, b );
  }
}