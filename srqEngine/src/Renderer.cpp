#include<glad/glad.h>
#include<iostream>
#include "Renderer.h"

/* Constructor*/
// Render the currently active scene
Renderer::Renderer(GLFWwindow* window) {

	// shader - temp
	int success;
	char infolog[1024];
	const char* vertexShaderSrc =
		"#version 330 core\n"
		"layout (location=0) in vec3 aPos;\n"
		"void main(){ gl_Position = vec4(aPos,1.0f); }\0";
	const char* fragmentShaderSrc =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main(){ FragColor = vec4(0.2f,0.5f,0.3f,1.0f);}\0";
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		std::cout << "[ERROR] Shader Compilation Error!" << std::endl;
		glGetShaderInfoLog(vertexShader, 1024, NULL, infolog);
		std::cout << infolog << std::endl;
	}

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		std::cout << "[ERROR] Shader Compilation Error!" << std::endl;
		glGetShaderInfoLog(fragmentShader, 1024, NULL, infolog);
		std::cout << infolog << std::endl;
	}

	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		std::cout << "[ERROR] Shader LINK Error!" << std::endl;
		glGetProgramInfoLog(shaderProgram, 1024, NULL, infolog);
		std::cout << infolog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(shaderProgram);

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