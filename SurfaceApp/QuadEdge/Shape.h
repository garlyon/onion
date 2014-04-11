#pragma once


#include "Edge.h"
#include "Quad.h"
#include <vector>
#include <list>
#include <unordered_set>
#include <memory>
#include <functional>


namespace Shape_NS
{
  template <typename Core>
  class Shape
  {
  public:

    using Dual = typename Core::Dual;
    using Quad = Quad_NS::Quad<Core>;
    using Edge = Edge_NS::Edge<Core>;
    
    Edge make() { d_quads.emplace_back(); return d_quads.back().o(); }

    template <typename C> using Ring = Ring_NS::Ring<C>;
    template <typename C> using Ref = std::reference_wrapper<Ring<C>>;

    using Vert = Ring<Core>;
    using Face = Ring<Dual>;
    using VertRef = Ref<Core>;
    using FaceRef = Ref<Dual>;

    template <typename C> std::vector<Ref<C>> nodes();

    std::vector<VertRef> verts() { return nodes<Core>(); }
    std::vector<FaceRef> faces() { return nodes<Dual>(); }

    void compress() { d_quads.remove_if( []( const Quad& q ) { return q.unique(); } ); }

  private:

    std::list<Quad> d_quads;
  };


  /////////////////////////////////////////////////////////////////////////////


  template <typename Core> template <typename C>
  auto Shape<Core>::nodes() -> std::vector<Ref<C>>
  {
    std::unordered_set<Ring<C>*> n;
    std::vector<Ref<C>> o;

    auto add = [&n, &o]( Ring<C>& r ) { if( n.insert( &r ).second ) o.push_back( r ); };

    for( Quad& q : d_quads )
    {
      add( q.f<C>().ring() );
      add( q.b<C>().ring() );
    }

    return o;
  }
}