#include "Test.h"
#include "Ring.h"
#include "Leaf.h"
#include "Quad.h"
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
  Quad_NS::Quad<VertData> q;

  auto& e = q.leaf();
}