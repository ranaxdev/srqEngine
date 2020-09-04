#include "Entity.h"
#include "../Util/Signature.h"
#include<iostream>
/* Initialize the entity by generating an ID */
Entity::Entity(){
	// Set entity's scene to the active one
	Entity::scene = Scene::getActiveScene();
	// No componenets attached initially
	Entity::hascomponents[1] = {0};
	
	// Generate unique ID to identify with in scenes
	Entity::m_ID = Signature::generateSig();
	if (Entity::m_ID == -1)
		Entity::~Entity();
}
/* Destroy entity by clearing all related memory */
Entity::~Entity() {
	std::cout << "Entity destroyed " << Entity::m_ID << std::endl;
}

/* Getters */

// Return array of components the entity contains
// Index: ID of component, 0: Not attached, 1: attached
bool* Entity::hasComponents() { return Entity::hascomponents; }


/* Return the ID (unique signature) of the current entity */
int Entity::getID() { return Entity::m_ID; }