#pragma once

typedef unsigned long long uint64;

namespace zen {
    struct ECSEntity {
        friend class ECSController;
        ECSEntity() : m_key(0), m_handle(0), m_alive(true) {}
        ECSEntity(uint64 Key, unsigned int handle) : m_key(Key), m_handle(handle), m_alive(true) {}
        ECSEntity(ECSEntity& e) {
            m_key = e.m_key;
            type = e.type;
            m_handle = e.m_handle;
            m_alive = e.m_alive;
        }

        bool isAlive() {
            return m_alive;
        }

        unsigned int component(unsigned int index) {
            return m_componentHandles[index];
        }
        uint64 key() {
            return m_key;
        }

        uint8_t type : 7; /* Padding data, can be used if you want */

    private:
        bool m_alive : 1;
        uint64 m_key;
        unsigned int m_handle;
        unsigned int m_componentHandles[0];
    };
}