#include "Test.h"
#include "Ring.h"
#include "Leaf.h"
#include "Quad.h"
#include <string>
#include "Splice.h"


struct VertData;
struct FaceData;


struct VertData
{
  std::string vid;

  static int s_counter;

  VertData() { ++s_counter; }
  ~VertData() { --s_counter; }

  using Dual = FaceData;
  
  const VertData* operator -> ( ) const { return this; }
  VertData*       operator -> ( )       { return this; }
};

int VertData::s_counter = 0;


struct FaceData
{  
  int fid;

  static int s_counter;

  FaceData() { ++s_counter; }
  ~FaceData() { --s_counter; }

  FaceData( int i_fid ) : FaceData() { fid = i_fid; }

  using Dual = VertData;

  const FaceData* operator -> ( ) const { return this; }
  FaceData*       operator -> ( )       { return this; }
};

int FaceData::s_counter = 0;


void QuadEdge_NS::test()
{
  {
    Quad_NS::Quad<VertData> p, q;

    auto& e = q.leaf();

    e.ring().reset();

    e->vid = "Yahoo Tanok!";

    e.dual().ring().reset( 13 );

    p.leaf().ring().reset();

    Splice_NS::splice( e, p.leaf() );
  }

  bool v = VertData::s_counter == 0;
  bool f = FaceData::s_counter == 0;
}