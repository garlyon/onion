#pragma once


#include "Leaf.h"
#include "Quad.h"
#include <vector>
#include <list>
#include <unordered_set>
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
    
    using Prim = Leaf<Vert>;
    using Dual = Leaf<Face>;
        
    //  single quad edge construction
    Prim& make() { d_quads.emplace_back(); return d_quads.back().o(); }

    //  list of all primal nodes
    std::vector<const Prim*> verts() const;
    std::vector<Prim*>       verts();

    //  list of all dual nodes
    std::vector<const Dual*> faces() const;
    std::vector<Dual*>       faces();

    //  list of all primal ribs (full edges)
    std::vector<const Prim*> prims() const;
    std::vector<Prim*>       prims();

    //  list of all dual ribs (full co-edges)
    std::vector<const Dual*> duals() const;
    std::vector<Dual*>       duals();

    //  shape cleanup removes disconnected quad edges
    void compress() { d_quads.remove_if( []( const Quad& q ) { return q.unique(); } ); }

  private:

    std::list<Quad> d_quads;
  };


  template <typename Core>
  using Vert = typename Shape<Core>::Vert;


  template <typename Core>
  using Face = typename Shape<Core>::Face;


  template <typename Core>
  using Prim = typename Shape<Core>::Prim;


  template <typename Core>
  using Dual = typename Shape<Core>::Dual;


  /////////////////////////////////////////////////////////////////////////////


  template <typename Core>
  auto Shape<Core>::verts() const -> std::vector<const Prim*>
  {
    std::unordered_set<const Vert*> nodes;
    std::vector<const Prim*> edges;

    for( const Quad& q : d_quads )
    {
      if( nodes.insert( &q.o().o() ).second ) edges.push_back( &q.o() );
      if( nodes.insert( &q.d().o() ).second ) edges.push_back( &q.d() );
    }

    return edges;
  }


  template <typename Core>
  auto Shape<Core>::verts() -> std::vector<Prim*>
  {
    std::unordered_set<Vert*> nodes;
    std::vector<Prim*> edges;

    for( Quad& q : d_quads )
    {
      if( nodes.insert( &q.o().o() ).second ) edges.push_back( &q.o() );
      if( nodes.insert( &q.d().o() ).second ) edges.push_back( &q.d() );
    }

    return edges;
  }


  template <typename Core>
  auto Shape<Core>::faces() const -> std::vector<const Dual*>
  {
    std::unordered_set<const Face*> nodes;
    std::vector<const Dual*> edges;

    for( const Quad& q : d_quads )
    {
      if( nodes.insert( &q.l().o() ).second ) edges.push_back( &q.l() );
      if( nodes.insert( &q.r().o() ).second ) edges.push_back( &q.r() );
    }

    return edges;
  }


  template <typename Core>
  auto Shape<Core>::faces() -> std::vector<Dual*>
  {
    std::unordered_set<Face*> nodes;
    std::vector<Dual*> edges;

    for( Quad& q : d_quads )
    {
      if( nodes.insert( &q.l().o() ).second ) edges.push_back( &q.l() );
      if( nodes.insert( &q.r().o() ).second ) edges.push_back( &q.r() );
    }

    return edges;
  }


  template <typename Core>
  auto Shape<Core>::prims() const -> std::vector<const Prim*>
  {
    std::vector<const Prim*> edges;
    for( const Quad& q : d_quads ) edges.push_back( &q.o() );
    return edges;
  }


  template <typename Core>
  auto Shape<Core>::prims() -> std::vector<Prim*>
  {
    std::vector<Prim*> edges;
    for( Quad& q : d_quads ) edges.push_back( &q.o() );
    return edges;
  }


  template <typename Core>
  auto Shape<Core>::duals() const -> std::vector<const Dual*>
  {
    std::vector<const Dual*> edges;
    for( const Quad& q : d_quads ) edges.push_back( &q.l() );
    return edges;
  }


  template <typename Core>
  auto Shape<Core>::duals() -> std::vector<Dual*>
  {
    std::vector<Dual*> edges;
    for( Quad& q : d_quads ) edges.push_back( &q.l() );
    return edges;
  }
}