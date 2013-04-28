#pragma once

#include "Edge.h"

namespace QuadEdge_NS
{
  class Quad
  {
    Edge d_oVert;
    Edge d_rFace;
    Edge d_dVert;
    Edge d_lFace;

  private:

    Quad( Edge i_oVert, Edge i_rFace, Edge i_dVert, Edge i_lFace );

  public:

    Quad();

    Quad& cRot(); //  rotate around edge center
    Quad& oRot(); //  rotate around origin vertex
  };
}