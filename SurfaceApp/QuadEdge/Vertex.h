#pragma once


#include "Vector.h"


namespace Shape_NS
{
  struct IVertex
  {
    virtual const Math_NS::VectorI point() const = 0;
    virtual ~IVertex() {}
  };


  class VertexI : public IVertex, public Math_NS::VectorI
  {
    virtual const Math_NS::VectorI point() const override { return *this; }
  public:
    VertexI( const Math_NS::VectorI& v ) : Math_NS::VectorI{ v } {}
  };
}