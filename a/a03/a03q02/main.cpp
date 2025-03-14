#include <iostream>
#include <string>
#include "bufferpool.h"

int main()
{
  std::string file;
  int filesize;
  int framesize;
  int frames;

  std::cin >> file;
  file += ".txt";
  std::cin >> filesize;
  std::cin >> framesize;
  std::cin >> frames;
  
  const char* filename = file.c_str();
  BufferPool buffer(filename, filesize, framesize, frames);
  
  buffer.run();
  
  return 0;
} 