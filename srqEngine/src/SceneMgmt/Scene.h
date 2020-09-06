#ifndef _H_SCENE
#define _H_SCENE
#include "../Components/Renderable.h"
#include<vector>
#
class Scene {
public:
	std::vector<Renderable> renderables;
	
	Scene();

};

#endif