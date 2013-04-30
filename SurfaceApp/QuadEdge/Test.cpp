#include "Test.h"

#include "Shape.h"

void QuadEdge_NS::test()
{
  Shape s;
  
  ORing& a = s.create();
  ORing& b = s.create();
  ORing& c = s.create();

  splice( a.rot().rot(), b );
  splice( b.rot().rot(), c );
  splice( c.rot().rot(), a );

  ORing& d = s.create();

  splice( a, d );

  std::vector<size_t> v;
  v.push_back( sizeof(Quad) );
  v.push_back( sizeof(Quad*) );
  v.push_back( sizeof(RRing) );
  v.push_back( sizeof(RRing*) );
}