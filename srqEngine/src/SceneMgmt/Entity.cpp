#include "Entity.h"
#include "../Util/Signature.h"
#include<iostream>
/* Initialize the entity by generating an ID */
Entity::Entity(Scene* scene): scene(scene){
	// Set entity's scene to the active one
	//Entity::scene = Scene::getActiveScene();
	// No componenets attached initially
	Entity::hascomponents[1] = {0};
	
	// Generate unique ID to identify with in scenes
	Entity::m_ID = Signature::generateSig();
	if (Entity::m_ID == -1)
		Entity::~Entity();
}
/* Destroy entity by clearing all related memory */
Entity::~Entity() {
}

/* Getters */

// Return array of components the entity contains
// Index: ID of component, 0: Not attached, 1: attached
bool* Entity::hasComponents() { return Entity::hascomponents; }


/* Return the ID (unique signature) of the current entity */
int Entity::getID() const { return Entity::m_ID; }

