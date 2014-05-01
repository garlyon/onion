#pragma once


#include "Vector.h"
#include "Shape.h"


namespace Math_NS
{
  struct VertData;
  struct FaceData;
  struct PrimData;
  struct DualData;


  struct VertData : public VectorI
  {
    using Dual = FaceData;
    using Edge = PrimData;
  };


  struct FaceData
  {
    using Dual = VertData;
    using Edge = DualData;
  };


  struct PrimData
  {
    enum Type
    {
      Original,
      Intersection,
      Triangulation
    };

    Type type;
  };


  struct DualData {};


  /////////////////////////////////////////////////////////////////////////////


  using Shape = Quad_NS::Shape<VertData>;
}