#include "Logger.h"

#include <fstream>

namespace Zenith {
    Logger::Logger() {}

    void Logger::construct(std::string logFile, std::string origin /*="NONE"*/) {
        m_logFile = "./Logs/" + logFile;
        std::fstream file;
        if (!m_constructed) {
            file.open(m_logFile, std::ios::out | std::ios::trunc);
        }
        else {
            file.open(m_logFile, std::ios::out | std::ios::app);
        }
        if (file.fail()) {
            std::printf("COULD NOT OPEN LOG FILE : %s", logFile.c_str());
            return;
        }
        file << "[Logging started from " + origin + "]\n\n";
        file.close();
        m_constructed = true;
    }

    void Logger::log(const std::string& origin, LogType type, const std::string& report, int code /*=0*/) {
        std::fstream logFile;
        logFile.open(m_logFile, std::ios::out | std::ios::app);
        switch (type) {
        case LogType::ERROR:
            logFile << "\n[ERROR:" << origin << "]   -> " << report;
            break;
        case LogType::WARNING:
            logFile << "\n[WARNING:" << origin << "] -> " << report;
            break;
        case LogType::EVENT:
            logFile << "\n[Event:" << origin << "]   -> " << report;
            break;
        default:
            break;
        }
        if (code) {
            logFile << "\n\tLog Code : " << std::to_string(code);
        }
        logFile.close();
    }
}