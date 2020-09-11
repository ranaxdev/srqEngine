#ifndef _H_ENTITY
#define _H_ENTITY
#include "../Components/Renderable.h"
#include "Scene.h"
#include<iostream>

/* List of all components sorted relative to their personal identifier */
enum class ComponentType { RENDERABLE };

class Entity {
public:

	Entity(Scene * scene);
	~Entity();

	
	/* Add component to entity and return component signature*/
	template<typename ...Args>
	unsigned int addComponent(ComponentType type, Args&&...args) {
		switch (type) {
			case ComponentType::RENDERABLE: {
				Renderable r = Renderable(std::forward<Args>(args)...);
				scene->renderables.push_back(r);
				break;
			}
		}
		return 0;
	} 


	int getID() const;
	
private:
	int m_ID;

	Scene* scene;
};

#endif