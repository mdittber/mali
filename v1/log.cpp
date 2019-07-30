#include "log.hpp"

void Log::set_console_level(level l) {
    mConsoleLevel = l;
    std::cout << "Console log level changed to: ";
    print_log_level(mConsoleLevel);
}

Log::Log(std::string filename, level file, level console):
    mFilename(filename), mFileLevel(file), mConsoleLevel(console) {

    if(fs::exists(mFilename)) {
        std::cout << "[Warning] file '" << mFilename << "' already exists. ";
        mFilename = get_alternative_filename(mFilename);
        std::cout << mFilename << " will be used instead.\n";
    }

    fout.open(mFilename);
    if(!fout.good()) {
        std::cout << "Log file '" << mFilename << "' could not be opened.\n";
    }

}

void Log::__debug(std::string msg, const char *type, const char *file, const char *fun, const int line) {
    log(msg, Log::level::debug, type, file, fun, line);
}

void Log::__error(std::string msg, const char *type, const char *file, const char *fun, const int line) {
    log(msg, Log::level::error, type, file, fun, line);
}

void Log::__info(std::string msg, const char *type, const char *file, const char *fun, const int line) {
    log(msg, Log::level::info, type, file, fun, line);
}

void Log::__warn(std::string msg, const char *type, const char *file, const char *fun, const int line) {
    log(msg, Log::level::warn, type, file, fun, line);
}

Log::~Log() {
    std::cout << "Log file " << mFilename << " closed.\n";
    fout.close();
}

void Log::set_level(level l) {
    set_file_level(l);
    set_console_level(l);
}

void Log::set_file_level(level l) {
    mFileLevel = l;
    std::cout << "Log file level for '" << mFilename << "' changed to: ";
    print_log_level(mFileLevel);
}

std::string Log::timestamp() {
    std::stringstream ts;
    auto now              = std::chrono::system_clock::now();
    std::time_t now_c     = std::chrono::system_clock::to_time_t(now);
    ts << std::put_time(std::localtime(&now_c), "%F %T") << ' ';
    return(ts.str());
}

void Log::log(std::string msg, Log::level l, const char *type, const char *file, const char *fun, const int line) {
    std::lock_guard<std::mutex> lock_ofstream(mutex_ofstream);
    if(mFileLevel    >= l) fout      << timestamp() << type << file << "(" << fun << ":" << line << ") | " << msg << "\n";
    if(mConsoleLevel >= l) std::cout << timestamp() << type << file << "(" << fun << ":" << line << ") | " << msg << "\n";
}

std::string Log::get_alternative_filename(std::string filename) {
    std::string alternative_filename = filename;
    int i = 1;
    while(fs::exists(alternative_filename)) {
        alternative_filename = filename + '.' + std::to_string(i);
        i++;
    }
    return(alternative_filename);
}

void Log::print_log_level(level l) {
    switch (l) {

        case level::debug:
            std::cout << "debug\n";
            break;

        case level::error:
            std::cout << "error\n";
            break;

        case level::info:
            std::cout << "info\n";
            break;

        case level::no:
            std::cout << "no\n";
            break;

        case level::warn:
            std::cout << "warn\n";
            break;

        default:
            break;
    }
}