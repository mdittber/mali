#include<iostream>
#include<sys/types.h>
#include<unistd.h>
#include<chrono>
#include<thread>

int main() {
   std::cout << "DEBUG: accessfile() called by process "
             << ::getpid() << " (parent: " << ::getppid()
             << ")" << std::endl;
   constexpr unsigned int secs = 5;
   std::cout << "Sleeping for " << secs << " seconds. Exit afterwards." << std::endl;
   std::this_thread::sleep_for(std::chrono::seconds(secs));
   return(0);
}
