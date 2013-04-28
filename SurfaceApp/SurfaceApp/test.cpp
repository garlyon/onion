#include "stdafx.h"

#include "..\QuadEdge\Test.h"

namespace Test_NS
{
  bool myTestFunc()
  {
    QuadEdge_NS::test();

    return true;
  }

  bool val = myTestFunc();
}