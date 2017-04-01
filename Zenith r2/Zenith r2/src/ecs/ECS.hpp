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
            controller = new ECSController;
            ManagerInit<Cs...>::construct(controller);
            controller->finalize();
        }

        ~ECSCore() {
            controller->dispose();
            delete controller;
        }

        template<typename C>
        uint64 getComponentID() {
            return GetComponentID<0, C, Cs...>::value;
        }

        void addSystem(std::function<void(unsigned int, uint8_t)> insertion,
                       std::function<void(unsigned int, uint8_t)> removal,
                       uint64 key, const char* name = "<No name specified>") {
            controller->registerSystem(insertion, removal, key, name);
        }

        unsigned int createEntity(uint8_t type = 0) {
            return controller->createEntity(type);
        }

        template<typename... Ts>
        unsigned int createEntity(uint8_t type = 0) {
            unsigned int handle;
            handle = controller->createEntity(type);
            AddComponents<Ts...>::To(controller, handle);
        }

        void removeEntity(unsigned int entityHandle) {
            controller->removeEntity(entityHandle);
        }

        template<typename... Ts>
        void addComponentsTo(unsigned int entityHandle) {
            AddComponents<Ts...>::To(controller, entityHandle);
        }

        template<typename... Ts>
        void removeComponentsFrom(unsigned int entityHandle) {
            RemComponents<Ts...>::From(controller, entityHandle);
        }

        ECSEntity* getEntity(unsigned int entityHandle) {
            return controller->getEntity(entityHandle);
        }

        template<typename C>
        C* getComponentFrom(unsigned int entityHandle) {
            return controller->getComponentFrom<C>(entityHandle, getComponentID<C>());
        }

        void update() {
            controller->update();
        }

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

        ECSController* controller = nullptr;
    };
}