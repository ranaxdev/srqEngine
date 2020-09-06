#include<glad/glad.h>
#include<iostream>
#include "Renderer.h"
#include "Util/Shader.h"
#include "Util/Globals.h"
#include "SceneMgmt/Entity.h"

/* GLOBALS */
extern const int MAX_ENTITIES;
unsigned int VAO;

/* Constructor*/
// Render the currently active scene
Renderer::Renderer(GLFWwindow* window) : window(window) {
	
}

void Renderer::render() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	Shader generalShader = Shader("res/shaders/vertexgen.shader", "res/shaders/fragmentgen.shader");
	generalShader.use();

	float pos[] = { 0.0f,0.5f,0.0f, -0.5f,-0.5f,0.0f, 0.5f,-0.5f,0.0f };
	unsigned int ind[] = { 0,0,0 };
	float tex[] = { 0,0,0 };
	float pos2[] = { -0.3f,0.5f,0.0f, 0.0f,-0.5f,0.0f, 0.5f,-0.5f,0.0f };
	unsigned int ind2[] = { 0,0,0 };
	float tex2[] = { 0,0,0 };
	Scene s1 = Scene();

	Entity e1 = Entity(&s1);
	Entity e2 = Entity(&s1);
	e2.addComponent(Entity::RENDERABLE, e2.getID(), pos2, ind2, tex2);
	e1.addComponent(Entity::RENDERABLE, e1.getID(), pos, ind, tex);
	
	unsigned int VBO[2];
	glGenBuffers(2, VBO);
	for (int i = 0; i < s1.renderables.size(); i++) {
		
		glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), s1.renderables[i].pos_data, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		std::cout << "VBO: " <<  VBO[i] << std::endl;
	}


	/* Main loop */
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* DRAW ENTITIES FROM ACTIVE SCENE */
		for (int i = 0; i < 2; i++) {
			glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		/* Swap buffers */
		glfwSwapBuffers(window);

		/* Poll events and input */
		glfwPollEvents();
	}
}

/* Destructor */
Renderer::~Renderer() {}