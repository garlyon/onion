#pragma once

#include "Ring.h"

namespace QuadEdge_NS
{
  template <typename T>
  class RingRef
  {
  public:

    typedef typename T::E   E;  //  Edge
    typedef typename T::D   D;  //  Dual Edge
    typedef typename T::R   R;  //  Ring
    typedef typename T::V   V;  //  Vertex Data
    typedef typename T::F   F;  //  Face Data

    RingRef( R& i_ring ) : d_ring( i_ring ) {}

    E oNext() const { return d_ring.next(); }
    E oPrev() const { return d_ring.dual().next().dual(); }

    E dNext() const { return d_ring.dual().dual().next().dual().dual(); }
    E dPrev() const { return d_ring.dual().dual().dual().next().dual().dual().dual(); }

    E lNext() const { return d_ring.dual().dual().dual().next().dual(); }
    E lPrev() const { return d_ring.next().dual().dual(); }

    E rNext() const { return d_ring.dual().next().dual().dual().dual(); }
    E rPrev() const { return d_ring.dual().dual().next(); }

    D rot()   const { return d_ring.dual(); }
    E sym()   const { return d_ring.dual().dual(); }

    const V& o() const { return *d_ring.data(); }
    const F& r() const { return *d_ring.dual().data(); }
    const V& d() const { return *d_ring.dual().dual().data(); }
    const F& l() const { return *d_ring.dual().dual().dual().data(); }
    
    V& o() { return *d_ring.data(); }
    F& r() { return *d_ring.dual().data(); }
    V& d() { return *d_ring.dual().dual().data(); }
    F& l() { return *d_ring.dual().dual().dual().data(); }

  protected:

    const R& ring() const { return d_ring; }

  private:

    RingRef();
    RingRef& operator = ( const RingRef& );

  private:

    R& d_ring;
  };

  /////////////////////////////////////////////////////////////////////////////
  
  template <typename V, typename F>
  class ConstEdge;

  template <typename V, typename F>
  struct ConstEdgeTraits
  {
    typedef ConstEdge<V, F>   E;
    typedef ConstEdge<F, V>   D;
    typedef const Ring<V, F>  R;
    typedef const V           V;
    typedef const F           F;
  };

  template <typename V, typename F>
  class ConstEdge : public RingRef<ConstEdgeTraits<V, F>>
  {
  public:
    
    ConstEdge( R& i_ring ) : RingRef( i_ring ) {}
  };

  /////////////////////////////////////////////////////////////////////////////

  template <typename V, typename F>
  class Edge;

  template <typename V, typename F>
  struct EdgeTraits
  {
    typedef Edge<V, F>  E;
    typedef Edge<F, V>  D;
    typedef Ring<V, F>  R;
    typedef V           V;
    typedef F           F;
  };

  template <typename V, typename F>
  class Edge : public RingRef<EdgeTraits<V, F>>
  {
  public:
    
    Edge( R& i_ring ) : RingRef( i_ring ) {}

    operator ConstEdge<V, F> () const { return ring(); }
  };
}