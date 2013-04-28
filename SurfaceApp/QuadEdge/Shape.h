#pragma once

#include "Quad.h"
#include <list>

namespace QuadEdge_NS
{
  class Shape
  {
    std::list<Quad> d_quads;
  };
}