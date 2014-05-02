#include "Grid.h"


const Math_NS::VectorD Math_NS::Grid::operator() ( const VectorI& p ) const
{
  return
  {
    v.min.x + ( static_cast<VectorD::type>( p.x - i.min.x ) / ( i.max.x - i.min.x ) ) * ( v.max.x - v.min.x ),
    v.min.y + ( static_cast<VectorD::type>( p.y - i.min.y ) / ( i.max.y - i.min.y ) ) * ( v.max.y - v.min.y ),
    v.min.z + ( static_cast<VectorD::type>( p.z - i.min.z ) / ( i.max.z - i.min.z ) ) * ( v.max.z - v.min.z )
  };
}


const Math_NS::VectorI Math_NS::Grid::operator() ( const VectorD& p ) const
{
  return
  {
    i.min.x + static_cast<VectorI::type>( std::round( ( ( p.x - v.min.x ) / ( v.max.x - v.min.x ) ) * ( i.max.x - i.min.x ) ) ),
    i.min.y + static_cast<VectorI::type>( std::round( ( ( p.y - v.min.y ) / ( v.max.y - v.min.y ) ) * ( i.max.y - i.min.y ) ) ),
    i.min.z + static_cast<VectorI::type>( std::round( ( ( p.z - v.min.z ) / ( v.max.z - v.min.z ) ) * ( i.max.z - i.min.z ) ) )
  };
}