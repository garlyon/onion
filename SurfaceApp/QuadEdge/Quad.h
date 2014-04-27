#pragma once


#include "Leaf.h"


namespace Quad_NS
{
  template <typename Core>
  class Quad
  {
  public:

    using Vert = Core;
    using Face = typename Core::Dual;
    using Prim = Leaf<Vert>;
    using Dual = Leaf<Face>;

    //  straight edge
    Quad() : d_oVert( d_rFace ), d_dVert( d_lFace ), d_lFace( d_oVert ), d_rFace( d_dVert ) { d_lFace.fuse( d_rFace ); }

    //  check if edge connected to other edges or not
    bool unique() const;

    //  direct accessors

    const Prim& o() const { return d_oVert; }
    const Prim& d() const { return d_dVert; }
    const Dual& l() const { return d_lFace; }
    const Dual& r() const { return d_rFace; }

    Prim& o() { return d_oVert; }
    Prim& d() { return d_dVert; }
    Dual& l() { return d_lFace; }
    Dual& r() { return d_rFace; }

  private:

    Prim d_oVert;
    Prim d_dVert;
    Dual d_lFace;
    Dual d_rFace;

  private:

    Quad( const Quad& ) = delete;
    Quad( Quad&& ) = delete;
    Quad& operator = ( const Quad& ) = delete;
    Quad& operator = ( Quad&& ) = delete;
  };


  /////////////////////////////////////////////////////////////////////////////


  template <typename Core>
  bool Quad<Core>::unique() const
  {
    return ( &o().next() == &o() && &d().next() == &d() && &l().next() == &r() && &r().next() == &l() )
      ||   ( &l().next() == &l() && &r().next() == &r() && &o().next() == &d() && &d().next() == &o() );
  }
}