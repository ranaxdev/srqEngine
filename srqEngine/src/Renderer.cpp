#include<glad/glad.h>
#include<iostream>
#include "Renderer.h"
#include "Renderer_API/Shader.h"
#include "Util/Globals.h"

/* GLOBALS */
extern const int MAX_ENTITIES;

glm::mat4 Renderer::viewProjectionMatrix = glm::mat4(1.0f);
glm::mat4 Renderer::viewMatrix = glm::mat4(1.0f);
glm::mat4 Renderer::projectionMatrix = glm::mat4(1.0f);
bool Renderer::calcedProj = false;

Renderer::Renderer() {
	
}
Renderer::~Renderer() {}

/* Initialze renderer */
void Renderer::init(Camera& cam) {
	Renderer::viewProjectionMatrix = cam.getVP(); // recalulates automatically
	// recalcs when cam.getVP() is called so no extra performance hit
	Renderer::viewMatrix = cam.getView();
	// only calc once as it doesn't change
	if (!calcedProj) {
		Renderer::projectionMatrix = cam.getProjection();
		Renderer::calcedProj = true;
	}
	
}

/* Render textured model to screen */
void Renderer::renderTexModel(Shader& shader, Model& model, glm::mat4 transform)
{
	model.update(); // update model (just binds texture for now)
	// bind shader and set uniform
	shader.bind();
	shader.setMat4("u_VP", Renderer::viewProjectionMatrix); // view projection matrix
	shader.setMat4("u_M", transform); // model matrix

	model.getVA().bind();
	glDrawArrays(GL_TRIANGLES, 0, model.getTotalVectors());
	
}

void Renderer::renderParticle(Shader& shader, ParticleGen& pg, glm::mat4 transform) {
	shader.bind();
	shader.setMat4("u_VP", Renderer::viewProjectionMatrix);
	shader.setMat4("u_M", transform);
	shader.setFloat("size", 0.1f);

	pg.render();

}


/* Render colored model to screen */
void Renderer::renderModel(Shader& shader, Model& model, glm::mat4 transform) {
	shader.bind();
	// bind camera uniforms
	shader.setMat4("u_VP", Renderer::viewProjectionMatrix);
	shader.setMat4("u_M", transform);

	glBindTexture(GL_TEXTURE_2D, 0);
	// bind configured uniforms
	if (shader.getConfig().size() > 0) {
		for (auto& c : shader.getConfig()) {
			c();
		}
	}

	model.getVA().bind();
	glDrawArrays(GL_TRIANGLES, 0, model.getTotalVectors());
}

/* Render plain data straight from a VAO to screen */
void Renderer::renderPlain(Shader& shader, VertexArray& va, glm::mat4 transform)
{
	// bind shader
	shader.bind();

	// Explicit configurations (due to being applicable to all)
	shader.setMat4("u_VP", Renderer::viewProjectionMatrix);
	shader.setMat4("u_M", transform);
	
	// Run all other shader configurations
	if (shader.getConfig().size() > 0) {
		for (auto& c : shader.getConfig()) {
			c();
		}
	}

	va.bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
}


void Renderer::renderSkybox(Shader& shader, Skybox& sky)
{
	glDepthFunc(GL_LEQUAL);
	// bind cubemap
	sky.bind();
	
	// bind shader
	shader.bind();
	

	// Cam configs
	
	glm::mat4 view = glm::mat4(glm::mat3(Renderer::viewMatrix));
	shader.setMat4("u_V", view);
	shader.setMat4("u_P", Renderer::projectionMatrix);
	

	// draw
	sky.getVA().bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthFunc(GL_LESS);
}

