#pragma once

#include <string>

namespace Zenith {
    class Log {
    public:
        static void     refresh();
        static void     logEvent(std::string report);
        static void     logError(std::string report);
        static void     logWarning(std::string report);
    };
}