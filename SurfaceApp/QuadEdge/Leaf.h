#pragma once


//
//  class Leaf
//  {
//    Core* core  //  all lifs in a list refer to the same core
//    Leaf* next
//    Leaf* dual
//  }
//


#include <memory>


namespace Ring_NS { template <typename> class Ring; }


namespace Leaf_NS
{
  template <typename Core>
  class Leaf
  {
  public:

    using Ring = Ring_NS::Ring<Core>;
    using Dual = Leaf<typename Core::Dual>;
    using Ptr = std::shared_ptr<Ring>;

    Leaf( Dual& i_dual ) : d_next( this ), d_dual( i_dual ), d_core( std::make_shared<Ring>( *this ) ) {}

    //  exchange links
    void swap( Leaf& o ) { std::swap( d_next, o.d_next ); }

    //  take other's leaf core
    void reset( Leaf& o ) { core( o.d_core ); }

    //  take unique core
    void reset() { core( std::make_shared<Ring>( *this ) ); }

  private:

    void core( Ptr i_core ) { Leaf* f = this; do { f->d_core = i_core; } while( ( f = f->d_next ) != this ); }

  private:

    Leaf*   d_next;
    Dual&   d_dual;
    Ptr     d_core;

  private:

    Leaf() = delete;
    Leaf( const Leaf& ) = delete;
    Leaf( Leaf&& ) = delete;
    Leaf& operator = ( const Leaf& ) = delete;
    Leaf& operator = ( Leaf&& ) = delete;
  };
}