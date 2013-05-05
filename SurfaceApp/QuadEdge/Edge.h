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
  
  template <typename V, typename F>
  class ConstEdge;

  template <typename V, typename F>
  struct ConstEdgeTraits
  {
    typedef ConstEdge<V, F>   PrimEdge;
    typedef ConstEdge<F, V>   DualEdge;
    typedef const Ring<V, F>  PrimRing;
    typedef const Ring<F, V>  DualRing;
  };

  template <typename V, typename F>
  class ConstEdge : public RingRef<ConstEdgeTraits<V, F>>
  {
  public:
    
    ConstEdge( const Ring<V, F>& i_ring ) : RingRef( i_ring ) {}
  };

  /////////////////////////////////////////////////////////////////////////////

  template <typename V, typename F>
  class Edge;

  template <typename V, typename F>
  struct EdgeTraits
  {
    typedef Edge<V, F>  PrimEdge;
    typedef Edge<F, V>  DualEdge;
    typedef Ring<V, F>  PrimRing;
    typedef Ring<F, V>  DualRing;
  };

  template <typename V, typename F>
  class Edge : public RingRef<EdgeTraits<V, F>>
  {
  public:
    
    Edge( Ring<V, F>& i_ring ) : RingRef( i_ring ) {}

    operator ConstEdge<V, F> () const { return o(); }
  };

  /////////////////////////////////////////////////////////////////////////////

  template <typename V, typename F>
  void splice( Edge<V, F> a, Edge<V, F> b )
  {
    Ring<V, F>& pa = a.o();
    Ring<V, F>& pb = b.o();
    Ring<F, V>& da = pa.next().dual();
    Ring<F, V>& db = pb.next().dual();

    pa.fuse( pb );
    da.fuse( db );
  }
}