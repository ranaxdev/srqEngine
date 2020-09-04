#include<glad/glad.h>
#include<iostream>
#include "Renderer.h"
#include "Util/Shader.h"
/* Constructor*/
// Render the currently active scene
Renderer::Renderer(GLFWwindow* window) {

	Shader generalShader = Shader("res/shaders/vertexgen.shader", "res/shaders/fragmentgen.shader");
	generalShader.use();
	// data + vbo/ebo/vao - temp
	float pos_data[] = {
		0.0f, 0.5f, 0.0f,
		-0.5f,0.0f,0.0f,
		0.5f,0.0f,0.0f
	};
	unsigned int indicies[] = { 0,1,2 };
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), pos_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0);


	/* Main loop */
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		/* TEMP DRAW STUFF */
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		/* Swap buffers */
		glfwSwapBuffers(window);

		/* Poll events and input */
		glfwPollEvents();
	}
}


/* Destructor */
Renderer::~Renderer() {}