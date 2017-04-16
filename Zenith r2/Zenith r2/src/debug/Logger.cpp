#include "debug/Logger.hpp"
#include <ctime>

int abs(int val) { return (val < 0)? -val : val; }

namespace zen {
    std::vector<unsigned int> Log::sm_codeRecord;
    LogSettings Log::sm_settings = LogSetting::ALL;
    const char* Log::sm_logFile = "debugLog.log";

    void Log::setSettings(LogSettings settings) {
        Log::sm_settings = settings;
    }

    void Log::enableSetting(LogSettings setting) {
        Log::sm_settings |= setting;
    }

    void Log::disableSetting(LogSettings setting) {
        Log::sm_settings &= ~setting;
    }

    void Log::setLogFile(const char* path, bool clear /*= true*/) {
        Log::sm_logFile = path;
        if (clear) {
            Log::clear();
        }
    }

    void Log::exportDate(std::fstream& file, bool showDate, bool showTime) {
        std::time_t tNow = std::time(0);
        std::tm now;
        localtime_s(&now, &tNow);
        std::tm utc;
        gmtime_s(&utc, &tNow);
        if (showDate) {
            file << "[";
            if (now.tm_mon < 9) {
                file << "0" << 1 + now.tm_mon;
            }
            else {
                file << 1 + now.tm_mon;
            }
            if (now.tm_mday < 10) {
                file << "/0" << now.tm_mday;
            }
            else {
                file << "/" << now.tm_mday;
            }
            file << "/" << 1900 + now.tm_year << " - ";
        }
        if (showTime) {
            int timedif = (now.tm_hour - utc.tm_hour);
            if(abs(timedif) >= 12) {
                timedif = 0;
                if(now.tm_hour > utc.tm_hour) {
                    timedif += 24 - now.tm_hour;
                    timedif += utc.tm_hour;
                } else {
                    timedif += 24 - utc.tm_hour;
                    timedif += now.tm_hour;
                }
            }
            file << "<GMT " << (now.tm_hour - utc.tm_hour)-25 << ">";
            if (now.tm_hour < 10) {
                file << "0" << now.tm_hour;
            }
            else {
                file << now.tm_hour;
            }
            if (now.tm_min < 10) {
                file << ":0" << now.tm_min;
            }
            else {
                file << ":" << now.tm_min;
            }
            if (now.tm_sec < 10) {
                file << ":0" << now.tm_sec << "] ";
            }
            else {
                file << ":" << now.tm_sec << "] ";
            }
        }
    }

    void Log::clear() {
        if (Log::sm_settings & LogSetting::ENABLED) {
            std::fstream file;
            file.open(Log::sm_logFile, std::ios::out | std::ios::trunc);
            if (file.fail()) {
                std::printf("COULD NOT OPEN LOG FILE! Are all required directories created? %s", Log::sm_logFile);
                return;
            }
            file << "Logging started at ";
            exportDate(file, true, true);
            file.close();
        }
        else {
            std::printf("Log has not been enabled, original file not cleared.\n");
        }
    }

    unsigned int Log::NextCode() {
        unsigned int lowest = 0;
        for (int i = 0; i < Log::sm_codeRecord.size(); ++i) {
            if (lowest == Log::sm_codeRecord[i]) {
                i = 0;
                ++lowest;
            }
        }
        return lowest;
    }

    void Log::refreshRepetitives() {
        Log::sm_codeRecord.clear();
    }

    void Log::DateTime(bool Inline) {
        std::fstream file;
        file.open(Log::sm_logFile, std::ios::out | std::ios::app);
        if (file.fail()) {
            std::printf("COULD NOT OPEN LOG FILE! Are all required directories created? %s", Log::sm_logFile);
            return;
        }
        if(!Inline) {
            file << "\nDate: ";
        }
        exportDate(file, true, true);
        file.close();
    }
}