#include "Test.h"
#include "Long.h"
#include <random>


void Quad_NS::test()
{
  using namespace Math_NS;

  std::default_random_engine e;

  for( size_t i = 0; i < 100; ++i )
  {
    Long64 a( e(), e() );
    Long64 b( e(), e() );
    uint64_t A = reinterpret_cast<const uint64_t&>( a );
    uint64_t B = reinterpret_cast<const uint64_t&>( b );
    
    Long64 c = ( a *= b );
    uint64_t C = reinterpret_cast<const uint64_t&>( c );

    uint64_t r = A * B;

    bool x = ( C == r );
  }
}