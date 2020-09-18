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

/* Render model to screen */
void Renderer::renderModel(Shader& shader, VertexArray& va, Model& model, glm::mat4 transform) 
{
	model.update(); // update model (just binds texture for now)
	// bind shader and set uniform
	shader.bind();
	shader.setMat4("u_VP", Renderer::viewProjectionMatrix); // view projection matrix
	shader.setMat4("u_M", transform); // model matrix

	va.bind();
	glDrawArrays(GL_TRIANGLES, 0, model.getTotalVectors());
	
}
/* Render plain data to screen */
void Renderer::renderPlain(Shader& shader, VertexArray& va, glm::mat4 transform)
{
	// bind shader and set uniforms
	shader.bind();
	shader.setMat4("u_VP", Renderer::viewProjectionMatrix);
	shader.setMat4("u_M", transform);
	
	// Run all shader configurations
	for (auto& c : shader.config) {
		c();
	}

	
	va.bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

