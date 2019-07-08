#include <curses.h>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <exception>

std::mutex mutex_wait, mutex_input;
std::condition_variable cv;

struct TimedBuffer {

    unsigned int __wait_secs;
    std::string &__msg;
    std::string __filename;
    std::ofstream __fout;
    bool __run = true;
    std::thread __t;

    TimedBuffer(std::string &msg, unsigned int wait_secs = 3): __msg(msg), __wait_secs(wait_secs) {
        __filename = "test.txt";
        __fout.open(__filename);
        if(!__fout.good()) {
            std::cout << "Error opening file " << __filename << std::endl;
        } else {
            __fout << "Buffer:" << std::endl;
            __t = std::thread(TimedBuffer::countdown, std::ref(__run), std::ref(__wait_secs), std::ref(__msg), std::ref(__fout));
        }
    }

    ~TimedBuffer() {
        std::cout << "Destructor called" << std::endl;
        __run = false;
        cv.notify_all();
        if(__t.joinable()) {
            std::cout << "Joining thread ... " << std::endl;
            __t.join();
            std::cout << "done." << std::endl;
        }
        std::cout << "Closing " << __filename << " ... ";
        __fout.close();
        std::cout << "done." << std::endl;
    }

    static void countdown(bool &__run, unsigned int &__wait_secs, std::string &__msg, std::ofstream &__fout) {
        std::cout << "Started thread with buffer time " << __wait_secs << std::endl;
        unsigned int i;
        std::cv_status status;
        while(__run) {
            std::unique_lock<std::mutex> ul(mutex_wait);
            for(i=__wait_secs; i>0; i--) {
                status = cv.wait_for(ul, std::chrono::seconds(1));
                if(!__run) {
                    i = 1;
                    write(__msg, __fout);
                } else {
                    if(i == 1 && status == std::cv_status::timeout) {
                        write(__msg, __fout);
                    }
                    if(__run && status == std::cv_status::no_timeout) {
                        i = __wait_secs;
                    }
                }
            }
        }
    }

    static void write(std::string &__msg, std::ofstream &__fout) {
        std::unique_lock<std::mutex> ul(mutex_input);
        if(__msg.size() > 0) {
            __fout << __msg << std::endl;
            __msg = "";
        }
    }
};

int main(int argc, char **argv) {
    try {

        initscr();
        cbreak();

        std::string msg = "";
        char ch;

        TimedBuffer c(msg);

        printw("press any key to exit...\n");
        std::unique_lock<std::mutex> ul_input(mutex_input);
        ul_input.unlock();

        for(int i=0; i<10; i++) {
            ch = getch();
            ul_input.lock();
            msg += ch;
            ul_input.unlock();
            cv.notify_all();
        }
        endwin();

    } catch(const std::exception &e) {
        std::ofstream log("log.txt");
        log << e.what() << std::endl;
        log.close();
    }
    return 0;
}