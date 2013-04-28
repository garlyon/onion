#include "Quad.h"

QuadEdge_NS::Quad::Quad( Edge i_oVert, Edge i_rFace, Edge i_dVert, Edge i_lFace ) : d_oVert( i_oVert ), d_rFace( i_rFace ), d_dVert( i_dVert ), d_lFace( i_lFace )
{
}

QuadEdge_NS::Quad::Quad() : d_oVert( &d_oVert ), d_dVert( &d_dVert ), d_lFace( &d_rFace ), d_rFace( &d_lFace )
{
}

QuadEdge_NS::Quad& QuadEdge_NS::Quad::cRot()
{
  const Edge oVert = d_oVert;
  
  d_oVert = d_rFace;
  d_rFace = d_dVert;
  d_dVert = d_lFace;
  d_lFace = oVert;

  return *this;
}