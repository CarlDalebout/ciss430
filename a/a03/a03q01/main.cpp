#include <iostream>
#include <string>
#include "bufferpool.h"


 
int main()
{
  std::string file = "abc.txt";
  const char* filename = file.c_str();
  BufferPool2 buffer(filename);
  
  buffer.run();
  
  return 0;
}