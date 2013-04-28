#include "stdafx.h"

namespace Test_NS
{
  class A
  {
    A* ptr;

  public:

    A() : ptr( this )
    {
    }
  };

  void f()
  {
    A a;
  }
}