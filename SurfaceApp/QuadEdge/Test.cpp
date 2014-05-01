#include "Test.h"
#include "Leaf.h"
#include "Quad.h"
#include "Shape.h"
#include "Splice.h"
#include <string>
#include <iostream>
#include "Vector.h"
#include "VShape.h"
#include "Box.h"


struct VertData;
struct FaceData;

struct PrimEdge
{
  std::string peid;
};


struct DualEdge {};


struct VertData
{
  std::string vid;

  using Dual = FaceData;
  using Edge = PrimEdge;
};


struct FaceData
{  
  std::string fid;

  using Dual = VertData;
  using Edge = DualEdge;
};


void Quad_NS::test()
{
  Shape<VertData> s;

  Prim<VertData>& a = s.make();
  Prim<VertData>& b = s.make();
  Prim<VertData>& c = s.make();

  a.o().vid = "A";
  a.d().vid = "empty a.d";
  a.l().fid = "Inner";
  a.peid = "eA";
  a.sym().peid = "eA.sym";
  
  b.o().vid = "B";
  b.d().vid = "empty b.d";
  b.l().fid = "empty b.l & b.r";
  b.peid = "eB";
  b.sym().peid = "eB.sym";
  
  c.o().vid = "C";
  c.d().vid = "empty c.d";
  c.l().fid = "empty c.l & c.r";
  c.peid = "eC";
  c.sym().peid = "eC.sym";
  
  a.r();

  spliceAA( a, c.sym() ); //  preserves a.o, a.l
  spliceAB( b, a.sym() ); //  preserves b.o, a.r = a.l
  spliceAB( c, b.sym() ); //  preserves c.o, b.r = b.l


  s.verts();
  s.faces();
  s.prims();
  s.duals();

  const auto& cs = s;

  cs.verts();
  cs.faces();
  cs.prims();
  cs.duals();

  Math_NS::Vector<double> v;

  v = ( v += v );
  v = v + v;
  v = v ^ v;

  v.length();

  Math_NS::Shape ms;

  ms.make().o().lengthSqr();

  Math_NS::Box<char>();
  Math_NS::Box<double>();
}