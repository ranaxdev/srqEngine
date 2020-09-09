#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include<iostream>

#include "Util/Globals.h"

#include "Renderer.h"
#include "Renderer_API/Shader.h"
#include "Renderer_API/Texture.h"
#include "Renderer_API/Buffer.h"
/* GLOBALS */
extern const int MAX_ENTITIES;

/*---------------- TEMPORARY - callback declarations ------------------- */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

/* Entry point */
int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Main window */
	GLFWwindow* mainWindow = glfwCreateWindow(800, 600, "srqEngine", NULL, NULL);
	if (mainWindow == NULL) {
		std::cout << "[ERROR] Failed to create window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(mainWindow); // make it the current context
	/* TEMPORARY: SET GLFW CALLBACKS */
	glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);

	/* Load glad */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "[ERROR] Failed to init GLAD!" << std::endl;
	}

	/* Config OpenGL options */
	glViewport(0, 0, 800, 600);

	/* Init renderer */
	Renderer r = Renderer();
	
	/* Define model data*/

	/* Link shader and use it*/
	Shader shader = Shader("res/shaders/vertexgen.shader", "res/shaders/fragmentgen.shader");
	shader.bind();
	
	/* TEMP - VAO/VBO/Data init */
	float data[] = {
		0.0f, 0.5f, 0.0f,	0.8f,0.2f,0.0f,
		-0.5f, 0.0f, 0.0f,	0.0f,8.0f,0.2f,
		0.5f, 0.0f, 0.0f,	0.5f,0.2f,0.8f
	};
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VertexBuffer vb = VertexBuffer(data, sizeof(data));

	// defines layout of data in vao 
	BufferLayout layout =
	{
		{DataType::Float3, "a_Pos"},
		{DataType::Float3, "a_Color"},
		
	};

	unsigned int index = 0;
	for (const auto& element : layout) {
		glVertexAttribPointer(index, element.count, GL_DATA_TYPE_LOOKUP(element.type), element.normalized? GL_TRUE:GL_FALSE, layout.getStride(), (const void*)(element.offset));
		glEnableVertexAttribArray(index);
		index++;
	}

	/* Main loop */
	while (!glfwWindowShouldClose(mainWindow)) {
		glClearColor(0.2f, 0.3f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* DRAW RENDERABLES FROM ACTIVE SCENE */
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap buffers */
		glfwSwapBuffers(mainWindow);

		/* Poll events and input */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}



/* --------------------------- TEMPORARY - DEFINE CALLBACKS ----------------------  */
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}