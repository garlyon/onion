#pragma once


#include "Box.h"


namespace Math_NS
{
  class Grid
  {
    BoxD v; //  vector box
    BoxI i; //  index box

  public:

    Grid( const BoxD& vectorVolume, const BoxI& indexVolume ) : v{ vectorVolume }, i{ indexVolume } {}

    const VectorD operator() ( const VectorI& ) const;
    const VectorI operator() ( const VectorD& ) const;
  };
}