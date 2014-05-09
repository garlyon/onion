#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\QuadEdge\Vector.h"
#include "..\QuadEdge\Box.h"
#include "..\QuadEdge\Rational.h"
#include "..\QuadEdge\Long.h"
#include <random>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


using L = Math_NS::Long64;


const uint64_t toi64( const L& x ){ return reinterpret_cast<const uint64_t&>( x ); };


template <> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString( const L& v )
{
  return std::to_wstring( toi64( v ) );
}


namespace UnitTests
{
  TEST_CLASS( Long )
  {
  public:

    TEST_METHOD( Simple )
    {
      Assert::AreEqual( L{}, L{}, L"Zero" );
      Assert::AreEqual( L{ 1, 2 }, L{ 1, 2 }, L"Equality" );

      Assert::IsTrue( L{ 0, 1 } < L{ 0, 2 }, L"Less1" );
      Assert::IsTrue( L{ 0, 1 } < L{ 1, 0 }, L"Less2" );
      Assert::IsTrue( L{ 1, 0 } < L{ 1, 1 }, L"Less3" );

      Assert::AreEqual( L{ 4, 6 }, L{ 1, 2 } +L{ 3, 4 }, L"Sum" );
      Assert::AreEqual( L{ 1, 2 }, L{ 4, 6 } -L{ 3, 4 }, L"Difference" );

      Assert::AreEqual( L{ 0, 0 }, L{ 0, 1 } *L{ 0, 0 }, L"Product0" );
      Assert::AreEqual( L{ 0, 6 }, L{ 0, 2 } *L{ 0, 3 }, L"Product1" );
      Assert::AreEqual( L{ 1, 0 }, L{ 1, 0 } *L{ 0, 1 }, L"Product2" );
      Assert::AreEqual( L{ 1, 0 }, L{ 0, 1 } *L{ 1, 0 }, L"Product3" );
      Assert::AreEqual( L{ 1, 0 }, L{ 1, 0 } *L{ 1, 1 }, L"Product4" );

      Assert::AreEqual( L{ 1, 0 }, L{ 0, 1 << 16 } * L{ 0, 1 << 16 }, L"Product5" );
      Assert::AreEqual( L{ 1, 0 }, L{ 1 << 16, 1 << 16 } * L{ 1 << 16, 1 << 16 }, L"Product6" );
    }

    TEST_METHOD( RandomSums )
    {
      std::default_random_engine e;

      for( size_t i = 0; i < 2000; ++i )
      {
        const L A{ e(), e() };
        const L B{ e(), e() };

        Assert::AreEqual( toi64( A ) + toi64( B ), toi64( A + B ), ( L"Random Sum #" + std::to_wstring( i ) ).c_str() );
        Assert::AreEqual( toi64( A ) - toi64( B ), toi64( A - B ), ( L"Random Difference #" + std::to_wstring( i ) ).c_str() );
      }
    }


    TEST_METHOD( RandomProds )
    {
      std::default_random_engine e;

      for( size_t i = 0; i < 2000; ++i )
      {
        const L A{ e(), e() };
        const L B{ e(), e() };

        Assert::AreEqual( toi64( A ) * toi64( B ), toi64( A * B ), ( L"Random Product #" + std::to_wstring( i ) ).c_str() );
      }
    }


    TEST_METHOD( RandomMults )
    {
      std::default_random_engine e;

      for( size_t i = 0; i < 2000; ++i )
      {
        const L A{ e(), e() };
        const L B{ e(), e() };

        Assert::AreEqual( A * B, reinterpret_cast<const L&>( Math_NS::mul( A, B ) ), ( L"Random Product #" + std::to_wstring( i ) ).c_str() );
      }
    }
  };
}