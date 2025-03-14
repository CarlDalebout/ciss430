#include "bufferpool.h"

// BufferPool
void BufferPool::resize(int n)
{
  std::vector<FRAME>ret (n);
  for(int i = 0; i < frames_; ++i)
  {
    ret[i] = frameBuffer_[i];
  }
  frames_ = n;
}

void BufferPool::writePage(int file, int pagenumber, std::string frame)
{
  unsigned char buff[frames_];
  int size;

  for(int i = 0; i <= frames_; ++i)
    buff[i] = frame[i];

  lseek(file, pagenumber*4, SEEK_SET);
  write(file, buff, framesize_);
}

std::string BufferPool::getPage(int file, int pagenumber)
{
  unsigned char buff[frames_];
  int size;

  lseek(file, pagenumber*4, SEEK_SET);

  size = read(file, buff, framesize_);
  // std::cout << size << ", "<< buff  << std::endl;
  std::string ret;
  for(int i = 0; i < size; i++)
    ret.insert(ret.end(), buff[i]); 
  return ret;
}

void BufferPool::run()
{
  int option = 0;
  int pagenumber = -1;
  while(option != 2)
  {
    std::cout << "\n[0] Fetch a page into memory\n"
              << "[1] Write frame\n"
              << "[2] Shutdown\n"
              << "[3] Print LRU\n"
              << "Frames:";
    for (int i = 0; i < frames_; i++)
    {
      std::cout << "[";

      if(frameBuffer_[i].page_number == 0 && frameBuffer_[i].page == "")  // if a frame is empty
      {
        std::cout << frameBuffer_[i].page << "]";
      }
      else 
      {
        if (!frameBuffer_[i].dirty)
          std::cout << frameBuffer_[i].page_number << ':' << frameBuffer_[i].page << ']';
        else if (frameBuffer_[i].dirty)
          std::cout << '*' << frameBuffer_[i].page_number << ':' << frameBuffer_[i].page << ']';
      }
    }
    std::cout << std::endl;
    std::cout << "option: ";
    std::cin  >> option;

    while(option > 3 || option < 0) // Checking if user picked one of the options
    {
      std::cout << "please give me an option between 0 and 2\n";
      std::cout << "option: ";
      std::cin  >> option;
    }

    switch(option)
    {
      case 0:
      {
        std::cout << "which page?: ";
        std::cin  >> pagenumber;
        
        int LRU_Status = updateLRU(pagenumber);
        
        if(LRU_Status > -1) // the buffer is full and we need to replace the LRU page
        {
          int frame_number;
          for(int i = 0; i< frames_; ++i)
          {
            if(LRU_Status == frameBuffer_[i].page_number)
              frame_number = i;
          }
          std::cout << "LRU: frame " << LRU_Status << " is selected as victim\n";
          if(frameBuffer_[frame_number].dirty)
          {
            std::cout << "frame " << frame_number << " is dirty ... write to block " << frameBuffer_[frame_number].page_number << std::endl;
            writePage(file_, frameBuffer_[frame_number].page_number, frameBuffer_[frame_number].page);
            frameBuffer_[frame_number].dirty = false;
          }
          else 
          {
            std::cout << "frame " << frame_number << " is not dirty ... no write" << std::endl;
          }
          frameBuffer_[frame_number].page = getPage(file_, pagenumber);
          frameBuffer_[frame_number].page_number = pagenumber;
        }
        else if(LRU_Status == -1) // The buffer has room
        {
          for(int i = 0; i < frames_; i++)
          {
            if(frameBuffer_[i].page_number == 0 && frameBuffer_[i].page == "") // if a frame is empty
            {
              frameBuffer_[i].page = getPage(file_, pagenumber);
              frameBuffer_[i].page_number = pagenumber;
              break;
            }
          }
        }
        else // The same page is called that is already in the buffer
        {
          for(int i = 0; i< frames_; ++i)
          {
            if(pagenumber == frameBuffer_[i].page_number)
              std::cout << "page " << pagenumber << " is already fetched ... frame id is " << i << std::endl;
          }
        }
      }
      break;
      
      //==========================================================================================
      // Write Frame
      //==========================================================================================
      case 1:
      {
        std::string newFrame_;

        std::cout << "which page?: ";
        std::cin  >> pagenumber;

        std::cout << "enter 4 characters: ";
        std::cin  >> newFrame_;

        bool flag = false;  // flag to check if the requested page has been placed in a frame

        for(int i = 0; i < frames_; i++)
        {
          if(frameBuffer_[i].page_number == pagenumber)
          {
            frameBuffer_[i].dirty = true;
            frameBuffer_[i].page_number = pagenumber;
            frameBuffer_[i].page = newFrame_;
          }
        }
      }
      break;

      case 2:
      {
        for(int i = 0; i < frames_; ++i)
        {
          if (frameBuffer_[i].dirty)
          {
            std::cout << "frame " << i << " is dirty ... write to block " << frameBuffer_[i].page_number << std::endl;
            writePage(file_, frameBuffer_[i].page_number, frameBuffer_[i].page);
            frameBuffer_[i].dirty = false;
          }
        }
      }
      break;

      case 3:
      {
        printLRU();
      }
      break;
    };
  }
}

int BufferPool::updateLRU(int pagenumber)
{
  LRU_.insert(LRU_.begin(), pagenumber);

  for(int i = 1; i < LRU_.size(); ++i) // 0, 1, 2, 3, 0, 5, 4
  {
    if(LRU_[i] == pagenumber)
      {
        LRU_.erase(LRU_.begin()+i);
        return -2;
      }
  }
  if(LRU_.size() > frames_)
  {
    int ret = LRU_.back();
    LRU_.pop_back();
    return ret;
  }
  return -1;
}

void BufferPool::printLRU()
{
  std::string dir = "";
  std::cout << '[';
  for(int i = 0; i < LRU_.size(); ++i)
  {
    std::cout << dir << LRU_[i]; dir = ", ";
  }
  std::cout << ']' << std::endl;
}