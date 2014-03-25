#pragma once


//
//  class Ring
//  {
//    Leaf* owner     //  first leaf linked to this ring
//    Core* ...       //  user data
//  }
//


#include <memory>


namespace Leaf_NS { template <typename> class Leaf; }


namespace Ring_NS
{
  template <typename Core>
  class Ring
  {
  public:

    using Leaf = Leaf_NS::Leaf<Core>;

    Ring( Leaf& i_owner ) : d_owner( i_owner ) {}

    //  user data accessor
    const Core& operator -> ( ) const { return *d_core; }
    Core&       operator -> ( )       { return *d_core; }

    //  user data constructor
    template <typename ... Args>
    void reset( Args&& ... i_args ) { d_core = std::make_unique<Core>( i_args... ); }

  private:

    Leaf&                   d_owner;
    std::unique_ptr<Core>   d_core;   //  User data

  private:

    Ring() = delete;
    Ring( const Ring& ) = delete;
    Ring& operator = ( const Ring& ) = delete;
  };
}