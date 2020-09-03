#ifndef _H_ENTITY
#define _H_ENTITY

class Entity {
public:
	/* Init entity/generate signature */
	Entity();

	/* List of all components sorted relative to their personal identifier */
	enum ComponentType {RENDERABLE};

	/* Add component to entity and return component signature */
	template<typename T, typename...Args>
	unsigned int addComponent(T, Args...args);

	/* Getters */
	bool* getComponents();

private:
	/* Unique entity signature */
	unsigned int m_ID;

	/* Bool array whose indices correspond to which component the entity has */
	bool hascomponents[1];
};

#endif