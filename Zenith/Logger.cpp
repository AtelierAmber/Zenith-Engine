#include "Logger.h"

#include <fstream>

namespace Zenith {
    Logger::Logger() {}

    void Logger::construct(std::string logFile, std::string LogOrigin /*="NONE"*/) {
        m_logFile = "./Logs/" + logFile;
        m_origin = LogOrigin;
        std::fstream file;
        file.open(m_logFile, std::ios::out | std::ios::trunc);
        if (file.fail()) {
            std::printf("COULD NOT OPEN LOG FILE : %s", logFile.c_str());
            return;
        }
        file << "[Logging started from " + LogOrigin + "]\n\n";
        file.close();
    }

    void Logger::log(LogType type, const std::string& report, int code /*=0*/) {
        std::fstream logFile;
        logFile.open(m_logFile, std::ios::out | std::ios::app);
        switch (type) {
        case LogType::ERROR:
            logFile << "\n[ERROR:" << m_origin << "]   -> " << report;
            break;
        case LogType::WARNING:
            logFile << "\n[WARNING:" << m_origin << "] -> " << report;
            break;
        case LogType::EVENT:
            logFile << "\n[Event:" << m_origin << "]   -> " << report;
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