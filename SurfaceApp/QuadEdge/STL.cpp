#include "STL.h"
#include <fstream>
#include <unordered_map>
#include "Splice.h"


Math_NS::BoxD STL_NS::box( const char* i_fileName )
{
  std::ifstream file( i_fileName, std::ifstream::binary );

  file.exceptions( std::ifstream::badbit | std::ifstream::failbit );

  file.seekg( 80 ); // header

  uint32_t nf = 0;
  file.read( reinterpret_cast<char*>( &nf ), 4 );

  Math_NS::BoxD b;

  for( uint32_t f = 0; f < nf; ++f )
  {
    float x[ 3 * 3 ];

    file.seekg( 3 * 4, std::ifstream::cur ); //  normal
    file.read( reinterpret_cast<char*>( x ), 3 * 3 * 4 );
    file.seekg( 2, std::ifstream::cur );  //  attribute

    b += Math_NS::VectorD( x[0], x[1], x[2] );
    b += Math_NS::VectorD( x[3], x[4], x[5] );
    b += Math_NS::VectorD( x[6], x[7], x[8] );
  }

  return b;
}


void STL_NS::read( const char* i_fileName, Shape_NS::Shape& s, const Math_NS::Grid& g )
{
  using VectorF = Math_NS::Vector<float>;

  //
  //  organize maping from geometrycal edge to topologycal
  //

  using Edge = std::pair<VectorF, VectorF>;

  struct Hash
  {
    static_assert( sizeof( size_t ) == sizeof( float ), "invalid hasher" );

    const size_t hash( const float x ) const          { return *reinterpret_cast<const size_t*>( &x ); }
    const size_t hash( const VectorF& v ) const       { return hash( v.x ) ^ ( hash( v.y ) << 10 ) ^ ( hash( v.z ) << 20 ); }
    const size_t hash( const Edge& e ) const          { return hash( e.first ) ^ ( hash( e.second ) << 5 ); }
    const size_t operator() ( const Edge& e ) const   { return hash( e ); }
  };

  std::unordered_map<Edge, Shape_NS::Shape::Prim*, Hash> edges;

  //  get-or-constuct edge
  auto edge = [&]( const std::pair<VectorF, VectorF>& e ) -> Shape_NS::Shape::Prim&
  {
    auto f = edges.find( std::make_pair( e.second, e.first ) );
    return ( f == edges.end() ) ? *( edges[e] = &s.makeEdge() ) : f->second->sym();
  };

  //
  //  Read the file
  //

  std::ifstream file( i_fileName, std::ifstream::binary );

  file.exceptions( std::ifstream::badbit | std::ifstream::failbit );

  file.seekg( 80 ); // header

  uint32_t nf = 0;
  file.read( reinterpret_cast<char*>( &nf ), 4 );

  //  topology information

  for( uint32_t f = 0; f < nf; ++f )
  {
    float x[ 3 * 3 ];

    file.seekg( 3 * 4, std::ifstream::cur ); //  normal
    file.read( reinterpret_cast<char*>( x ), 3 * 3 * 4 );
    file.seekg( 2, std::ifstream::cur );  //  attribute

    const VectorF a( x[0], x[1], x[2] );
    const VectorF b( x[3], x[4], x[5] );
    const VectorF c( x[6], x[7], x[8] );

    Shape_NS::Shape::Prim& ea = edge( std::make_pair( a, b ) );
    Shape_NS::Shape::Prim& eb = edge( std::make_pair( b, c ) );
    Shape_NS::Shape::Prim& ec = edge( std::make_pair( c, a ) );

    auto stitch = []( Shape_NS::Shape::Prim& x, Shape_NS::Shape::Prim& y )
    {
      if( &x.d() != &y.o() ) splice( x.sym().oPrev(), y );
    };
    
    stitch( ea, eb );
    stitch( eb, ec );
    stitch( ec, ea );
  }

  //  geometry information

  for( auto e : edges )
  {
    auto& o = e.second->o().vert;
    if( !o ) o = std::make_unique<Shape_NS::VertexI>( g( Math_NS::VectorD( e.first.first ) ) );
    
    auto& d = e.second->d().vert;
    if( !d ) d = std::make_unique<Shape_NS::VertexI>( g( Math_NS::VectorD( e.first.second ) ) );
  }
}


void STL_NS::write( const char* i_fileName, const Shape_NS::Shape& s, const Math_NS::Grid& g )
{
  std::ofstream file( i_fileName, std::ofstream::binary );

  file.exceptions( std::ofstream::badbit | std::ofstream::failbit );

  file.seekp( 80 ); //  header

  const auto faces = s.faces();

  uint32_t nf = faces.size();
  file.write( reinterpret_cast<const char*>( &nf ), 4 );

  for( auto f : faces )
  {
    const auto& va = f->r().vert;
    const auto& vb = f->oNext().r().vert;
    const auto& vc = f->oNext().oNext().r().vert;

    if( !va || !vb || !vc ) throw std::logic_error( "Shape vertex not initialized" );

    const Math_NS::VectorD a = g( va->point() );
    const Math_NS::VectorD b = g( vb->point() );
    const Math_NS::VectorD c = g( vc->point() );

    float x[ 3 * 3 ] = 
    {
      static_cast<float>( a.x ), static_cast<float>( a.y ), static_cast<float>( a.z ),
      static_cast<float>( b.x ), static_cast<float>( b.y ), static_cast<float>( b.z ),
      static_cast<float>( c.x ), static_cast<float>( c.y ), static_cast<float>( c.z )
    };

    file.seekp( 3 * 4, std::ofstream::cur );  //  normal
    file.write( reinterpret_cast<const char*>( x ), 3 * 3 * 4 );
    file.seekp( 2, std::ofstream::cur );  //  attribute
  }

  uint16_t end = 0;
  file.seekp( -2, std::ofstream::cur );
  file.write( reinterpret_cast<const char*>( &end ), 2 ); //  write explicitly last attribute to make correct file size
}