#include "Test.h"
#include "VShape.h"
#include "STL.h"


void Quad_NS::test()
{
  Shape_NS::Shape s;

  Math_NS::Grid g = STL_NS::box( "../test.stl" );

  STL_NS::read( "../test.stl", s, g );

  auto verts = s.verts();
  auto faces = s.faces();
  auto edges = s.prims();
  auto duals = s.duals();

  STL_NS::write( "../out.stl", s, g );
}