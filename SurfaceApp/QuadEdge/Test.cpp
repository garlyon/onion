#include "Test.h"
#include "Shape.h"
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

  Shape_NS::Shape s2;

  STL_NS::read( "../out.stl", s2, g );

  auto verts2 = s2.verts();
  auto faces2 = s2.faces();
  auto edges2 = s2.prims();
  auto duals2 = s2.duals();
}