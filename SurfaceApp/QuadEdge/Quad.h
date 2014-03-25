#pragma once


namespace Leaf_NS { template <typename> class Leaf; }


#pragma once


#include "Leaf.h"


namespace Quad_NS
{
  template <typename Core>
  class Quad
  {
  public:

    using Prim = Leaf_NS::Leaf<Core>;
    using Dual = Leaf_NS::Leaf<typename Core::Dual>;

    Quad() : o( r ), d( l ), l( o ), r( d )
    {
      l.swap( r );
      l.reset( r );
    }

    Prim& leaf() { return o; }

  private:

    Prim o;
    Prim d;
    Dual l;
    Dual r;

  private:

    Quad( const Quad& ) = delete;
    Quad( Quad&& ) = delete;
    Quad& operator = ( const Quad& ) = delete;
    Quad& operator = ( Quad&& ) = delete;
  };
}