#include<iostream>

int main(int argc, char **argv) {

	std::cout << "Your PATH is: " << std::getenv("PATH") << std::endl;
	std::cout << "USER is: " << std::getenv("USER") << std::endl;
	return(0);
}

