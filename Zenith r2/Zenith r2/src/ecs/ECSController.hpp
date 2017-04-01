#pragma once
#include <functional>

#include "ECSComponentPool.hpp"
#include "ECSEntity.hpp"

namespace zen {
    struct SystemRef {
        SystemRef(uint64 Key,
                  std::function<void(unsigned int, uint8_t)> Insert,
                  std::function<void(unsigned int, uint8_t)> Remove) :
            key(Key), addEntity(Insert), remEntity(Remove){ }
        uint64 key;
        std::function<void(unsigned int, uint8_t)> addEntity;
        std::function<void(unsigned int, uint8_t)> remEntity;
    };

    /* Modifies entity components */
    struct EntityModifier {
        EntityModifier(int modifier, unsigned int handle, uint64 ID,
                       std::function<unsigned int()> funcAdd = nullptr) : 
            mod((Modifier)modifier), entityHandle(handle), componentID(ID), dataAdd(funcAdd) {}
        enum Modifier{
            ADD, REMOVE
        } mod;
        unsigned int entityHandle;
        uint64 componentID;
        std::function<unsigned int()> dataAdd;
    };

    class ECSController {
    public:
        ECSController() {}

        /* Core */
        template<typename T>
        uint64 registerComponent() { return registerComponent(sizeof(T)); }
        uint64 registerComponent(std::size_t size);

        void registerSystem(std::function<void(unsigned int, uint8_t)> insertion, 
                            std::function<void(unsigned int, uint8_t)> removal, 
                            uint64 key, const char* name = "<No name specified>");

        void finalize();
        void clear();
        void dispose();

        void update();

        /* Entity */
        unsigned int createEntity(uint8_t type = 0);

        void removeEntity(unsigned int entityHandle);
        void removeEntity(ECSEntity* entity);

        ECSEntity* getEntity(unsigned int entityHandle);

        bool entityHas(unsigned int entityHandle, uint64 id);
        bool entityHas(ECSEntity* entity, uint64 id);
        
        /* Component */
        template<typename C>
        C* getComponentFrom(ECSEntity* entity, uint64 id) {
            if(!m_initialized) {
                std::printf("Cannot get component before ecs initialization!");
                return nullptr;
            }

            unsigned int poolNum = idtoind(id);
            ECSComponentPool* pool = &m_componentPools[poolNum];
            if(!entityHas(entity->m_handle, id) || pool->isVirtual()) {
                return nullptr;
            }
            return pool->get<C>(entity->component(poolNum));
        }
        template<typename C>
        C* getComponentFrom(unsigned int entityHandle, uint64 id) {
            return getComponentFrom<C>(m_entities.get<ECSEntity>(entityHandle), id);
        }
        void* getComponentFrom(unsigned int entityHandle, uint64 id);
        void* getComponentFrom(ECSEntity* entity, uint64 id);

        template<typename C>
        void addComponentTo(ECSEntity* entity, uint64 id, C c) {
            if(!m_initialized) {
                std::printf("Cannot add component before ecs initialization!");
                return;
            }

            if(entity->isAlive()) {
                m_eModQueue.emplace_back(EntityModifier::ADD, entity->m_handle, id);
                unsigned int index = idtoind(id);
                if(!(m_componentPools[index].isVirtual())) {
                    m_eModQueue.back().dataAdd = [this, index, c]() { return m_componentPools[index].add(c); };
                }
            }
        }
        template<typename C>
        void addComponentTo(unsigned int entityHandle, uint64 id, C c) {
            addComponentTo<C>(m_entities.get<ECSEntity>(entityHandle), id, c);
        }
        void addComponentTo(ECSEntity* entity, uint64 id, void* data);
        void addComponentTo(unsigned int entityHandle, uint64 id, void* data);

        void remComponentFrom(ECSEntity* entity, uint64 id);
        void remComponentFrom(unsigned int entityHandle, uint64 id);

    private:
        /* Core */
        bool m_initialized = false;
        int idtoind(uint64_t n);
        bool m_clearEntities = false;

        /* Entity */
        std::vector<unsigned int> m_eRemQueue;
        ZSparse m_entities;

        /* Component */
        unsigned int m_numComponents = 0;
        std::vector<ECSComponentPool> m_componentPools;
        std::vector<EntityModifier> m_eModQueue;

        /* Systems */
        std::vector<SystemRef> m_systems;
    };
}