#ifndef _H_ENTITY
#define _H_ENTITY

class Entity {
public:
	/* Constructor - init entity/generate signature */
	Entity();

	/* List of all components sorted relative to their personal identifier */
	enum ComponentType {RENDERABLE};

	/* Add component to entity and return component signature */
	template<typename T, typename...Args>
	unsigned int addComponent(T, Args...args);

private:
	unsigned int m_ID;
};

#endif