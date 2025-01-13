#include <iostream>
#include "bufferpool.h"


 
int main()
{
  BufferPool buffer("abc.txt");
  buffer.run();

  return 0;
}