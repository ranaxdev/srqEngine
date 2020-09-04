#ifndef _H_SCENE
#define _H_SCENE
#include "../Components/Renderable.h"
#include "../Util/Globals.h"

/* Globals */
extern const int MAX_ENTITIES;

class Scene {
public:
	/* Maintain component arrays (index represents entity ID)*/
	Renderable* renderables[MAX_ENTITIES];

	/* Constructor / Destructor */
	Scene();
	~Scene();

	/* Getters */
	static Scene* getActiveScene();

	/* Setters */
	static void setActiveScene(Scene* scene);

private:
	/* currently active state */
	static Scene* m_activeScene;
	
	
};

#endif