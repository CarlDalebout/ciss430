#include <iostream>
#include <fstream>
#include <string>
#include <vector>



class BufferPool
{
  public:
    BufferPool(std::string file, int framesize = 4, int frames = 3)
    :file_(file, std::ios::in | std::ios::out),framesize_(framesize), frames_(frames), option_(-1), pageNumber_(-1), newFrame_(""),
     frameBuffer_(std::vector<std::string>(frames_)), 
     fetchedFrames_(std::vector<int>(frames_))
    {
      fill( fetchedFrames_.begin(), fetchedFrames_.end(), -1);
      std::cout << fetchedFrames_[0] << std::endl;
      return;
    }

    void run()
    {
      while(option_ != 2)
      {
        std::cout << "[0] Fetch a page into memory\n"
                  << "[1] Write frame\n"
                  << "[2] Shutdown\n"
                  << "Frames:";
        for (int i = 0; i < frames_; i++)
        {
          std::cout << "[";

          if(fetchedFrames_[i] == -1)
          {
            std::cout << frameBuffer_[i] << "]";
          }
          else 
          {
            std::cout << fetchedFrames_[i] << " : " << frameBuffer_[i] << "]";
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
              if(fetchedFrames_[i] == -1) // if a fram is empty
              {
                std::string temp = "";
                for(int i = 0; i < pageNumber_ * framesize_; i++) // for loop to move the coursor where it needs to be
                  file_.get();
                //   std::cout << (char)file_.get() << std::endl;
                for(int i = 0; i < framesize_; i++)
                {
                  char j = file_.get();
                  temp.insert(temp.end(), j);
                }
                flag = true;
                frameBuffer_[i] = temp;
                fetchedFrames_[i] = pageNumber_;
                break;
              }
              else if (pageNumber_ == fetchedFrames_[i])
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
                std::cout << "please give me a value between 0 and " << frames_  << ": ";
                std::cin >> frame_number;
              }

              std::string temp = "";
              for(int i = 0; i < pageNumber_ * framesize_; i++) // for loop to move the coursor where it needs to be
                file_.get();
              //   std::cout << (char)file_.get() << std::endl;
              for(int i = 0; i < framesize_; i++)
              {
                char j = file_.get();
                temp.insert(temp.end(), j);
              }
              flag = true;
              frameBuffer_[frame_number] = temp;
              fetchedFrames_[frame_number] = pageNumber_;
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
          }
          break;
        };
      }
    }

    //setters
    std::string& operator [](int index) { return frameBuffer_[index]; } // setter
    void setFrameSize(int size) { framesize_ = size; }
    // int setFrameSize(int n) { framesize_ = size; }

    //getters
    const std::string& operator [](int index) const { return frameBuffer_[index]; } // getter
    int getFrameSize() {  return framesize_; }
    int getFrames()    {  return frames_; }
  
  private:
  std::fstream file_;
  int framesize_; // in bytes
  int frames_;
  int option_;
  int pageNumber_;
  std::string newFrame_;
  
  std::vector<std::string> frameBuffer_;
  std::vector<int> fetchedFrames_; 
};
 
int main()
{
  // std::string read;
  // std::string temp = "cccc";
  // if(file.is_open())
  // {
  //   for(int i = 0; i < 8; i++)
  //     std::cout << (char)file.get() << std::endl;
  //   for(int i = 0; i < 4; i++)
  //   {
  //     char j = file.get();
  //     read.insert(read.end(), j);
  //     std::cout << read << std::endl;
  //   }
  //   for(int i = 0; i < 4; ++i)
  //     file.seekp((file.tellp() - static_cast<std::streampos>(1)));
  //   for(int i = 0; i < 4; ++i)
  //   {
  //     file.put(temp[i]);
  //     std::cout << temp[i] << std::endl;
  //   }
  //   file.close();
  // }
  // else
  //   std::cout << "failed to open file\n";
  

  BufferPool buffer("abc.txt");
  buffer.run();

  return 0;
}