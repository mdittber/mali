#ifndef LOG_HPP
#define LOG_HPP

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <string>
#include <sstream>

#define debug(x) __debug(x, "[Debug]   ", __FILE__, __FUNCTION__, __LINE__)
#define error(x) __error(x, "[Error]   ", __FILE__, __FUNCTION__, __LINE__)
#define info(x)  __info(x,  "[Info]    ", __FILE__, __FUNCTION__, __LINE__)
#define warn(x)  __warn(x,  "[Warning] ", __FILE__, __FUNCTION__, __LINE__)

namespace fs = std::filesystem;

class Log {
    public:
        enum level {no, error, warn, info, debug};

        Log(std::string filename, level file = level::warn, level console = level::warn);
        ~Log();

        void __debug(std::string msg, const char *type, const char *file, const char *fun, const int line);
        void __error(std::string msg, const char *type, const char *file, const char *fun, const int line);
        void __info(std::string msg, const char *type, const char *file, const char *fun, const int line);
        void __warn(std::string msg, const char *type, const char *file, const char *fun, const int line);

        void set_level(level l);
        void set_file_level(level l);
        void set_console_level(level l);

    private:
        std::ofstream fout;
        std::string mFilename;
        level mConsoleLevel, mFileLevel;

        std::mutex mutex_ofstream;

        static std::string timestamp();
        void log(std::string msg, Log::level l, const char *type, const char *file, const char *fun, const int line);
        std::string get_alternative_filename(std::string filename);
        void print_log_level(level l);

};

#endif