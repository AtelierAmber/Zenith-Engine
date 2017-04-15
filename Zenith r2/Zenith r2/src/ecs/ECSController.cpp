#include <iostream>

#include "ECSController.hpp"
#include "debug/Logger.hpp"

namespace zen {
    uint64 ECSController::registerComponent(std::size_t size) {
        if(m_initialized) {
            std::printf("Cannot add components after ecs finalization!");
            return -1;
        }
        uint64 key = (1ULL << m_numComponents);
        if(size == 0) {
            m_componentPools.emplace_back(key, size, true);
            Log::Debug({LogMajorType::EVENT, "ecs"}, "Registered virtual component ", m_numComponents);
        } else {
            m_componentPools.emplace_back(key, size);
            Log::Debug({LogMajorType::EVENT, "ecs"}, "Registered component ", m_numComponents, " with size: ", size);
        }
        ++m_numComponents;
        return key;
    }

    void ECSController::registerSystem(std::function<void(unsigned int, uint8_t)> insertion, 
                                 std::function<void(unsigned int, uint8_t)> removal, 
                                 uint64 key, const char* name /*= "<No name specified>"*/) {
        m_systems.emplace_back(key, insertion, removal);
        Log::Debug({LogMajorType::EVENT, "ecs"}, "Registered system ", name, " [", key, "");
    }

    void ECSController::finalize() {
        std::size_t eSize = sizeof(ECSEntity) + (sizeof(unsigned int) * m_numComponents);
        m_entities = ZSparse(eSize);
        m_initialized = true;
        Log::Debug({LogMajorType::EVENT, "ecs"}, "Finalized Entity Component System with entity size: ", eSize);
    }

    void ECSController::clear() {
        m_clearEntities = true;
    }
    void ECSController::dispose() {
        m_eRemQueue.clear();
        m_entities.clear();

        m_numComponents = 0;
        m_componentPools.clear();
        m_eModQueue.clear();

        m_systems.clear();
        Log::Debug({LogMajorType::EVENT, "ecs"}, "Disposed of Entity Component System");
    }

    void ECSController::update() {
        if(!m_initialized) {
            std::printf("Cannot update ECS before initialization!");
            return;
        }

        if(m_clearEntities) {
            m_entities.clear();
            m_componentPools.clear();
            return;
        }

        struct KeyChange {
            KeyChange(unsigned int handle, uint64 key) :
                eHandle(handle), newKey(key) {}
            unsigned int eHandle;
            uint64 newKey;
        };
        std::vector<KeyChange> keyChanges;

        /* Delete entities */
        for(std::size_t i = 0; i < m_eRemQueue.size(); ++i) {
            unsigned int eHandle = m_eRemQueue[i];
            ECSEntity* e = m_entities.get<ECSEntity>(eHandle);
            for(int i = 0; i < m_numComponents; ++i) {
                uint64 id = 1 << (i + 1);
                if((e->m_key & id) == id) {
                    ECSComponentPool* pool = &m_componentPools[id];
                    pool->remove(e->m_componentHandles[i]);
                }
            }
            keyChanges.emplace_back(eHandle, 0);
            m_entities.remove(eHandle);
        }
        m_eRemQueue.clear();

        /* Add and remove components */
        for(std::size_t i = 0, dataI = 0; i < m_eModQueue.size(); ++i) {
            EntityModifier* eMod = &m_eModQueue[i];
            ECSEntity* e = m_entities.get<ECSEntity>(eMod->entityHandle);

            /* Don't modify dead entities */
            if(!e->isAlive()) {
                continue;
            }

            /* Skip modification if it would not change the entity */
            if(eMod->mod == EntityModifier::ADD && (e->m_key & eMod->componentID)) {
                continue;
            } else if(eMod->mod == EntityModifier::REMOVE && !(e->m_key & eMod->componentID)){
                continue;
            }

            KeyChange* newChange = nullptr;
            /* Use or create pattern change */
            for(auto& pc : keyChanges) {
                if(pc.eHandle == eMod->entityHandle) {
                    newChange = &pc;
                    break;
                } 
            }
            if(newChange == nullptr) {
                keyChanges.emplace_back(eMod->entityHandle, e->m_key);
                newChange = &keyChanges.back();
            }

            /* Modify pattern*/
            if(eMod->mod == EntityModifier::ADD) {
                newChange->newKey |= eMod->componentID;
                /* Check for virtual component */
                unsigned int index = idtoind(eMod->componentID);
                if(m_componentPools[index].isVirtual()) {
                    continue;
                }
                e->m_componentHandles[index] = eMod->dataAdd();
            } else {
                newChange->newKey ^= eMod->componentID;
                /* Check for virtual component */
                unsigned int index = idtoind(eMod->componentID);
                if(m_componentPools[index].isVirtual()) {
                    continue;
                }
                unsigned int cIndex = e->m_componentHandles[index];
                m_componentPools[index].remove(cIndex);
            }
        }
        m_eModQueue.clear();

        for(auto& c : keyChanges) {
            ECSEntity* e = m_entities.get<ECSEntity>(c.eHandle);

            for(auto& s : m_systems) {
                if((s.key & e->m_key) == s.key && (s.key & c.newKey) != s.key) {
                    /* Remove entity from system */
                    s.addEntity(e->m_handle, e->type);
                } else if((s.key & e->m_key) != s.key && (s.key & c.newKey) == s.key) {
                    /* Add entity to system */
                    s.remEntity(e->m_handle, e->type);
                }
            }

            e->m_key = c.newKey;
        }
    }

    unsigned int ECSController::createEntity(uint8_t type /*= 0*/) {
        if(!m_initialized) {
            std::printf("Cannot create entity before ecs initialization!");
            return -1;
        }

        unsigned int handle = m_entities.add(ECSEntity());
        ECSEntity* e = m_entities.get<ECSEntity>(handle);
        e->m_handle = handle;
        e->m_alive = true;
        e->type = type;
        return handle;
    }

    void ECSController::removeEntity(unsigned int entityHandle) {
        if(!m_initialized) {
            std::printf("Cannot remove entity before ecs initialization!");
            return;
        }

        ECSEntity* e = m_entities.get<ECSEntity>(entityHandle);
        if(e != nullptr && e->isAlive()) {
            e->m_alive = false;
            m_eRemQueue.emplace_back(entityHandle);
        }        
    }
    void ECSController::removeEntity(ECSEntity* entity) {
        removeEntity(entity->m_handle);
    }

    ECSEntity* ECSController::getEntity(unsigned int entityHandle) {
        if(!m_initialized) {
            std::printf("Cannot get entity before ecs initialization!");
            return nullptr;
        }

        ECSEntity* e = m_entities.get<ECSEntity>(entityHandle);
        return (e != nullptr && e->isAlive()) ? e : nullptr;
    }

    bool ECSController::entityHas(ECSEntity* entity, uint64 id) {
        if(!m_initialized) {
            std::printf("Cannot check entity before ecs initialization!");
            return 0;
        }

        return (entity->m_key & id) == id;
    }
    bool ECSController::entityHas(unsigned int entityHandle, uint64 id) {
        if(!m_initialized) {
            std::printf("Cannot check entity before ecs initialization!");
            return 0;
        }

        return (m_entities.get<ECSEntity>(entityHandle)->m_key & id) == id;
    }

    void* ECSController::getComponentFrom(ECSEntity* entity, uint64 id) {
        if(!m_initialized) {
            std::printf("Cannot get component before ecs initialization!");
            return nullptr;
        }

        unsigned int poolNum = idtoind(id);
        ECSComponentPool* pool = &m_componentPools[poolNum];
        if(!entityHas(entity->m_handle, id) || pool->isVirtual()) {
            return nullptr;
        }
        return (*pool)[entity->component(poolNum)];
    }
    void* ECSController::getComponentFrom(unsigned int entityHandle, uint64 id) {
        return getComponentFrom(m_entities.get<ECSEntity>(entityHandle), id);
    }

    void ECSController::addComponentTo(unsigned int entityHandle, uint64 id, void* data) {
        addComponentTo(m_entities.get<ECSEntity>(entityHandle), id, data);
    }
    void ECSController::addComponentTo(ECSEntity* entity, uint64 id, void* data) {
        if(!m_initialized) {
            std::printf("Cannot add component before ecs initialization!");
            return;
        }

        if(entity->isAlive()) {
            m_eModQueue.emplace_back(EntityModifier::ADD, entity->m_handle, id);
            if(!(m_componentPools[idtoind(id)].isVirtual())) {
                m_eModQueue.back().dataAdd = [this, id, data]() { return m_componentPools[idtoind(id)].addPtr(data); };
            }
        }

    }

    void ECSController::remComponentFrom(unsigned int entityHandle, uint64 id) {
        remComponentFrom(m_entities.get<ECSEntity>(entityHandle), id);
    }
    void ECSController::remComponentFrom(ECSEntity* entity, uint64 id) {
        if(!m_initialized) {
            std::printf("Cannot remove component before ecs initialization!");
            return;
        }
        if(entity->isAlive()) {
            m_eModQueue.emplace_back(EntityModifier::REMOVE, entity->m_handle, id);
        }
    }

    int ECSController::idtoind(uint64_t n) {
        #define S(k) if (n >= (UINT64_C(1) << k)) { i += k; n >>= k; }
        int i = -(n == 0); S(32); S(16); S(8); S(4); S(2); S(1); return i;
        #undef S
    }
}