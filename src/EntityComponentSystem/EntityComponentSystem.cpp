#include "EntityComponentSystem.h"

#include "Debug.h"


////////////////////////////////////////////////////////////////////////////////
/////////////////////////// Entity Component System ////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void EntityComponentSystem::init()
{
    // Initialize Entity IDs
    for (size_t i {0}; i < MAX_ENTITIES; ++i)
        availableIDs.emplace(static_cast<EntityID>(i));

    DEBUG_PRINT("Entity Component System Initialized.");

    /******************************** Testing *********************************/

    // auto test {create()};

    // emplace<int>(test, 88);
    // emplace<float>(test, 9.11f);

    // DEBUG_PRINT("Int:%   Float:%", get<int>(test), get<float>(test));

    // update<int, float>(test, [] (int& intVal, float& floatVal)
    // {
    //     intVal = 12;
    //     floatVal = 42.0f;
    // });

    // const auto& [newIntVal, newFloatVal] {get<int, float>(test)};

    // DEBUG_PRINT("Int:%   Float:%", newIntVal, newFloatVal);
}


void EntityComponentSystem::cleanup()
{
    // Delete Component Arrays
    for (const auto& elem : componentPool)
        delete elem.second;

    DEBUG_PRINT("Entity Component System Cleaned.");
}

/********************************* Functions **********************************/

EntityID EntityComponentSystem::create()
{
    DEBUG_ASSERT(availableIDs.size() > 0);

    // Retrieve Next Available ID
    EntityID entity {availableIDs.front()};

    // Pop ID from Available ID List
    availableIDs.pop();

    return entity;
}
