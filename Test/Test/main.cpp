#include <iostream>
#include <vector>

std::ostream& sayHello( std::ostream& io_str )
{
  return io_str << "Hello, Git Hub!" << std::endl;
}

class E
{
  E* p;

public:

  E() : p( this )
  {
  }
};

void main()
{
  E e;

  sayHello( std::cout );

  std::cout << sizeof( std::vector<E>::iterator ) << std::endl;
  std::cout << sizeof( E* ) << std::endl;
  std::cout << sizeof( size_t ) << std::endl;
  std::cout << sizeof( int ) << std::endl;
}