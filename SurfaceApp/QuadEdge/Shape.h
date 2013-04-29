#pragma once

#include "Ring.h"
#include <vector>
#include <memory>

namespace QuadEdge_NS
{
  class Shape
  {
    std::vector<std::shared_ptr<Quad>> d_nodes;

  public:

    Quad& create() { d_nodes.push_back( Quad::create() ); return *d_nodes.back(); }
  };
}