#pragma once
typedef unsigned long long uint64;

/* Interface wrapper around id */

namespace zen {
    namespace ecs {
    struct Component {
        unsigned int entityHandle;
    };
    }
}