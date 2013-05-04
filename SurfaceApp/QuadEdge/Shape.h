#pragma once

#include "Ring.h"
#include <vector>

namespace QuadEdge_NS
{
  template <typename V, typename F>
  class Shape
  {
    std::vector<Quad<V, F>*> d_nodes;
    std::vector<Ring<V, F>*> d_verts;
    std::vector<Ring<F, V>*> d_faces;

  public:

    Quad<V, F>& create() { d_nodes.push_back( new Quad<V, F>() ); return *d_nodes.back(); }
    
    V& create( Ring<V, F>& i_ring ) { i_ring.data( new V ); d_verts.push_back( &i_ring ); return *i_ring.data(); }
    F& create( Ring<F, V>& i_ring ) { i_ring.data( new F ); d_faces.push_back( &i_ring ); return *i_ring.data(); }
    
    const std::vector<Ring<V, F>*>& verts() const { return d_verts; }
    const std::vector<Ring<F, V>*>& faces() const { return d_faces; }

    ~Shape()
    {
      std::for_each( d_verts.begin(), d_verts.end(), []( Ring<V, F>* i_ptr ) { delete i_ptr->data(); } );
      std::for_each( d_faces.begin(), d_faces.end(), []( Ring<F, V>* i_ptr ) { delete i_ptr->data(); } );
      std::for_each( d_nodes.begin(), d_nodes.end(), []( Quad<V, F>* i_ptr ) { delete i_ptr; } );
    }
  };
}