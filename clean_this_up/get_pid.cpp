#include<iostream>
#include<fstream>
#include<sys/types.h>
#include<unistd.h>
#include<chrono>
#include<thread>

void get_pid() {
	std::ofstream fout("test.txt");
	fout << "Open" << std::endl;
	std::cout << "DEBUG: accessfile() called by process "
						<< ::getpid() << " (parent: " << ::getppid()
						<< ")" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(10));
	fout << "Thread" << std::endl;
	fout.close();
}

void thread_pid() {
	std::cout << "this is the thread" << std::endl;
	get_pid();
}

int main() {
	std::thread t(thread_pid);
	t.detach();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "Exiting" << std::endl;
	return(0);
}
