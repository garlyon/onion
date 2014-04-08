#include "Test.h"
#include "Edge.h"
#include "Shape.h"
#include <string>


struct VertData;
struct FaceData;


struct VertData
{
  std::string vid;

  using Dual = FaceData;
  
  const VertData* operator -> ( ) const { return this; }
  VertData*       operator -> ( )       { return this; }
};


struct FaceData
{  
  std::string fid;

  using Dual = VertData;

  const FaceData* operator -> ( ) const { return this; }
  FaceData*       operator -> ( )       { return this; }
};


void QuadEdge_NS::test()
{
  Shape_NS::Shape<VertData> s;

  Edge_NS::Edge<VertData> a = s.make();
  Edge_NS::Edge<VertData> b = s.make();
  Edge_NS::Edge<VertData> c = s.make();

  splice( a.sym(), b );
  splice( b.sym(), c );
  splice( c.sym(), a );

  a.o().reset();
  b.o().reset();
  c.o().reset();

  a.o()->vid = "A";
  a.d()->vid = "B";
  b.d()->vid = "C";
}