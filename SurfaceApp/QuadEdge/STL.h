#pragma once


#include "Shape.h"
#include "Grid.h"


namespace STL_NS
{
  Math_NS::BoxD box( const char* i_fileName );

  void read( const char* i_fileName, Shape_NS::Shape&, const Math_NS::Grid& );

  void write( const char* i_fileName, const Shape_NS::Shape&, const Math_NS::Grid& );
}