#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\QuadEdge\STL.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
  TEST_CLASS( STL )
  {
  public:

    TEST_METHOD( RearWrite )
    {
      Math_NS::Grid g = STL_NS::box( "../test.stl" );

      Shape_NS::Shape s;

      STL_NS::read( "../test.stl", s, g );

      Assert::AreEqual<size_t>( s.verts().size(), 9, L"Verts number" );
      Assert::AreEqual<size_t>( s.faces().size(), 14, L"Faces number" );
      Assert::AreEqual<size_t>( s.prims().size(), 21, L"Prims number" );
      Assert::AreEqual<size_t>( s.duals().size(), 21, L"Duals number" );

      STL_NS::write( "../out.stl", s, g );

      Shape_NS::Shape t;

      STL_NS::read( "../out.stl", t, g );

      Assert::AreEqual( s.verts().size(), t.verts().size(), L"Verts number" );
      Assert::AreEqual( s.faces().size(), t.faces().size(), L"Faces number" );
      Assert::AreEqual( s.prims().size(), t.prims().size(), L"Prims number" );
      Assert::AreEqual( s.duals().size(), t.duals().size(), L"Duals number" );
    }

  };
}