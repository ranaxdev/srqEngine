#include "Renderer.h"

/* Constructor*/
// Render the currently active scene
Renderer::Renderer(GLFWwindow* window) {

	/* Main loop */
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		

		/* Swap buffers */
		glfwSwapBuffers(window);

		/* Poll events and input */
		glfwPollEvents();
	}
}


/* Destructor */
Renderer::~Renderer() {}