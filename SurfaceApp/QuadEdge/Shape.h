#pragma once


#include "Edge.h"
#include "Quad.h"
#include <vector>
#include <list>
#include <unordered_set>
#include <memory>
#include <functional>


namespace Quad_NS
{
  template <typename Core>
  class Shape
  {
  public:

    using Vert = Core;
    using Face = typename Core::Dual;
    
    using Quad = Quad<Vert>;
    
    using Prim = Edge<Vert>;
    using Dual = Edge<Face>;
    
    using ConstPrim = ConstEdge<Vert>;
    using ConstDual = ConstEdge<Face>;
    
    //  primitive construction
    Prim make() { d_quads.emplace_back(); return d_quads.back().o(); }

    //  topology data accessors
    std::vector<ConstPrim> verts() const { return nodes<Vert>(); }
    std::vector<ConstDual> faces() const { return nodes<Face>(); }
    std::vector<ConstPrim> edges() const { return ribs<Vert>(); }
    std::vector<ConstDual> duals() const { return ribs<Face>(); }

    std::vector<Prim> verts() { return nodes<Vert>(); }
    std::vector<Dual> faces() { return nodes<Face>(); }
    std::vector<Prim> edges() { return ribs<Vert>(); }
    std::vector<Dual> duals() { return ribs<Face>(); }

    //  shape cleanup removes disconnected quads
    void compress() { d_quads.remove_if( []( const Quad& q ) { return q.unique(); } ); }

  private:

    template <typename C> std::vector<ConstEdge<C>> nodes() const;
    template <typename C> std::vector<ConstEdge<C>> ribs() const;

    template <typename C> std::vector<Edge<C>> nodes();
    template <typename C> std::vector<Edge<C>> ribs();

  private:

    std::list<Quad> d_quads;
  };


  /////////////////////////////////////////////////////////////////////////////


  template <typename Core> template <typename C>
  auto Shape<Core>::nodes() const -> std::vector<ConstEdge<C>>
  {
    std::unordered_set<const C*> n;
    std::vector<ConstEdge<C>> o;

    auto add = [&n, &o]( const Leaf<C>& i ) { if( n.insert( &i.core() ).second ) o.push_back( i ); };

    for( const Quad& q : d_quads )
    {
      add( q.f<C>() );
      add( q.b<C>() );
    }

    return o;
  }


  template <typename Core> template <typename C>
  auto Shape<Core>::nodes() -> std::vector<Edge<C>>
  {
    std::unordered_set<const C*> n;
    std::vector<Edge<C>> o;

    auto add = [&n, &o]( Leaf<C>& i ) { if( n.insert( &i.core() ).second ) o.push_back( i ); };

    for( Quad& q : d_quads )
    {
      add( q.f<C>() );
      add( q.b<C>() );
    }

    return o;
  }


  template <typename Core> template <typename C>
  auto Shape<Core>::ribs() const -> std::vector<ConstEdge<C>>
  {
    std::vector<ConstEdge<C>> o;

    for( const Quad& q : d_quads )
    {
      o.push_back( q.f<C>() );
    }

    return o;
  }


  template <typename Core> template <typename C>
  auto Shape<Core>::ribs() -> std::vector<Edge<C>>
  {
    std::vector<Edge<C>> o;

    for( Quad& q : d_quads )
    {
      o.push_back( q.f<C>() );
    }

    return o;
  }
}