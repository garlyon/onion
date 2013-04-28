#pragma once

namespace QuadEdge_NS
{
  class Edge
  {
    Edge* d_next;   //  edge ring at origin vertex
    Edge* d_dual;   //  dual edge ring at right face

  public:

    const Edge& next() const;
    const Edge& dual() const;
  };
}