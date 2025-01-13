#include "bufferpool.h"

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