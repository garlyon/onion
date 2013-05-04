#include "Test.h"
#include "Ring.h"
#include "Shape.h"

void QuadEdge_NS::test()
{
  struct VertData
  {
    int vid;
  };

  struct FaceData
  {
    int fid;
  };

  Shape<VertData, FaceData> s;

  auto& a = s.create();
  auto& b = s.create();
  auto& c = s.create();

  splice( a.o().dual().dual(), b.o() );
  splice( b.o().dual().dual(), c.o() );
  splice( c.o().dual().dual(), a.o() );

  s.create( a.o() ).vid = 0;
  s.create( b.o() ).vid = 1;
  s.create( c.o() ).vid = 2;

  s.create( a.l() ).fid = -1;
  s.create( a.r() ).fid = -2;
}