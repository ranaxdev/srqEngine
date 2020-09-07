#include<glad/glad.h>
#include<iostream>
#include "Renderer.h"
#include "Util/Shader.h"
#include "Util/Globals.h"


/* GLOBALS */
extern const int MAX_ENTITIES;


/* Constructor*/
// Render the currently active scene
Renderer::Renderer() {
	
}

void Renderer::render(unsigned int* VAOs, int numtoRender) {
	for (int i = 0; i < numtoRender; i++) {
		glBindVertexArray(VAOs[i]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}

/* Destructor */
Renderer::~Renderer() {}