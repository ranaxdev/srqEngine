#ifndef _H_SCENE
#define _H_SCENE
#include "../Components/Renderable.h"
#include "../Util/Globals.h"
#include<vector>
extern const int MAX_ENTITIES;

class Scene {
public:
	std::vector<Renderable> renderables;
	
	Scene();
	
	static void setActiveScene(Scene* scene);
	static Scene* getActiveScene();



private:
	static Scene* active_scene;

};

#endif