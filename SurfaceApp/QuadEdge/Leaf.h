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


namespace Leaf_NS
{
  template <typename Core>
  class Leaf
  {
  public:

    using Dual = Leaf<typename Core::Dual>;

    Leaf( Dual& i_dual ) : d_next( this ), d_dual( i_dual ), d_core( std::make_shared<Core>() ) {}

    //  topology accessors

    const Leaf& next() const { return *d_next; }
    Leaf&       next()       { return *d_next; }

    const Dual& dual() const { return d_dual; }
    Dual&       dual()       { return d_dual; }

    const Core& core() const { return *d_core; }
    Core&       core()       { return *d_core; }

    //  exchange links
    void swap( Leaf& o ) { std::swap( d_next, o.d_next ); }

    //  take other's leaf core
    void reset( Leaf& o ) { core( o.d_core ); }

    //  take unique core
    void reset() { core( std::make_shared<Core>() ); }

    //  half of edge splice operation, changes own core
    void fuse( Leaf& o )
    {
      if( d_core == o.d_core )
      {
        //  detach this leaf from other leaf
        swap( o );
        reset();
      }
      else
      {
        //  attach this leaf to other leaf
        reset( o );
        swap( o );
      }
    }

  private:

    using Ptr = std::shared_ptr<Core>;

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