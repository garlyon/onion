#pragma once


#include "Edge.h"
#include "Quad.h"
#include <vector>
#include <memory>


namespace Shape_NS
{
  template <typename Core>
  class Shape
  {
  public:

    Edge_NS::Edge<Core> make() { d_quads.push_back( std::make_unique<Quad_NS::Quad<Core>>() ); return d_quads.back()->leaf(); }

  private:

    std::vector<std::unique_ptr<Quad_NS::Quad<Core>>> d_quads;
  };
}