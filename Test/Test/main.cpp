#include <iostream>

std::ostream& sayHello( std::ostream& io_str )
{
  return io_str << "Hello, Git Hub!" << std::endl;
}

void main()
{
  sayHello( std::cout );
}