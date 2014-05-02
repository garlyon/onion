#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\QuadEdge\Rational.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


using R = Math_NS::R;


template <>
std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString( const R& v ){ return std::to_wstring( v.n ) + std::wstring{ L'/' } +std::to_wstring( v.d ); }


namespace UnitTests
{
  TEST_CLASS( Rational )
  {
  public:

    TEST_METHOD( Direct )
    {
      Assert::AreEqual( R{ 1, 2 }, R{ 2, 4 }, L"Equality" );

      Assert::AreEqual( R{ 14, 15 }, R{ 2, 3 } * R{ 7, 5 }, L"Product" );
      Assert::AreEqual( R{ 14, 15 }, R{ 2, 3 } / R{ 5, 7 }, L"Ratio" );

      Assert::AreEqual( R{ 7, 6 }, R{ 1, 2 } + R{ 2, 3 }, L"Sum" );
      Assert::AreEqual( R{ 1, 6 }, R{ 1, 2 } - R{ 1, 3 }, L"Difference" );

      Assert::AreEqual( R{ -5, 7 }, -R{ 5, 7 }, L"Negate" );

      Assert::IsFalse( R{ 2, 3 } != R{ 2, 3 }, L"Non Equality" );
    }

    TEST_METHOD( Simplified )
    {
      auto same = []( const R& l, const R& r ) -> bool { return l.n == r.n && l.d == r.d; };

      Assert::IsTrue( same( R{ 2, 5 }, R{ 2, 7 } * R{ 7, 5 } ), L"Simplified Product 1" );
      Assert::IsTrue( same( R{ 2, 5 }, R{ 7, 5 } * R{ 2, 7 } ), L"Simplified Product 2" );

      Assert::IsTrue( same( R{ 2, 5 }, R{ 2, 7 } / R{ 5, 7 } ), L"Simplified Ratio 1" );
      Assert::IsTrue( same( R{ 2, 5 }, R{ 7, 5 } / R{ 7, 2 } ), L"Simplified Ratio 2" );

      Assert::IsTrue( same( R{ 5, 7 }, R{ 2, 7 } + R{ 3, 7 } ), L"Simplified Sum" );
      Assert::IsTrue( same( R{ 2, 7 }, R{ 5, 7 } - R{ 3, 7 } ), L"Simplified Difference" );
    }
  };
}