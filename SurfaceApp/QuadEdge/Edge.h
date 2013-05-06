#pragma once

#include "Ring.h"

namespace QuadEdge_NS
{
  template <typename T>
  class RingRef
  {
  public:

    typedef typename T::PrimEdge    PrimEdge;
    typedef typename T::DualEdge    DualEdge;
    typedef typename T::PrimRing    PrimRing;
    typedef typename T::DualRing    DualRing;

    RingRef( PrimRing& i_ring ) : d_ring( i_ring ) {}

    PrimEdge oNext() const { return d_ring.next(); }
    PrimEdge oPrev() const { return d_ring.dual().next().dual(); }

    PrimEdge dNext() const { return d_ring.dual().dual().next().dual().dual(); }
    PrimEdge dPrev() const { return d_ring.dual().dual().dual().next().dual().dual().dual(); }

    PrimEdge lNext() const { return d_ring.dual().dual().dual().next().dual(); }
    PrimEdge lPrev() const { return d_ring.next().dual().dual(); }

    PrimEdge rNext() const { return d_ring.dual().next().dual().dual().dual(); }
    PrimEdge rPrev() const { return d_ring.dual().dual().next(); }

    DualEdge rot()   const { return d_ring.dual(); }
    PrimEdge sym()   const { return d_ring.dual().dual(); }

    const PrimRing& o() const { return d_ring; }
    const DualRing& r() const { return d_ring.dual(); }
    const PrimRing& d() const { return d_ring.dual().dual(); }
    const DualRing& l() const { return d_ring.dual().dual().dual(); }
    
    PrimRing& o() { return d_ring; }
    DualRing& r() { return d_ring.dual(); }
    PrimRing& d() { return d_ring.dual().dual(); }
    DualRing& l() { return d_ring.dual().dual().dual(); }

  private:

    RingRef();
    RingRef& operator = ( const RingRef& );

  private:

    PrimRing& d_ring;
  };

  /////////////////////////////////////////////////////////////////////////////
  
  template <typename T>
  class ConstEdge;

  template <typename T>
  struct ConstEdgeTraits
  {
    typedef typename T::Prim      Prim;
    typedef typename T::Dual      Dual;
    typedef ConstEdge<Prim>       PrimEdge;
    typedef ConstEdge<Dual>       DualEdge;
    typedef const Ring<Prim>      PrimRing;
    typedef const Ring<Dual>      DualRing;
  };

  template <typename T>
  class ConstEdge : public RingRef<ConstEdgeTraits<T>>
  {
  public:
    
    ConstEdge( const Ring<T>& i_ring ) : RingRef( i_ring ) {}
  };

  /////////////////////////////////////////////////////////////////////////////

  template <typename T>
  class Edge;

  template <typename T>
  struct EdgeTraits
  {
    typedef typename T::Prim      Prim;
    typedef typename T::Dual      Dual;
    typedef Edge<Prim>            PrimEdge;
    typedef Edge<Dual>            DualEdge;
    typedef Ring<Prim>            PrimRing;
    typedef Ring<Dual>            DualRing;
  };

  template <typename T>
  class Edge : public RingRef<EdgeTraits<T>>
  {
  public:
    
    Edge( Ring<T>& i_ring ) : RingRef( i_ring ) {}

    operator ConstEdge<T> () const { return o(); }
  };

  /////////////////////////////////////////////////////////////////////////////

  template <typename T>
  void splice( Edge<T> a, Edge<T> b )
  {
    splice( a.o(), b.o() );
  }
}