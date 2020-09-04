#ifndef _H_ENTITY
#define _H_ENTITY
#include "../Components/Renderable.h"
#include<iostream>
class Entity {
public:
	/* Init entity/generate signature */
	Entity();
	~Entity();

	/* List of all components sorted relative to their personal identifier */
	enum ComponentType {RENDERABLE};

	/* Add component to entity and return component signature */
	template<typename...Args>
	unsigned int addComponent(ComponentType type, Args...args) {
		switch (type) {
			case RENDERABLE: {
				Renderable r = Renderable(args...);
				hascomponents[RENDERABLE] = true;
				break;
			}
		}
		return 0;
	}

	/* Getters */
	bool* getComponents();
	int getID();

private:
	/* Unique entity signature */
	int m_ID;

	/* Bool array whose indices correspond to which component the entity has */
	bool hascomponents[1];
};

#endif