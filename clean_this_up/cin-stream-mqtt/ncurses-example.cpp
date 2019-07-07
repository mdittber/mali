#include <curses.h>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

struct Clock {

    Clock(): m_write(true) {}
    bool m_write;

    static void countdown(int N, bool &m_write) {
        for(int i=N; i>=0; i--) {
            std::cout << "i = " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        m_write = true;
    }

    bool write() {
        if(m_write) {
            std::cout << "Write to file." << std::endl;
            m_write = false;
            std::thread t(countdown, 3, std::ref(m_write));
            t.detach();
            return(true);
        } else {
            return(false);
        }
    }

};

/*
void countdown(int N) {
    std::ofstream fout("countdown.txt");
    fout << "Countdown" << std::endl;
    for(int i=N; i>=0; i--) {
        std::cout << i << " ... ";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        fout << i << " ... " << std::endl;
    }
    fout << std::endl;
    std::cout << std::endl;
    fout.close();
}
*/

int main(int argc, char **argv) {
    initscr();
    cbreak();

    // std::thread t(countdown, 10);

    std::string msg = "";
    char ch;
    Clock c;

    std::ofstream fout("test.txt");

    printw("press any key to exit...\n");
    for(int i=0; i<10; i++) {
        ch = getch();
        msg += ch;
        if(c.write()) {
            fout << msg << std::endl;
            msg = "";
        }
        // update();
    }

    fout << msg << std::endl;

    fout.close();
    // t.join();
    endwin();
    return 0;
}