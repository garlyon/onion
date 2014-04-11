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

    using Vert = Core;
    using Face = typename Core::Dual;
    
    using Quad = Quad_NS::Quad<Vert>;
    using Edge = Edge_NS::Edge<Vert>;
    using Dual = Edge_NS::Edge<Face>;
    
    Edge make() { d_quads.emplace_back(); return d_quads.back().o(); }

    template <typename C> std::vector<Edge_NS::Edge<C>> nodes();

    std::vector<Edge> verts() { return nodes<Vert>(); }
    std::vector<Dual> faces() { return nodes<Face>(); }

    void compress() { d_quads.remove_if( []( const Quad& q ) { return q.unique(); } ); }

  private:

    std::list<Quad> d_quads;
  };


  /////////////////////////////////////////////////////////////////////////////


  template <typename Core> template <typename C>
  auto Shape<Core>::nodes() -> std::vector<Edge_NS::Edge<C>>
  {
    std::unordered_set<C*> n;
    std::vector<Edge_NS::Edge<C>> o;

    auto add = [&n, &o]( Leaf_NS::Leaf<C>& i ) { if( n.insert( &i.core() ).second ) o.push_back( i ); };

    for( Quad& q : d_quads )
    {
      add( q.f<C>() );
      add( q.b<C>() );
    }

    return o;
  }
}