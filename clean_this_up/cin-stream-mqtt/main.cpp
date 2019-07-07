#include <iostream>
#include <string>

int main() {

    char ch;
    std::string msg;
    for(int i=0; i<10; i++) {
        // ch = std::cin.get();
        std::cin.get(ch);
        msg += ch;
        std::cout << "(" << i << ")";
    }
    std::cout << std::endl;
    std::cout << "msg: " << msg << std::endl;
    return(0);
}