#pragma once
#include <vector>
#include <functional>

#include "ecs/Component.hpp"
#include "ecs/Entity.hpp"
#include "debug/Logger.hpp"

/* Holds all components and has helper functions to interface with them */
namespace zen {
    namespace ecs {
    template<typename T>
    struct ComponentPool {
        uint64 compid = 0;
        std::vector<T> components;
        T* operator[](unsigned int i) {
            if (i > components.size()) {
                return nullptr;
            }
            return components[i];
        }
        void operator-=(unsigned int i) {
            components[i] = components.back();
            components.pop_back();
        }
        void operator+=(unsigned int ei) {
            T newT;
            newT.entityHandle = ei;
            components.emplace_back(newT);
        }
    };

    class Manager {
    public:
        /* Core */
        template<typename T>
        uint64 getComponentID() {
            ComponentPool<T>& pool = getPool<T>();
            return pool.compid;
        }

        /* Entity */
        template<typename... Cs>
        Entity* addEntity() {
            m_addEntitiesQueue.emplace_back();
            /* Update Systems */
        }
        void removeEntity(unsigned int entityIndex);
        void removeEntity(Entity* entity);
        Entity* getEntity(unsigned int entityIndex) { return &m_entities[entityIndex]; }

        template<typename T>
        bool entityHas(unsigned int entityIndex) {
            uint64 id = getComponentID<T>();
            return m_entities[entityIndex].m_id & id;
        }
        template<typename T>
        bool entityHas(Entity* entity) {
            uint64 id = getComponentID<T>();
            return entity->m_id & id;
        }
        bool entityHas(unsigned int entityIndex, uint64 id) { return m_entities[entityIndex].m_id & id; }
        bool entityHas(Entity* entity, uint64 id) { return entity->m_id & id; }

        /* Component */
        template<typename T>
        T* getComponent(unsigned int index) {
            return getPool<T>()[index]; 
        }
        template<typename T>
        T* getComponentFrom(unsigned int entityIndex){
            
        }
        template<typename T>
        T* getComponentFrom(Entity* entity) {

        }

        template<typename T>
        unsigned int addComponentTo(Entity* entity) {
            /* Queue add */
        }
        template<typename T>
        unsigned int addComponentTo(unsigned int entityIndex) {
            /* Queue add */
        }

        template<typename T>
        void removeComponent(unsigned int index) {
            ComponentPool& pool = getPool<T>();
            Component* compRef = pool[index];
            if (m_entities[compRef->entityHandle].m_id & pool.compid) {
                
            }
            /* Update Systems */
        }
        template<typename T>
        void removeComponentFrom(Entity* entity) {
            if (!entityHas<T>(entity)) { return; }
            ComponentPool& pool = getPool<T>();
            entity->m_id &= ~pool.compid;
            pool -= (entity->m_componentMap[pool.compid]);
            /* Update systems */
        }

    private:
        /* Core */
        template<typename T>
        ComponentPool<T>& getPool() {
            static ComponentPool<T> pool;
            if (pool.compid == 0) {
                if (numComponents == 64) {
                    Log::Debug({LogMajorType::ERROR}, "You have hit the component count of 64!! Condense or remove components!!");
                }
                if (numComponents >= 48) {
                    Log::Debug({LogMajorType::WARNING}, "You are approaching the component cap of 64. Current component count at ", numComponents, ".");
                }
                pool.compid = (1 >> numComponents);
                ++numComponents;
            }
            return pool;
        }

        /* Entity */
        template<typename C, typename... Cs> struct AddComponents {
            static void To(Entity* entity) {
                // do whatever
                Templates<Cs...>::addComponentsTo();
            }
        };
        template<typename C> struct AddComponents<C> {
            static void To(Entity* entity) {
                entity->m_id |= getComponentID<C>();
            }
        };
        void addComponentsTo(Entity* entity) {}
        template<typename C>
        void addComponentsTo(Entity* entity) {
            entity->m_id |= getComponentID<C>();
        }
        template<typename C, typename... Cs>
        void addComponentsTo(Entity* entity) {
            entity->m_id |= getComponentID<C>();
            addComponentsTo<Cs...>()
        }

        unsigned int numComponents = 0;
        std::vector<Entity> m_entities;

        std::vector<std::function<void>()> m_addEntitiesQueue;
    };
    }
}