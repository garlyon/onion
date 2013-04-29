#pragma once

#include "Ring.h"
#include <vector>
#include <memory>

namespace QuadEdge_NS
{
  class Shape
  {
    std::vector<Quad*> d_nodes;

  public:

    ORing& create() { d_nodes.push_back( Quad::create() ); return d_nodes.back()->edge(); }

  public:

    ~Shape()
    {
      std::for_each( d_nodes.begin(), d_nodes.end(), []( Quad* ptr ) { delete ptr; } );
    }
  };
}