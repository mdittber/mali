#ifndef TIMER_HPP
#define TIMER_HPP

#include <iostream>
#include <string>
#include <chrono>
#include <typeinfo>

template<class Resolution = std::chrono::milliseconds>
class Timer {
    public:
        Timer() {
            std::cout << "Timer constructor" << std::endl;
        }

        ~Timer() {
            std::cout << "Timer destructor" << std::endl;
        }

        void start() {
            std::cout << "tic" << std::endl;
            mStart = std::chrono::high_resolution_clock::now();
        }

        void stop() {
            mStop = std::chrono::high_resolution_clock::now();
            std::cout << "toc" << std::endl;
        }

        bool is_steady() {
            return(std::chrono::high_resolution_clock::is_steady);
        }

        std::string get_timestamp() {
            std::chrono::time_point sctp = std::chrono::system_clock::now();
            std::time_t tt = std::chrono::system_clock::to_time_t(sctp);
            auto t = localtime(&tt);
            std::string timestamp = std::put_time(t, "%Y-%m-%d %T %Z");
            return(timestamp);
        }

        long long int elapsed() {
            auto mElapsed = std::chrono::duration_cast<Resolution>(mStop-mStart).count();
            return(mElapsed);
        }

        std::string unit() {
            std::string mUnit;
            if(typeid(Resolution) == typeid(std::chrono::nanoseconds)) {
                mUnit = "(ns)";
            } else if (typeid(Resolution) == typeid(std::chrono::microseconds)) {
                mUnit = "(µs)";
            } else if(typeid(Resolution) == typeid(std::chrono::milliseconds)) {
                mUnit = "(ms)";
            } else if(typeid(Resolution) == typeid(std::chrono::seconds)) {
                mUnit = "(s)";
            } else {
                mUnit = "<unknown>";
            }
            
            return(mUnit);
        }

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> mStart, mStop;

};

#endif