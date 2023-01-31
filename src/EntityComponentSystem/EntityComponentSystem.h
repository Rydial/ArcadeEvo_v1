#ifndef SRC_ENTITY_COMPONENT_SYSTEM_H
#define SRC_ENTITY_COMPONENT_SYSTEM_H


#include <cstdint>
#include <queue>
#include <unordered_map>
#include <vector>


////////////////////////////////////////////////////////////////////////////////
/////////////////////////// Entity Component System ////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class EntityComponentSystem
{
private:

    /******************************* Constants ********************************/

    static constexpr uint32_t MAX_ENTITIES {10000};

public:

    /****************************** Enumerations ******************************/

    enum class ComponentID : uint32_t {};

    enum class EntityID : uint32_t {VOID = MAX_ENTITIES};

private:

    /****************************** Data Structs ******************************/

    struct ComponentBase {};


    template <typename T>
    struct ComponentTyped : public ComponentBase
    {
        std::vector<EntityID> sparse {};  // EntityID --> Dense Array Index
        std::vector<T> dense {};        // Holds Actual Elements
    };

    /******************************* Variables ********************************/

    std::queue<EntityID> availableIDs {};
    std::unordered_map<ComponentID, ComponentBase> componentPool {};
    size_t componentTypeCount {0};

    /******************************* Functions ********************************/

    /*
        Returns a reference to the specified component array, performing an
        insertion if the component type does not exist.

        Note: This is how a component type is added to the system.
    */
    // template <typename T>
    // ComponentTyped<T>& getComponentArray()
    // {
    //     return static_cast<ComponentTyped<T>>(
    //         componentPool[getComponentID<T>()]);
    // }


    /*
        Returns a unique ID for each component type 'T'.
    */
    template <typename T>
    ComponentID getComponentID()
    {
        static const ComponentID id {
            static_cast<ComponentID>(componentTypeCount++)
        };
        return id;
    }


    /*
        Returns whether the specified component is integrated in the system.
    */
    // template <typename T>
    // bool hasComponent() {return componentPool.contains(getComponentID<T>());}

public:

    /***************************** Main Functions *****************************/

    void init();

    /******************************* Functions ********************************/

    /*
        Create a new entity entry in the system and returns its respective ID.
    */
    EntityID create();
    

    /*
        Construct a new component for the specified entity with the
        given arguments (replacing pre-existing component).
    */
    // template <typename T, typename ...Args>
    // T& emplace_or_replace(EntityID entity, Args&&... /* args */)
    // {
    //     // Get Component Type Array
    //     auto& component {getComponentArray<T>()};

    //     // Validate Component Existence for Entity


    //     if ()
        
    // //     // Validate Component Existence
    // //     return .emplace_back(args...);
    // }
};


#endif // SRC_ENTITY_COMPONENT_SYSTEM_H
