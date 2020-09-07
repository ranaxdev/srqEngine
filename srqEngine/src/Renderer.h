#ifndef _H_RENDERER
#define _H_RENDERER

#include<GLFW/glfw3.h>

class Renderer {
public:
	/* Constructor & Destructor */
	Renderer();
	~Renderer();
	void render(unsigned int* VAOs, int numtoRender);

private:
	
};

#endif