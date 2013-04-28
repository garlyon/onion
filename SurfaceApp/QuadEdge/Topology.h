#pragma once

#include "Quad.h"

namespace QuadEdge_NS
{
  template <int T>
  void splice( Ring<T>& a, Ring<T>& b )
  {
    a.next().rot().swap( b.next().rot() );
    a.swap( b );
  }
}