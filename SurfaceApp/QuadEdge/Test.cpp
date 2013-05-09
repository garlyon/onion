#include "Test.h"
#include "Ring.h"
#include "Edge.h"
#include <string>

struct VertData
{
  std::string vid;
};

struct FaceData
{  
  std::string fid;
};

template <size_t> struct Vert;
template <size_t> struct Face;

template <size_t id>
struct Vert : public VertData
{
  typedef Face<id>                      Dual;
  typedef QuadEdge_NS::Reg<Vert, id>    Reg;
};

template <size_t id>
struct Face : public FaceData
{
  typedef Vert<id>                      Dual;
  typedef QuadEdge_NS::Reg<Face, id>    Reg;
};

void QuadEdge_NS::test()
{
  typedef Quad<Vert<0>> Q;
  typedef Edge<Vert<0>> E;

  auto& verts = Vert<0>::Reg::get();
  auto& faces = Face<0>::Reg::get();

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

  auto& f = QuadEdge_NS::Edge<Face<0>>( (*Face<0>::Reg::get().begin())->ring() );

  s = f.o()->fid;
  s = f.d()->fid;

  splice( e, e.sym() );
}