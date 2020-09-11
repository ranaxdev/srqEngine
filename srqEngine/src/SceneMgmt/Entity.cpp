#include "Entity.h"
#include "../Util/Signature.h"
#include<iostream>

/* Initialize the entity by generating an ID */
Entity::Entity(Scene* scene): scene(scene){
	// Generate unique ID to identify with in scenes
	Entity::m_ID = Signature::generateSig();
	if (Entity::m_ID == -1)
		Entity::~Entity();
}
/* Clear related memory */
Entity::~Entity() {
}

/* Getters */
/* Return the ID (unique signature) of the current entity */
int Entity::getID() const { return Entity::m_ID; }

