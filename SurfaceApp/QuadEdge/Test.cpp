#include "Test.h"
#include "Ring.h"
#include "Edge.h"
//#include "Shape.h"
#include <string>

struct VertData;
struct FaceData;

struct VertData
{
  typedef VertData Prim;
  typedef FaceData Dual;

  const VertData* operator -> () const { return this; }
  VertData*       operator -> ()       { return this; }

  std::string vid;
};

struct FaceData
{
  typedef FaceData Prim;
  typedef VertData Dual;
  
  const FaceData* operator -> () const { return this; }
  FaceData*       operator -> ()       { return this; }

  std::string fid;
};

void QuadEdge_NS::test()
{
  typedef Quad<VertData> Q;
  typedef Edge<VertData> E;

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

  splice( e, e.sym() );
}