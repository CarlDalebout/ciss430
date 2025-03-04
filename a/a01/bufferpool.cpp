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
  if(pagenumber*framesize_ > filesize_-framesize_)
  {
    std::cout << "!!!!Error Outside of filesize!!!!";
    return;
  }
  unsigned char buff[frames_];
  int size;

  for(int i = 0; i <= frames_; ++i)
    buff[i] = frame[i];

  lseek(file, pagenumber*framesize_, SEEK_SET);
  write(file, buff, framesize_);
}

std::string BufferPool::getPage(int file, int pagenumber)
{
  if(pagenumber*framesize_ > filesize_-framesize_)
  {
    std::cout << "!!!!Error Outside of filesize!!!!";
    return "";
  }

  unsigned char buff[frames_];
  int size;

  lseek(file, pagenumber*framesize_, SEEK_SET);

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

    while(option > 2 || option < 0) // Checking if user picked one of the options
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
        
        bool flag = false;  // flag to check if the requested page has been placed in a frame

        for(int i = 0; i < frames_; i++)
        {
          if(frameBuffer_[i].page_number == 0 && frameBuffer_[i].page == "") // if a frame is empty
          {
            flag = true;
            frameBuffer_[i].page = getPage(file_, pagenumber);
            frameBuffer_[i].page_number = pagenumber;
            break;
          }
          else if (pagenumber == frameBuffer_[i].page_number)
          {
            flag = true;
            std::cout << "page " << pagenumber << " is already fetched ... frame id is " << i << std::endl;
            break;
          }
        }
        if(!flag)
        {
          int frame_number;
          std::cout << "which frame to remove?: ";  
          std::cin  >> frame_number;

          while(frame_number > frames_-1 || frame_number < 0)
          {
            std::cout << "please give me a value between 0 and " << frames_-1  << ": ";
            std::cin >> frame_number;
          }
          
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
          break;
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
        close(file_);
      }
      break;
    };
  }
}