#pragma once
#include <string>

namespace Zenith {
    enum class LogType {
        ERROR,
        WARNING,
        EVENT,
    };

    class Logger {
    public:
        Logger();
        Logger(std::string logFile) { construct(logFile, "SYS"); }

        void construct(std::string logFile, std::string logOrigin = "NONE");
        void log(LogType type, const std::string& report, int code = 0);
    private:
        std::string m_origin;
        std::string m_logFile;
    };
}