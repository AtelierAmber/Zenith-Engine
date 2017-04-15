#include "ECSController.hpp"

namespace zen {
    template <typename T, typename... Ts>
    struct ManagerInit {
        static void construct(ECSController* controller) {
            controller->registerComponent((std::is_empty<T>::value == true) ? 0 : sizeof(T));
            ManagerInit<Ts...>::construct(controller);
        }
    };
    template <typename T>
    struct ManagerInit<T> {
        static void construct(ECSController* controller) {
            controller->registerComponent((std::is_empty<T>::value == true) ? 0 : sizeof(T));
        }
    };

    template <int I, typename T, typename S, typename... Ts>
    struct GetComponentID {
        constexpr static uint64 value = GetComponentID<I + 1, T, Ts...>::value;
    };
    template <int I, typename T, typename... Ts>
    struct GetComponentID<I, T, T, Ts...> {
        constexpr static uint64 value = 1ULL << I;
    };

    template<typename... Cs>
    class ECSCore {
    public:
        ECSCore() {
            m_controller = new ECSController;
            ManagerInit<Cs...>::construct(m_controller);
            m_controller->finalize();
        }

        ~ECSCore() {
            m_controller->dispose();
            delete m_controller;
        }

        template<typename C>
        uint64 getComponentID() {
            return GetComponentID<0, C, Cs...>::value;
        }

        void addSystem(std::function<void(unsigned int, uint8_t)> insertion,
                       std::function<void(unsigned int, uint8_t)> removal,
                       uint64 key, const char* name = "<No name specified>") {
            m_controller->registerSystem(insertion, removal, key, name);
        }

        unsigned int createEntity(uint8_t type = 0) {
            return m_controller->createEntity(type);
        }

        template<typename... Ts>
        unsigned int createEntity(uint8_t type = 0) {
            unsigned int handle;
            handle = m_controller->createEntity(type);
            AddComponents<Ts...>::To(m_controller, handle);
        }

        void removeEntity(unsigned int entityHandle) {
            m_controller->removeEntity(entityHandle);
        }
        void removeEntity(ECSEntity* entity) {
            m_controller->removeEntity(entity->m_handle);
        }

        template<typename... Ts>
        void addComponentsTo(unsigned int entityHandle) {
            AddComponents<Ts...>::To(m_controller, entityHandle);
        }
        template<typename... Ts>
        void addComponentsTo(ECSEntity* entity) {
            AddComponents<Ts...>::To(m_controller, entity->m_handle);
        }

        template<typename... Ts>
        void removeComponentsFrom(unsigned int entityHandle) {
            RemComponents<Ts...>::From(m_controller, entityHandle);
        }
        template<typename... Ts>
        void removeComponentsFrom(ECSEntity* entity) {
            RemComponents<Ts...>::From(m_controller, entity->m_handle);
        }

        ECSEntity* getEntity(unsigned int entityHandle) {
            return m_controller->getEntity(entityHandle);
        }

        template<typename C>
        C* getComponentFrom(unsigned int entityHandle) {
            return m_controller->getComponentFrom<C>(entityHandle, getComponentID<C>());
        }
        template<typename C>
        C* getComponentFrom(ECSEntity* entity) {
            return m_controller->getComponentFrom<C>(entity->m_handle, getComponentID<C>());
        }

        void refresh() {
            m_controller->update();
        }

        ECSController* getContext() { return m_controller; }

    private:
        template <typename C, typename... Is>
        struct AddComponents {
            static void To(ECSController* controller, unsigned int entityHandle) {
                controller->addComponentTo(entityHandle, GetComponentID<0, C, Cs...>::value, C());
                AddComponents<Is...>::To(controller, entityHandle);
            }
        };
        template <typename C>
        struct AddComponents<C> {
            static void To(ECSController* controller, unsigned int entityHandle) {
                controller->addComponentTo(entityHandle, GetComponentID<0, C, Cs...>::value, C());
            }
        };

        template <typename C, typename... Is>
        struct RemComponents {
            static void From(ECSController* controller, unsigned int entityHangle) {
                controller->remComponentFrom(entityHandle, GetComponentID<0, C, Cs...>::value);
                RemComponents<Is...>::From(controller, entityHangle);
            }
        };
        template <typename C>
        struct RemComponents<C> {
            static void From(ECSController* controller, unsigned int entityHandle) {
                controller->remComponentFrom(entityHandle, GetComponentID<0, C, Cs...>::value);
            }
        };

        template <typename C, typename... Is>
        struct GetComponentPattern {
            constexpr static int value = (GetComponentID<0, C, Cs...>::value | GetComponentPattern<Is...>::value);
        };
        template <typename C>
        struct GetComponentPattern<C> {
            constexpr static int value = (GetComponentID<0, C, Cs...>::value);
        };

        ECSController* m_controller = nullptr;
    };
}