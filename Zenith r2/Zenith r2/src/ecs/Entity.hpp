#pragma once
#include <unordered_map>

typedef unsigned long long uint64;

namespace zen {
    namespace ecs {
    class Entity {
        friend class Manager;
    protected:
        void removeComponentKey(uint64 key) {
            m_key &= ~key;
            m_componentMap.erase(key);
        }
        void addComponentKey(uint64 key, unsigned int) { m_key &= key; }

        uint64 m_key;
        unsigned int m_id;
        /* Maps component keys with their vector index */
        std::unordered_map<uint64, unsigned int> m_componentMap;
    };
    }
}