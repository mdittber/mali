#include <iostream>
#include <fstream>
#include <map>
#include <string>
// #include <typeid>
#include <unordered_map>

#include "../git/mali/v1/timer.hpp"
#include "../git/mali/v1/progress_bar.hpp"

template<class T, class key, class value>
void statistics(T mappings) {

    if(typeid(mappings) == typeid(std::unordered_map<key, value>)) {
        std::cout << "mappings.buckets() " << mappings.buckets() << std::endl;
        std::cout << "mappings.bucket_count() " << mappings.bucket_count() << std::endl;
    } else if(typeid(mappings) == typeid(std::map<key, value>)) {
        std::cout << "mappings.size() " << mappings.size() << std::endl;
    }
}

int main(int argc, char **argv) {

    // ProgressBar progress_m(1439355);
    std::unordered_map<std::string, unsigned int> umappings;
    std::map<std::string, unsigned int> mappings;

    bool run_um = false;
    std::string filename;
    if(argc < 2) {
        std::cout << argv[0] << " filename" << std::endl;
        return(0);
    } else {
        filename = argv[1];
    }
    if(argc == 3) {
        run_um = true;
    }

    std::ofstream fout;
    std::ifstream fin(filename);
    if(!fin.good()) {
        std::cout << filename << " could not be opened." << std::endl;
        return(0);
    }

    std::string word;
    Timer t;

    if(run_um) {
        typename std::map<std::string, unsigned int> Map;

        t.start();
        while(!fin.eof()) {
            fin >> word;
            mappings[word]++;
            // progress_m.update();
        }
        t.stop();
        std::cout << "Time elapsed to map " << filename << ": "
                << t.elapsed() << t.unit() << std::endl;

        std::cout << "sizeof(mappings): " << sizeof(mappings) << std::endl;

        std::cout << "mappings.size() " << mappings.size() << std::endl;
        // statistics<Map, std::string, unsigned int>(mappings);

        fout.open("mappings.txt");
        for(auto &e: mappings) {
            fout << e.first << " " << e.second << std::endl;
        }
        fout.close();
    } else {
        fin.clear();
        fin.seekg(0, std::ios::beg);

        // ProgressBar progress_um(1439355);
        t.start();
        while(!fin.eof()) {
            fin >> word;
            umappings[word]++;
            // progress_um.update();
        }
        t.stop();
        std::cout << "Time elapsed to map " << filename << ": "
                << t.elapsed() << t.unit() << std::endl;

        std::cout << "sizeof(umappings): " << sizeof(umappings) << std::endl;

        std::cout << "umappings.size() " << umappings.size() << std::endl;

        fout.open("umappings.txt");
        for(auto &e: umappings) {
            fout << e.first << " " << e.second << std::endl;
        }
        fout.close();
    }

        std::string input;
        std::cin  >> input;

    fin.close();
    return(0);
}