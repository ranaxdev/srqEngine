#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include "Renderer.h"



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
	glfwMakeContextCurrent(mainWindow);

	/* Load glad */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "[ERROR] Failed to init GLAD!" << std::endl;
	}

	/* Config OpenGL options */
	glViewport(0, 0, 800, 600);

	/* Init renderer */
	Renderer r = Renderer(mainWindow);
	r.render();
	/* Main loop */
	while (!glfwWindowShouldClose(mainWindow)) {
		glClearColor(0.2f, 0.3f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* DRAW ENTITIES FROM ACTIVE SCENE */
		
		/* Swap buffers */
		glfwSwapBuffers(mainWindow);

		/* Poll events and input */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}