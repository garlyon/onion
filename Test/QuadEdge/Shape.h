#include "QuadEdge.h"
#include "Collection.h"

namespace QuadEdge_NS
{
  class Shape
  {
    std::vector<Edge> d_edge;

  public:
    
    Edge makeEdge();

    void splice( Edge i_left, Edge i_right );
  };
}