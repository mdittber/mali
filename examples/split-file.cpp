#include <iostream>
#include <fstream>
#include <map>
#include <string>
// #include <typeid>
#include <unordered_map>

#include "../git/mali/v1/timer.hpp"
#include "../git/mali/v1/progress_bar.hpp"
#include "../git/mali/v1/thread_safe/file.hpp"

int main(int argc, char **argv) {

    try {

        std::string filename;
        if(argc < 2) {
            std::cout << argv[0] << " filename" << std::endl;
            return(0);
        } else {
            filename = argv[1];
        }

        int num_chunks = 2;
        if(argc == 3) {
            num_chunks = std::stoi(argv[2]);
        }

        std::ifstream fin(filename);
        if(!fin.good()) {
            std::cout << filename << " could not be opened." << std::endl;
            return(0);
        }

        fin.clear();
        fin.seekg(0, std::ios::beg);
        int start = fin.tellg();
        fin.seekg(0, std::ios::end);
        int end   = fin.tellg();
        int size  = end-start;


        std::cout << "File size: " << (end-start) << std::endl;

        fin.close();

        File f(filename);
        std::cout << "Size: " << f.size() << " (" << f.unit() << ")" << std::endl;

        f.split(num_chunks);

    } catch(std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return(0);
}