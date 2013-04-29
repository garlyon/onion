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

  enum RingType { O, R, D, L };

  template <RingType T> class Ring;

  template <RingType T> struct DualRingType;
  template <> struct DualRingType<O> { typedef Ring<R> Dual; };
  template <> struct DualRingType<R> { typedef Ring<D> Dual; };
  template <> struct DualRingType<D> { typedef Ring<L> Dual; };
  template <> struct DualRingType<L> { typedef Ring<O> Dual; };

  class Quad;

  template <RingType T, typename Data>
  class Ring : public Link
  {
    Data* d_data; //  how to update the splitted part of the ring ater the splice in one step ?

  public:

    typedef typename DualRingType<T>::Dual Dual;

    Ring& next() { return static_cast< Ring& >( Link::next() ); }

    Dual& rot()  { return quad(); }

    Quad& quad();

    template <RingType D>
    void swap( Ring<D, Data>& rhs ) { std::swap(  ) }
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

  template <RingType T>
  inline Quad& Ring<T>::quad() { return static_cast<Quad&>( *this ); }

  /////////////////////////////////////////////////////////////////////////////

  template <RingType A, RingType B>
  void splice( Ring<A>& a, Ring<B>& b )
  {
    swap( a.next().rot(), b.next().rot() );
    swap( a, b );
  }
}