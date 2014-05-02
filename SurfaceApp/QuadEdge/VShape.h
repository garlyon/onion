#pragma once


#include "Shape.h"
#include "Vertex.h"
#include "Vector.h"
#include <memory>


namespace Shape_NS
{
  struct VertData;
  struct FaceData;
  struct PrimData;
  struct DualData;


  struct VertData
  {
    using Dual = FaceData;
    using Edge = PrimData;

    std::unique_ptr<IVertex> vert;
  };


  struct FaceData
  {
    using Dual = VertData;
    using Edge = DualData;
  };


  struct PrimData {};


  struct DualData {};


  /////////////////////////////////////////////////////////////////////////////


  using Shape = Quad_NS::Shape<VertData>;
}