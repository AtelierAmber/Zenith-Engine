#include "Logging/Logger.h"

#include <fstream>

#define LOG_FILE "system.log"

namespace Zenith {

    void Log::refresh() {
        std::fstream logFile;
        logFile.open(LOG_FILE, std::ios::out | std::ios::trunc);
        logFile << "[Logging started]\n\n";
        logFile.close();
    }

    void Log::logEvent(std::string report) {
        std::fstream logFile;
        logFile.open(LOG_FILE, std::ios::out | std::ios::app);
        logFile << "[Event]   -> " << report << "\n";
        logFile.close();
    }

    void Log::logError(std::string report) {
        std::fstream logFile;
        logFile.open(LOG_FILE, std::ios::out | std::ios::app);
        logFile << "[Error]   -> " << report << "\n";
        logFile.close();
    }

    void Log::logWarning(std::string report) {
        std::fstream logFile;
        logFile.open(LOG_FILE, std::ios::out | std::ios::app);
        logFile << "[Warning] -> " << report << "\n";
        logFile.close();
    }
}