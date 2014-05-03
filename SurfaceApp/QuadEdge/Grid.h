#pragma once


#include "Box.h"
#include "QuadEdgeAPI.h"


namespace Math_NS
{
  class QUADEDGE_API Grid
  {
    BoxD v; //  vector box
    BoxI i; //  index box

  public:

    Grid( const BoxD& vectorVolume, const BoxI& indexVolume = BoxI{
      VectorI{ std::numeric_limits<I>::lowest(), std::numeric_limits<I>::lowest(), std::numeric_limits<I>::lowest() },
      VectorI{ std::numeric_limits<I>::max(), std::numeric_limits<I>::max(), std::numeric_limits<I>::max() }
    } ) : v{ vectorVolume }, i{ indexVolume } {}

    //  vector to index
    const VectorI operator() ( const VectorD& ) const;

    //  index to vector
    const VectorD operator() ( const VectorI& ) const;
  };
}