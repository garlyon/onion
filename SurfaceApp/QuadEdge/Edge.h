#pragma once

namespace QuadEdge_NS
{
  //  this is a half-edge suructure, an element of the edge ring
  class Edge
  {
    Edge* d_next;

  public:

    explicit Edge( Edge* i_next );

    Edge& operator ++ ();
  };
}