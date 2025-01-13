#ifndef BUFFERPOOL_H
#define BUFFERPOOL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


struct FRAME
{
  bool dirty = false;
  int page_number = 0;
  std::string page = "";
};

class BufferPool
{
  public:
    BufferPool(std::string file, int framesize = 4, int frames = 3)
    :file_(file, std::ios::in | std::ios::out),framesize_(framesize), frames_(frames), option_(-1), pageNumber_(-1), newFrame_(""),
     frameBuffer_(std::vector<FRAME>(frames_))
    {}

    //setters
    std::string& operator [](int index) { return frameBuffer_[index].page; } // setter
    void setFrameSize(int size) { framesize_ = size; }
    // int setFrameSize(int n) { framesize_ = size; }
    void writePage(int pagenumber, std::string frame);

    //getters
    const std::string& operator [](int index) const { return frameBuffer_[index].page; } // getter
    int getFrameSize() {  return framesize_; }
    int getFrames()    {  return frames_; }
    std::string getPage(int pagenumber);

    void run();
    
  
  private:
  std::fstream file_;
  int framesize_; // in bytes
  int frames_;
  int option_;
  int pageNumber_;
  std::string newFrame_;
  
  std::vector<FRAME> frameBuffer_;
};

#endif