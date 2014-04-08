#pragma once


//
//  class Leaf
//  {
//    Ring* ring  //  all lifs in a list refer to the same ring
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

    Leaf( Dual& i_dual ) : d_next( this ), d_dual( i_dual ), d_ring( std::make_shared<Ring>( *this ) ) {}

    //  topology accessors

    const Leaf& next() const { return *d_next; }
    Leaf&       next()       { return *d_next; }

    const Dual& dual() const { return d_dual; }
    Dual&       dual()       { return d_dual; }

    const Ring& ring() const { return *d_ring; }
    Ring&       ring()       { return *d_ring; }

    //  exchange links
    void swap( Leaf& o ) { std::swap( d_next, o.d_next ); }

    //  take other's leaf ring
    void reset( Leaf& o ) { ring( o.d_ring ); }

    //  take unique core
    void reset() { ring( std::make_shared<Ring>( *this ) ); }

    //  half of edge splice operation, changes own ring
    void fuse( Leaf& o )
    {
      if( d_ring == o.d_ring )
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

    using Ptr = std::shared_ptr<Ring>;

    void ring( Ptr i_ring ) { Leaf* f = this; do { f->d_ring = i_ring; } while( ( f = f->d_next ) != this ); }

  private:

    Leaf*   d_next;
    Dual&   d_dual;
    Ptr     d_ring;

  private:

    Leaf() = delete;
    Leaf( const Leaf& ) = delete;
    Leaf( Leaf&& ) = delete;
    Leaf& operator = ( const Leaf& ) = delete;
    Leaf& operator = ( Leaf&& ) = delete;
  };
}