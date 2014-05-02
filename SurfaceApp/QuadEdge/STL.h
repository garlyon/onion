#pragma once


#include "Shape.h"
#include "Grid.h"
#include "QuadEdgeAPI.h"


namespace STL_NS
{
  QUADEDGE_API Math_NS::BoxD box( const char* i_fileName );

  QUADEDGE_API void read( const char* i_fileName, Shape_NS::Shape&, const Math_NS::Grid& );

  QUADEDGE_API void write( const char* i_fileName, const Shape_NS::Shape&, const Math_NS::Grid& );
}