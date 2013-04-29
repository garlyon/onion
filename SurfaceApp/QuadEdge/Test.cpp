#include "Test.h"

#include "Ring.h"
//#include "Shape.h"

void QuadEdge_NS::test()
{
  //using namespace QuadEdge_NS;
  
  Quad a, b, c;

  splice( a.d().rot().rot(), b.o() );
  splice( b.d().rot().rot(), c.o() );
  splice( c.d().rot().rot(), a.o() );
}