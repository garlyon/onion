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
};


struct FaceData
{  
  std::string fid;

  using Dual = VertData;
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

  a.o().vid = "A";
  a.d().vid = "B";
  b.d().vid = "C";

  auto v = s.verts();
  auto f = s.faces();

  s.compress();

  s.make();

  s.compress();

  const auto& cs = s;

  Edge_NS::ConstEdge<VertData> ca = a;

  bool t = ca.o().vid == cs.verts().front().o().vid;
}