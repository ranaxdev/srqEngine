#ifndef _H_COLLISION
#define _H_COLLISION
#include "../Renderer_API/Model.h"
#include "../Camera.h"
#include<vector>
#include<memory>
#include<algorithm>
class Collision
{
public:
	Collision();
	static void updateCollisions(Camera& cam);
	static std::vector<std::shared_ptr<Model>> collidables;

private:
	static float calcsign(float x);

};

#endif
