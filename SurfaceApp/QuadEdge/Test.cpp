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

  std::shared_ptr<Q> a( new Q );
  std::shared_ptr<Q> b( new Q );
  std::shared_ptr<Q> c( new Q );

  E ea( a->o() );
  E eb( b->o() );
  E ec( c->o() );

  ea.o()->vid = "A";
  eb.o()->vid = "B";
  ec.o()->vid = "C";

  ea.l()->fid = "In";
  ea.r()->fid = "Out";

  splice( eb, ea.sym() ); //  reset ea.d and ea.r
  splice( ec, eb.sym() ); //  reset eb.d and eb.r
  splice( ea, ec.sym() ); //  reset ec.d and ec.r

  std::string s;

  s = ea.o()->vid;
  s = eb.o()->vid;
  s = ec.o()->vid;
  s = ea.l()->fid;
  s = ea.r()->fid;
}