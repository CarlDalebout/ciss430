#ifndef BUFFERPOOL_H
#define BUFFERPOOL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include <cstring>


struct FRAME
{
  bool dirty = false;
  int page_number = 0;
  std::string page = "";
};

class BufferPool
{
  public:
    BufferPool(const char* filename, int filesize = 20, int framesize = 4, int frames = 3)
    :file_(open(filename, O_RDWR)), filesize_(filesize), framesize_(framesize), frames_(frames),
     frameBuffer_(std::vector<FRAME>(frames_))
    {
      if (file_ < 0)
      {
      std::cout << "open fail\n";
      std::cout << "errno: " << errno << std::endl;
      std::cout << "strerror: " << strerror(errno) << std::endl;
      }
      else
      {
      std::cout << "open ok" << std::endl;
      }
    }
    ~BufferPool()
    {
      std::cout << "closed file_\n";
      close(file_);
    }

    //setters
    std::string& operator [](int index) { return frameBuffer_[index].page; } // setter
    void setFrameSize(int size) { framesize_ = size; }
    void resize(int n);
    void writePage(int file, int pagenumber, std::string frame);

    //getters
    const std::string& operator [](int index) const { return frameBuffer_[index].page; } // getter
    int getFrameSize() {  return framesize_; }
    int size()         {  return frames_; }
    std::string getPage(int file, int pagenumber);

    void run();

  private:
    
    int file_;
    int filesize_;
    int framesize_;
    int frames_;
    std::vector<FRAME> frameBuffer_;
};

#endif