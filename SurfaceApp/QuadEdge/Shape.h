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
    
    using ConstEdge = Edge_NS::ConstEdge<Vert>;
    using ConstDual = Edge_NS::ConstEdge<Face>;
    
    //  primitive construction
    Edge make() { d_quads.emplace_back(); return d_quads.back().o(); }

    //  topology data accessors
    std::vector<ConstEdge> verts() const { return nodes<Vert>(); }
    std::vector<ConstDual> faces() const { return nodes<Face>(); }
    std::vector<ConstEdge> edges() const { return ribs<Vert>(); }
    std::vector<ConstDual> duals() const { return ribs<Face>(); }

    std::vector<Edge> verts() { return nodes<Vert>(); }
    std::vector<Dual> faces() { return nodes<Face>(); }
    std::vector<Edge> edges() { return ribs<Vert>(); }
    std::vector<Dual> duals() { return ribs<Face>(); }

    //  shape cleanup removes separated quads
    void compress() { d_quads.remove_if( []( const Quad& q ) { return q.unique(); } ); }

  private:

    template <typename C> std::vector<Edge_NS::ConstEdge<C>> nodes() const;
    template <typename C> std::vector<Edge_NS::ConstEdge<C>> ribs() const;

    template <typename C> std::vector<Edge_NS::Edge<C>> nodes();
    template <typename C> std::vector<Edge_NS::Edge<C>> ribs();

  private:

    std::list<Quad> d_quads;
  };


  /////////////////////////////////////////////////////////////////////////////


  template <typename Core> template <typename C>
  auto Shape<Core>::nodes() const -> std::vector<Edge_NS::ConstEdge<C>>
  {
    std::unordered_set<const C*> n;
    std::vector<Edge_NS::ConstEdge<C>> o;

    auto add = [&n, &o]( const Leaf_NS::Leaf<C>& i ) { if( n.insert( &i.core() ).second ) o.push_back( i ); };

    for( const Quad& q : d_quads )
    {
      add( q.f<C>() );
      add( q.b<C>() );
    }

    return o;
  }


  template <typename Core> template <typename C>
  auto Shape<Core>::nodes() -> std::vector<Edge_NS::Edge<C>>
  {
    std::unordered_set<const C*> n;
    std::vector<Edge_NS::Edge<C>> o;

    auto add = [&n, &o]( Leaf_NS::Leaf<C>& i ) { if( n.insert( &i.core() ).second ) o.push_back( i ); };

    for( Quad& q : d_quads )
    {
      add( q.f<C>() );
      add( q.b<C>() );
    }

    return o;
  }


  template <typename Core> template <typename C>
  auto Shape<Core>::ribs() const -> std::vector<Edge_NS::ConstEdge<C>>
  {
    std::vector<Edge_NS::ConstEdge<C>> o;

    for( const Quad& q : d_quads )
    {
      o.push_back( q.f<C>() );
    }

    return o;
  }


  template <typename Core> template <typename C>
  auto Shape<Core>::ribs() -> std::vector<Edge_NS::Edge<C>>
  {
    std::vector<Edge_NS::Edge<C>> o;

    for( Quad& q : d_quads )
    {
      o.push_back( q.f<C>() );
    }

    return o;
  }
}