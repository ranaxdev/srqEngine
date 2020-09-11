#include<glad/glad.h>
#include<iostream>
#include "Renderer.h"
#include "Renderer_API/Shader.h"
#include "Util/Globals.h"

/* GLOBALS */
extern const int MAX_ENTITIES;

Renderer::Renderer() {
	
}
Renderer::~Renderer() {}

/* Render to screen */
void Renderer::render(unsigned int* VAOs, int numtoRender) {
	for (int i = 0; i < numtoRender; i++) {
		glBindVertexArray(VAOs[i]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}

