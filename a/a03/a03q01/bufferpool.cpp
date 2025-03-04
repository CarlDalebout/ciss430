#include "bufferpool.h"

void BufferPool::resize(int n)
{
  std::vector<FRAME>ret;
  for(int i = 0; i < frames_; ++i)
  {
    ret.push_back(frameBuffer_[i]);
  }
  while (ret.size() < n)
  {
    ret.push_back(FRAME());
  }
  frames_ = n;
  frameBuffer_ = ret;
  return;
}

void BufferPool::writePage(int pagenumber, std::string frame)
{

}

std::string BufferPool::getPage(int pagenumber)
{
  std::string temp = "";
  file_.seekg(0, std::ios::beg); // reset the corser to the start
  
  for(int i = 0; i < pageNumber_ * framesize_; i++) // for loop to move the coursor where it needs to be
    file_.get();

  for(int i = 0; i < framesize_; i++)
  {
    char j = file_.get();
    temp.insert(temp.end(), j);
  }

  return temp;
}

void BufferPool::run()
{
  while(option_ != 2)
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
    std::cin  >> option_;

    while(option_ > 2 || option_ < 0) // Checking if user picked one of the options
    {
      std::cout << "please give me an option between 0 and 2\n";
      std::cout << "option: ";
      std::cin  >> option_;
    }

    switch(option_)
    {
      case 0:
      {
        std::cout << "which page?: ";
        std::cin  >> pageNumber_;
        
        file_.seekg(0, std::ios::beg); // reset the corser to the start

        bool flag = false;  // flag to check if the requested page has been placed in a frame

        for(int i = 0; i < frames_; i++)
        {
          if(frameBuffer_[i].page_number == 0 && frameBuffer_[i].page == "") // if a frame is empty
          {
            flag = true;
            frameBuffer_[i].page = getPage(pageNumber_);
            frameBuffer_[i].page_number = pageNumber_;
            break;
          }
          else if (pageNumber_ == frameBuffer_[i].page_number)
          {
            flag = true;
            std::cout << "page " << pageNumber_ << " is already fetched ... frame id is " << i << std::endl;
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

          flag = true;
          frameBuffer_[frame_number].page = getPage(pageNumber_);
          frameBuffer_[frame_number].page_number = pageNumber_;
          break;
        }
        
      }
      break;
      
      case 1:
      {
        std::cout << "which page?: ";
        std::cin  >> pageNumber_;

        std::cout << "enter 4 characters: ";
        std::cin  >> newFrame_;
        for(int i = 0; i < frames_; i++)
        {
          if(frameBuffer_[i].page_number == pageNumber_)
          {
            frameBuffer_[i].dirty = true;
            frameBuffer_[i].page_number = pageNumber_;
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

          }
        }
      }
      break;
    };
  }
}


// BufferPool2
void BufferPool2::resize(int n)
{
  std::vector<FRAME>ret (n);
  for(int i = 0; i < frames_; ++i)
  {
    ret[i] = frameBuffer_[i];
  }
  frames_ = n;
}

void BufferPool2::writePage(int file, int pagenumber, std::string frame)
{
  unsigned char buff[frames_];
  int size;

  for(int i = 0; i < frames_; ++i)
    buff[i] = frame[i];

  lseek(file, pagenumber*4, SEEK_SET);
  write(file, buff, framesize_);
}

std::string BufferPool2::getPage(int file, int pagenumber)
{
  unsigned char buff[frames_];
  int size;

  lseek(file, pagenumber*4, SEEK_SET);

  size = read(file, buff, framesize_);
  std::cout << size << ", "<< buff  << std::endl;
  std::string ret;
  for(int i = 0; i < size; i++)
    ret.insert(ret.end(), buff[i]); 
  return ret;
}

void BufferPool2::run()
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

          flag = true;
          frameBuffer_[frame_number].page = getPage(file_, pagenumber);
          frameBuffer_[frame_number].page_number = pagenumber;
          break;
        }
        
      }
      break;
      
      case 1:
      {
        std::string newFrame_;

        std::cout << "which page?: ";
        std::cin  >> pagenumber;

        std::cout << "enter 4 characters: ";
        std::cin  >> newFrame_;
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

          }
        }
      }
      break;
    };
  }
}