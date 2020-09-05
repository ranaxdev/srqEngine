#ifndef _H_SCENE
#define _H_SCENE
#include "../Components/Renderable.h"
#include "../Util/Globals.h"
#include<vector>
/* Globals */
extern const int MAX_ENTITIES;

class Scene {
public:
	/* Maintain component arrays (index represents entity ID)*/
	std::vector<Renderable> renderables;

	const char* name;
	
	/* Constructor / Destructor */
	Scene(const char* name);
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