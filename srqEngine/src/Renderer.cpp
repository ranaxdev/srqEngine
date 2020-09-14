#include<glad/glad.h>
#include<iostream>
#include "Renderer.h"
#include "Renderer_API/Shader.h"
#include "Util/Globals.h"

/* GLOBALS */
extern const int MAX_ENTITIES;

glm::mat4 Renderer::viewProjectionMatrix = glm::mat4(1.0f);

Renderer::Renderer() {
	
}
Renderer::~Renderer() {}

/* Initialze renderer */
void Renderer::init(Camera& cam) {
	Renderer::viewProjectionMatrix = cam.getVP(); // recalulates automatically
}

/* Render to screen */
void Renderer::render(Shader& shader, VertexArray& va) {

	// bind shader and set uniforms
	shader.bind();
	shader.setMat4("u_VP", Renderer::viewProjectionMatrix);

	va.bind();
	glDrawArrays(GL_TRIANGLES, 0, 18);
	
}

