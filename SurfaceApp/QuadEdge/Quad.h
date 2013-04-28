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

    Quad() : d_oVert( &d_oVert ), d_dVert( &d_dVert ), d_lFace( &d_rFace.rot().rot() ), d_rFace( &d_lFace.rot().rot() ) {}
  };
}