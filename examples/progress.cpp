#include <iostream>
#include <chrono>
#include <thread>
#include "../progress_bar.hpp"


int main(int argc, char **argv) {
    std::cout  << "cout"  << std::endl;
    int N = 10;
    if(argc == 2) N = std::stoi(argv[1]);
    ProgressBar progress(N);
    for(int i=0; i<N; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds( long( double(10000)/double(N) ) ));
        progress.update();
    }
    return(0);
}