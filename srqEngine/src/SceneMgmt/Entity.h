#ifndef _H_ENTITY
#define _H_ENTITY
#include "../Components/Renderable.h"
#include "Scene.h"
#include<iostream>
class Entity {
public:
	/* Init entity/generate signature */
	Entity(Scene* scene);
	~Entity();

	/* List of all components sorted relative to their personal identifier */
	enum ComponentType {RENDERABLE};

	/* Add component to entity and return component signature*/
	template<typename ...Args>
	unsigned int addComponent(ComponentType type, Args...args) {
		switch (type) {
			case RENDERABLE: {
				Renderable r = Renderable(args...);
				hascomponents[RENDERABLE] = true;
				std::cout << "getting " << Entity::getID() << std::endl;
				scene->renderables.push_back(r);
				break;
			}
		}
		return 0;
	} 
	

	/* Getters */
	bool* hasComponents();
	int getID() const;
	
private:
	/* Unique entity signature */
	int m_ID;

	/* Which scene this entity belongs to */
	Scene* scene;

	/* Bool array whose indices correspond to which component the entity has */
	bool hascomponents[1];
};

#endif