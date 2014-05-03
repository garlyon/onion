#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\QuadEdge\Vector.h"
#include "..\QuadEdge\Box.h"
#include "..\QuadEdge\Rational.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


using V = Math_NS::VectorI;
using B = Math_NS::BoxI;
using R = Math_NS::R;


template <> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString( const Math_NS::I& v )
{
  return std::to_wstring( v );
}

template <> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString( const V& v )
{
  return L"( " + std::to_wstring( v.x ) + L", " + std::to_wstring( v.y ) + L", " + std::to_wstring( v.z ) + L" )";
}

template <> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString( const B& v )
{
  return ToString( v.min ) + L" ~ " + ToString( v.max );
}

template <> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString( const R& v )
{
  return std::to_wstring( v.n ) + L'/' +std::to_wstring( v.d );
}


namespace UnitTests
{
  TEST_CLASS( Math )
  {
  public:

    TEST_METHOD( Vector )
    {
      Assert::AreEqual( V{ 1, 2, 3 }, V{ 1, 2, 3 }, L"Equality" );
      Assert::AreEqual( V{ 7, 7, 7 }, V{ 1, 2, 3 } + V{ 6, 5, 4 }, L"Sum" );
      Assert::AreEqual( V{ 5, 3, 1 }, V{ 6, 5, 4 } - V{ 1, 2, 3 }, L"Difference" );
      Assert::AreEqual( 1LL, V{ 1, 0, 1 } * V{ 0, 1, 1 }, L"Scalar Product" );
      Assert::AreEqual( 1LL * V{ 2, 4, 6 }, V{ 1, 2, 3 } *2LL, L"Multiplication" );
      Assert::AreEqual( V{ 1, 2, 3 }, V{ 2, 4, 6 } / 2LL, L"Division" );
      Assert::AreEqual( V{ 0, 0, 1 }, V{ 1, 0, 0 } ^ V{ 0, 1, 0 }, L"Vector Product" );
      Assert::AreEqual( V{}, V{ 1, 2, 3 } + -V{ 1, 2, 3 }, L"Negation" );
      Assert::AreEqual( 25LL, V{ 3, 0, 4 }.lengthSqr(), L"LengthSqr" );
    }

    TEST_METHOD( Box )
    {
      Assert::IsTrue( B{}.empty(), L"Empty" );
      Assert::IsFalse( B{ V{}, V{} }.empty(), L"NonEmpty Point" );
      Assert::IsFalse( B{ V{}, V{ 1, 1, 1 } }.empty(), L"NonEmpty Volume" );
      Assert::AreEqual( B{ V{ 0, 0, 0 }, V{ 3, 3, 3 } }, B{ V{ 0, 0, 0 }, V{ 3, 3, 3 } } + B{ V{ 1, 1, 1 }, V{ 2, 2, 2 } }, L"Internal Sum" );
      Assert::AreEqual( B{ V{ 0, 0, 0 }, V{ 3, 3, 3 } }, B{ V{ 0, 0, 0 }, V{ 2, 2, 2 } } + B{ V{ 1, 1, 1 }, V{ 3, 3, 3 } }, L"Overlaping Sum" );
      Assert::AreEqual( B{ V{ 0, 0, 0 }, V{ 3, 3, 3 } }, B{ V{ 0, 0, 0 }, V{ 1, 1, 1 } } + B{ V{ 2, 2, 2 }, V{ 3, 3, 3 } }, L"External Sum" );
    }

    TEST_METHOD( RationalDirect )
    {
      Assert::AreEqual( R{ 1, 2 }, R{ 2, 4 }, L"Equality" );

      Assert::AreEqual( R{ 14, 15 }, R{ 2, 3 } * R{ 7, 5 }, L"Product" );
      Assert::AreEqual( R{ 14, 15 }, R{ 2, 3 } / R{ 5, 7 }, L"Ratio" );

      Assert::AreEqual( R{ 7, 6 }, R{ 1, 2 } + R{ 2, 3 }, L"Sum" );
      Assert::AreEqual( R{ 1, 6 }, R{ 1, 2 } - R{ 1, 3 }, L"Difference" );

      Assert::AreEqual( R{ -5, 7 }, -R{ 5, 7 }, L"Negate" );

      Assert::IsFalse( R{ 2, 3 } != R{ 2, 3 }, L"Non Equality" );
    }

    TEST_METHOD( RationalSmart )
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