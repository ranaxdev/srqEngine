#include "Entity.h"

/* Constructor */
Entity::Entity() {}

/* Add component */
template<typename T, typename...Args>
unsigned int Entity::addComponent(T, Args...args) {}