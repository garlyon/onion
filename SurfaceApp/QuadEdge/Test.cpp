#include "Test.h"

#include "Shape.h"

void QuadEdge_NS::test()
{
  Shape s;
  
  Quad& a = s.create();
  Quad& b = s.create();
  Quad& c = s.create();

  splice( a.d(), b.o() );
  splice( b.d(), c.o() );
  splice( c.d(), a.o() );

  Quad& d = s.create();

  splice( a.o(), d.d() );
}