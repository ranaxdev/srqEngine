#include "Entity.h"

/* Initialize the entity by generating an ID */
Entity::Entity(){
	// No componenets attached initially
	Entity::hascomponents[1] = {0};
	
	// Generate unique ID to identify with in scenes

}

/* Add component and provide appropriate arguments */
template<typename T, typename...Args>
unsigned int Entity::addComponent(T, Args...args) {}


/* Getters */

// Return array of components the entity contains
// Index: ID of component, 0: Not attached, 1: attached
bool* Entity::getComponents() { return hascomponents; }