#pragma once


#include "Vector.h"
#include "Shape.h"


namespace Math_NS
{
  struct VertData;
  struct FaceData;
  struct PrimData;
  struct DualData;


  using I = long long int;


  struct VertData : public Vector<I>
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