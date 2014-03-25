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

  private:

    Leaf&                   d_owner;
    std::unique_ptr<Core>   d_core;   //  User data

  private:

    Ring() = delete;
    Ring( const Ring& ) = delete;
    Ring& operator = ( const Ring& ) = delete;
  };
}