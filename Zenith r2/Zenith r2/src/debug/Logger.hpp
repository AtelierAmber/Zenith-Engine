#pragma once
#include <vector>
#include <fstream>

namespace zen {
    enum class LogMajorType {
        ERROR,
        WARNING,
        EVENT,
        GENERAL
    };

    typedef const char* LogMinorType;
    struct LogType {
        LogType(LogMajorType Maj = LogMajorType::GENERAL, LogMinorType min = "") : major(Maj), minor(min) {}
        LogMajorType major;
        LogMinorType minor;
    };

    typedef unsigned int LogSettings;
    enum LogSetting {
        ENABLED = 0b1,
        SHOW_DATE = 0b10,
        SHOW_TIME = 0b100,
        SHOW_WARNINGS = 0b1000,
        SHOW_EVENTS = 0b10000,
        SHOW_MINOR_TYPE = 0b100000,
        SHOW_MAJOR_TYPE = 0b1000000,
        ALL = 0b1111111
    };

    class Log {
    public:

        /*! \brief Set the log settings.
         *  
         *  Overwrites the current log settings
         *  \public 
         *  \static 
         *  \param[in] LogSettings settings
         *  \retval void
         */
        static void setSettings(LogSettings settings);
        /*! \brief Enables a single setting or multiple settings OR'ed together.
         *  
         *  Will not overwrite previous settings
         *  \public 
         *  \static 
         *  \param[in] LogSettings setting
         *  \retval void
         */
        static void enableSetting(LogSettings setting);
        /*! \brief Disables a single setting or multiple settings OR'ed together.
         *  
         *  Will not overwrite previous settings
         *  \public 
         *  \static 
         *  \param[in] LogSettings setting
         *  \retval void
         */
        static void disableSetting(LogSettings setting);
        /*! \brief Sets the log file to path.
         *  
         *  Sets the new log file path and if clear is set to true will clear the
         *  file and marks the log start date and time
         *  \public 
         *  \static 
         *  \param[in] const char * path
         *  \param[in] bool clear
         *  \retval void
         */
        static void setLogFile(const char* path, bool clear = true);
        /*! \brief Clear the log file.
         *  
         *  Clears the log file and marks the log start date and time
         *  \public 
         *  \static 
         *  \retval void
         */
        static void clear();

        /*! \brief Main logging function.
         *  
         *  Will log with 
         *  \see LogType
         *  \public 
         *  \static 
         *  \param[in] LogType type
         *  \param[in] Args... args
         *  \retval void
         */
        template<typename... Args>
        static void Debug(LogType type, Args... args) {
            if (Log::sm_settings & LogSetting::ENABLED) {
                if (!(Log::sm_settings & LogSetting::SHOW_WARNINGS) &&
                    type.major == LogMajorType::WARNING) {
                    return;
                }
                if (!(Log::sm_settings & LogSetting::SHOW_EVENTS) &&
                    type.major == LogMajorType::EVENT) {
                    return;
                }
                std::fstream file;
                file.open(Log::sm_logFile, std::ios::out | std::ios::app);
                if (file.fail()) {
                    std::printf("COULD NOT OPEN LOG FILE! Are all required directories created? %s", Log::sm_logFile);
                    return;
                }
                file << '\n';
                if (Log::sm_settings & LogSetting::SHOW_DATE ||
                    Log::sm_settings & LogSetting::SHOW_TIME) {
                    exportDate(file,
                        (Log::sm_settings & LogSetting::SHOW_DATE) != 0,
                        (Log::sm_settings & LogSetting::SHOW_TIME) != 0);
                }
                if (Log::sm_settings & LogSetting::SHOW_MAJOR_TYPE ||
                    Log::sm_settings & LogSetting::SHOW_MINOR_TYPE) {
                    if (Log::sm_settings & LogSetting::SHOW_MAJOR_TYPE) {
                        switch (type.major) {
                        case LogMajorType::ERROR:
                            file << "ERROR   -> ";
                            break;
                        case LogMajorType::WARNING:
                            file << "Warning -> ";
                            break;
                        case LogMajorType::EVENT:
                            file << "Event   -> ";
                            break;
                        case LogMajorType::GENERAL:
                            file << "           ";
                            break;
                        }
                    }
                    if (Log::sm_settings & LogSetting::SHOW_MINOR_TYPE && type.minor != "") {
                        file << "[" << type.minor << "] ";
                    }
                }
                logReport(file, args...);
                file.close();
            }
        }

        /*! \brief Repetitive.
         *  
         *  Description
         *  \public 
         *  \static 
         *  \param[in] LogType type
         *  \param[in] unsigned int code
         *  \param[in] Args... args
         *  \retval void
         */
        template<typename... Args>
        static void Repetitive(LogType type, unsigned int code, Args... args) {
            if (Log::sm_settings & LogSetting::ENABLED) {
                for (auto& recCode : Log::sm_codeRecord) {
                    if (recCode == code) {
                        return;
                    }
                }
                Log::Debug(type, args...);
                Log::sm_codeRecord.emplace_back(code);
            }
        }
        
        /*! \brief NextCode.
         *  
         *  Description
         *  \public 
         *  \static 
         *  \retval unsigned int
         */
        static unsigned int NextCode();
        /*! \brief refreshRepetitives.
         *  
         *  Description
         *  \public 
         *  \static 
         *  \retval void
         */
        static void refreshRepetitives();

        /*! \brief Date.
         *  
         *  Logs the current Date 
         *  \public 
         *  \static 
         *  \retval void
         */
        static void DateTime();

    private:

        template<typename T, typename... Args>
        static void logReport(std::fstream& file, T t, Args... args) {
            file << t;
            logReport(file, args...);
        }
        template<typename T>
        static void logReport(std::fstream& file, T t) {
            file << t;
        }
        static void logReport(std::fstream& file) {}

        static void exportDate(std::fstream& file, bool showDate, bool showTime);

        static std::vector<unsigned int> sm_codeRecord;
        static LogSettings sm_settings;
        static const char* sm_logFile;
    };
}