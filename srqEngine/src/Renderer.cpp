#include<glad/glad.h>
#include<iostream>
#include "Renderer.h"
#include "Util/Shader.h"
#include "Util/Globals.h"
#include "Util/VertexBuffer.h"
#include "SceneMgmt/Entity.h"

/* GLOBALS */
extern const int MAX_ENTITIES;


/* Constructor*/
// Render the currently active scene
Renderer::Renderer(GLFWwindow* window) : window(window) {
	
}

void Renderer::render() {

	Shader generalShader = Shader("res/shaders/vertexgen.shader", "res/shaders/fragmentgen.shader");
	generalShader.use();

	float pos[] = {
		-0.5f,-0.5f,-0.5f, // triangle 1 : begin
	-0.5f,-0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f, // triangle 1 : end
	0.5f, 0.5f,-0.5f, // triangle 2 : begin
	-0.5f,-0.5f,-0.5f,
	-0.5f, 0.5f,-0.5f, // triangle 2 : end
	0.5f,-0.5f, 0.5f,
	-0.5f,-0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,
	0.5f, 0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,
	-0.5f,-0.5f,-0.5f,
	-0.5f,-0.5f,-0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f,-0.5f,
	0.5f,-0.5f, 0.5f,
	-0.5f,-0.5f, 0.5f,
	-0.5f,-0.5f,-0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f,-0.5f, 0.5f,
	0.5f,-0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f,-0.5f,-0.5f,
	0.5f, 0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f,-0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f,-0.5f,
	-0.5f, 0.5f,-0.5f,
	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f,-0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f,-0.5f, 0.5f
	};
	unsigned int ind[] = { 0,0,0 };
	float tex[] = { 0,0,0 };
	Scene s1 = Scene();

	Entity e1 = Entity(&s1);
	e1.addComponent(Entity::RENDERABLE, e1.getID(), pos, ind, tex);
	Scene::setActiveScene(&s1);
	
	
	/* Vertex Arrays*/
	unsigned int VAO[2];
	glGenVertexArrays(2, VAO);
	
	/* Data distribution initialization into VAOs */
	for (int i = 0; i < s1.renderables.size(); i++) {
		glBindVertexArray(VAO[i]);
		VertexBuffer vbo = VertexBuffer(pos, sizeof(pos));
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
		glEnableVertexAttribArray(0);
		
		glBindVertexArray(0);
		
	}

	/* Main loop */
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* DRAW ENTITIES FROM ACTIVE SCENE */
		for (int i = 0; i < 2; i++) {
			glBindVertexArray(VAO[i]);
			glDrawArrays(GL_TRIANGLES, 0, 12*3);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		glBindVertexArray(0);
		
		/* Swap buffers */
		glfwSwapBuffers(window);

		/* Poll events and input */
		glfwPollEvents();
	}
}

/* Destructor */
Renderer::~Renderer() {}