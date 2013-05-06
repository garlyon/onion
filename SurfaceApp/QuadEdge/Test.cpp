#include "Test.h"
#include "Ring.h"
#include "Edge.h"
//#include "Shape.h"
#include <string>

void QuadEdge_NS::test()
{
  struct VertData
  {
    std::string vid;
  };

  struct FaceData
  {
    std::string fid;
  };

  typedef Quad<VertData, FaceData> Q;
  typedef Edge<VertData, FaceData> E;

  std::shared_ptr<Q> a = Q::create();

  E e( a->o() );


  e.o()->vid = "Orig";
  e.d()->vid = "Dest";

  e.l()->fid = "Left";  //   = right

  bool x;
  std::string s;

  splice( e, e.sym() ); //  expect e.o = e.d = Orig; e.l = "Left", e.r = new

  s = e.o()->vid;
  s = e.d()->vid;
  s = e.l()->fid;
  s = e.r()->fid;

  auto z = *e.o();

  splice( e, e.sym() );
}