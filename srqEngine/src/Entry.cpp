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
#include "Renderer_API/VertexArray.h"

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
		0.0f, 0.5f, 0.0f,	
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};
	unsigned int indices[] = { 0, 1, 2 }; 
	std::shared_ptr<IndexBuffer> ib = std::make_shared<IndexBuffer>(indices, (unsigned int) (sizeof(indices)/sizeof(unsigned int)));
	std::shared_ptr<VertexBuffer> vb = std::make_shared<VertexBuffer>(data, (unsigned int) (sizeof(data)));
	vb->setlayout(
		{
			{DataType::Float3, "a_Pos"}
		}
	);
	VertexArray va = VertexArray();
	va.addVBO(vb);
	va.setEBO(ib);

	/* Main loop */
	while (!glfwWindowShouldClose(mainWindow)) {
		glClearColor(0.2f, 0.3f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* DRAW RENDERABLES FROM ACTIVE SCENE */
		glDrawElements(GL_TRIANGLES, va.getEBO().get()->getCount(), GL_UNSIGNED_INT, nullptr);

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