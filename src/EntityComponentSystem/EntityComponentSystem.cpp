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

    /******************************** Testing *********************************/

    // emplaceComponent<int>();
}

/********************************* Functions **********************************/

EntityComponentSystem::EntityID EntityComponentSystem::create()
{
    DEBUG_ASSERT(availableIDs.size() > 0);

    // Retrieve Next Available ID
    EntityID entity {availableIDs.front()};

    // Pop ID from Available ID List
    availableIDs.pop();

    return entity;
}
