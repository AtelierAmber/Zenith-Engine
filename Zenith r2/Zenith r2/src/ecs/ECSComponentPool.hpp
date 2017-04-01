#pragma once
#include "util/ZVector.hpp"

typedef unsigned long long uint64;

namespace zen {
    class ECSComponentPool {
        friend class ECSController;
    public:
        ECSComponentPool(uint64 id, std::size_t componentSize, bool virt = false) :
            m_compid(id), m_components(componentSize), m_virtual(virt) { }

        ~ECSComponentPool() {
            m_components.clear();
        }
        unsigned int size() { return m_components.size(); }

        void clear() {
            m_components.clear();
        }

        unsigned int addPtr(void* data) {
            return m_components.addPtr(data);
        }

        template<typename T>
        unsigned int add(T t) {
            return m_components.add(t);
        }

        template<typename T>
        T* get(unsigned int i) {
            return m_components.get<T>(i);
        }
        void* operator[](unsigned int i) {
            return m_components[i];
        }

        void remove(unsigned int i) {
            m_components.remove(i);
        }

        ECSComponentPool& operator-=(unsigned int i) {
            m_components.remove(i);
            return *this;
        }

        bool isVirtual() {
            return m_virtual;
        }

    private:
        bool m_virtual = false;
        uint64 m_compid = 0;
        ZSparse m_components;
    };
}