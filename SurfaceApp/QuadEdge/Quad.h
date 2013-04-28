#pragma once

#include "Ring.h"

namespace QuadEdge_NS
{
  class Quad
  {
    ORing d_oVert;
    RRing d_rFace;
    DRing d_dVert;
    LRing d_lFace;

  public:

    Quad() { d_lFace.swap( d_rFace.rot().rot() ); }

  public:

    const ORing& o() const { return d_oVert; }
    const RRing& r() const { return d_rFace; }
    const DRing& d() const { return d_dVert; }
    const LRing& l() const { return d_lFace; }

    ORing& o() { return d_oVert; }
    RRing& r() { return d_rFace; }
    DRing& d() { return d_dVert; }
    LRing& l() { return d_lFace; }
  };
}