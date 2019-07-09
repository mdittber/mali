#ifndef FILE_HPP
#define FILE_HPP

#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>

class File {
    public:
        File(std::string filename): mFilename(filename) {
            mFile.open(mFilename);
            if(!mFile.good()) {
                throw mFilename + " could not be opened.";
            }
            std::cout << mFilename << " opened." << std::endl;
        }

        ~File() {
            if(mFile.good()) {
                std::lock_guard<std::mutex> lock_file_operation(mutex_file_operation);
                if(mFile.good()) {
                    mFile.close();
                    std::cout << mFilename << " closed." << std::endl;
                }
            }
        }

        double size() {
            if(mSize == -1) {
                unsigned int orig_pos = mFile.tellg();
                mFile.seekg(0, std::ios::end);
                mSize = mFile.tellg();
                mFile.seekg(orig_pos, std::ios::beg);
                int i=0;
                double tmp = mSize;
                for(i=0; i<=4; i++) {
                    if(tmp >= 1024) {
                        tmp = mSize/std::pow(2,(i+1)*10);
                    } else {
                        break;
                    }
                }
                mSize = tmp;
                switch (i)
                {
                case 0:
                    mUnit = "bytes";
                    break;
                case 1:
                    mUnit = "KB";
                    break; 
                case 2:
                    mUnit = "MB";
                    break;
                case 3:
                    mUnit = "GB";
                    break;
                case 4:
                    mUnit = "TB";
                    break;
                default:
                    mUnit = "unknwon";
                    break;
                }
            }
            return(mSize);
        }

        std::string unit() {
            return(mUnit);
        }


    private:
        std::string mFilename;
        std::fstream mFile;
        std::mutex mutex_file_operation;
        double mSize = -1;
        std::string mUnit = "bytes";


};

#endif