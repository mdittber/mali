#ifndef FILE_HPP
#define FILE_HPP

#include <exception>
#include <fstream>
#include <iostream>
#include <math.h>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "../timer.hpp"

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
                        tmp = mSize/pow(2,(i+1)*10);
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

        void split(unsigned int num_chunks) {
            Timer t;
            t.start();
            unsigned int orig_pos = mFile.tellg();
            mFile.seekg(0, std::ios::end);
            unsigned int end = mFile.tellg();
            mFile.seekg(orig_pos, std::ios::beg);
            std::vector<unsigned int> indices(num_chunks);
            unsigned int offset = end/num_chunks;
            unsigned int from = 0;
            unsigned int to   = offset;
            std::vector<std::thread> mThreads;
            // Use a thread pool instead e.g. what if num_chunks > num of hardware threads?
            for(int i=0; i<num_chunks; i++) {
                mThreads.emplace_back([=](){
                    write_chunk(from, to, i+1);
                });
                
                from = to;
                to   = to + offset;
                if(to > end) {
                    to = end;
                }
            }
            for(auto &t: mThreads) {
                if(t.joinable()) {
                    t.join();
                }
            }
            t.stop();
            double throughput = double(size()) / t.elapsed() * 1000;
            std::cout << "Through put: " << throughput << " " << mUnit << "/s" << std::endl;
        }


    private:
        std::string mFilename;
        std::fstream mFile;
        std::mutex mutex_file_operation;
        double mSize = -1;
        std::string mUnit = "bytes";

        void fast_copy(unsigned int from, uint to, uint chunk_id) {
            std::ifstream file("myfile", std::ios::binary | std::ios::ate);
            std::streamsize size = file.tellg();
            file.seekg(0, std::ios::beg);

            std::vector<char> buffer(size);
            if (file.read(buffer.data(), size)) {

            }
        }

        void write_chunk(unsigned int from, uint to, uint chunk_id) {
            std::unique_lock<std::mutex> ulock(mutex_file_operation);
            ulock.unlock();
            std::string filename = mFilename + "." + std::to_string(chunk_id);
            File fin(mFilename);
            std::ofstream fout(filename);
            std::cout << "Processing chunk " << chunk_id << " ..." << std::endl;
            // uint orig = mFile.tellg();
            char ch;
            fin.mFile.seekg(from, std::ios::beg);
            for(int i=from; i<to; i++) {
                // ulock.lock();
                // mFile.seekg(i,std::ios::beg);
                ch = char(fin.mFile.get());
                // ulock.unlock();
                fout.put(ch);
            }
            fout.close();
        }

};

#endif