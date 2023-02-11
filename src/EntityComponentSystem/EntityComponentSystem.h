#ifndef SRC_ENTITY_COMPONENT_SYSTEM_H
#define SRC_ENTITY_COMPONENT_SYSTEM_H


#include "Debug.h"
#include "ECS_Enumerations.h"
#include "UID_Generator.h"

#include <functional>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <vector>


////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// CONCEPTS ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


template <typename ...Args, typename Func>
concept Callable = requires (Func&& func, Args&&... args)
{
    std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
};


////////////////////////////////////////////////////////////////////////////////
/////////////////////////// Entity Component System ////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class EntityComponentSystem
{
private:

    /******************************* Constants ********************************/

    static constexpr uint32_t MAX_ENTITIES {10000};
    static constexpr uint32_t NULL_INDEX {MAX_ENTITIES};

    /******************************** Aliases *********************************/

    using ComponentID = uint32_t;

    /****************************** Data Structs ******************************/

    struct ComponentBase
    {
        virtual ~ComponentBase() = default;
    };


    template <typename T>
    struct ComponentTyped : public ComponentBase
    {
        std::vector<uint32_t> sparse {};    // EntityID --> Dense Array Index
        std::vector<T> dense {};            // Holds Actual Elements

        ComponentTyped() : sparse(MAX_ENTITIES, NULL_INDEX) {}
    };

    /******************************* Variables ********************************/

    std::queue<EntityID> availableIDs {};
    std::unordered_map<ComponentID, ComponentBase*> componentPool {};
    UID_Generator uidGenerator {};

    /******************************* Functions ********************************/

    /*
        Returns a reference to the specified component for the given entity.

        Warning: Assumes specified component exists for given entity.
    */
    template <typename T>
    T& getComponent(const EntityID entity)
    {
        // Retrieve Component (Assuming Entity has one)
        const auto& array {getComponentArray<T>()};
        uint32_t entityID {static_cast<uint32_t>(entity)};

        DEBUG_ASSERT(entityID < MAX_ENTITIES);
        DEBUG_ASSERT(array->sparse[entityID] != NULL_INDEX);

        return array->dense[array->sparse[entityID]];
    }


    /*
        Returns a pointer to the specified component array, performing an
        insertion if the component type does not exist in the system.

        Note: This is how a component type is added to the system.
    */
    template <typename T>
    ComponentTyped<T>* getComponentArray()
    {
        // Search for Component Type in System
        const auto componentID {getComponentID<T>()};
        const auto& search {componentPool.find(componentID)};
        ComponentTyped<T>* ptr {nullptr};

        if (search == componentPool.end()) // Component Type Non-existant
        {
            // Perform Insertion
            const auto&& [insertion, insertionSuccessful] {
                componentPool.emplace(componentID, new ComponentTyped<T>())
            };

            DEBUG_ASSERT(insertionSuccessful);

            ptr = dynamic_cast<ComponentTyped<T>*>(insertion->second);
        }

        else // Component Type Exists
            ptr = dynamic_cast<ComponentTyped<T>*>(search->second);
        
        DEBUG_ASSERT(ptr != nullptr);

        return ptr;
    }


    /*
        Returns a unique ID for the specified template argument.
    */
    template <typename T>
    ComponentID getComponentID()
    {
        return static_cast<ComponentID>(uidGenerator.getUID<T>());
    }

public:

    /***************************** Main Functions *****************************/

    void init();
    void cleanup();

    /******************************* Functions ********************************/

    /*
        Create a new entity entry in the system and returns its respective ID.
    */
    EntityID create();
    

    /*
        Returns a reference to the inserted component, or the already existing
        component.
    */
    template <typename T, typename ...Args>
    T& emplace(const EntityID entity, Args&&... args)
    {
        auto* const array {getComponentArray<T>()};
        const uint32_t entityID {static_cast<uint32_t>(entity)};

        DEBUG_ASSERT(entityID < MAX_ENTITIES);

        if (array->sparse[entityID] == NULL_INDEX)          // No Component
        {
            // Emplace New Component
            T& newComponent {array->dense.emplace_back(args...)};

            // Set Dense Index for Entity
            array->sparse[entityID] = array->dense.size() - 1;

            return newComponent;
        }

        else                                                // Has Component
            return array->dense[array->sparse[entityID]];
    }


    /*
        Returns reference(s) to the specified component(s) for the given entity.

        Warning: Assumes specified component(s) exists for given entity.
    */
    template <typename ...T>
    [[nodiscard]] decltype(auto) get(const EntityID entity)
    {
        if constexpr(sizeof...(T) == 1)                 // 1 Type
            return (getComponent<T>(entity), ...);
        else                                            // 2 or More Types
            return std::tie(getComponent<T>(entity)...);
    }

    
    /*
        Updates the specified component(s) for the given entity.

        Warning: Assumes specified component exists for given entity.
    */
    template <typename ...T, Callable Func>
    void update(const EntityID entity, Func&& func)
    {
        // Call given function with the given entity's components as arguments
        func(getComponent<T>(entity)...);
    }
};


#endif // SRC_ENTITY_COMPONENT_SYSTEM_H
