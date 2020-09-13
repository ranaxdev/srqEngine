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

#include "Camera.h"

// ------------------------------------------------

/* GLOBALS */
extern const int MAX_ENTITIES;

/*---------------- TEMPORARY - callback declarations ------------------- */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processMovement(GLFWwindow* window);

/* Camera */
Camera cam = Camera();

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


	/* Setup shaders */
	Shader shader = Shader("res/shaders/vertexgen.shader", "res/shaders/fragmentgen.shader");
	
	
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

	

	// ============================================================
	/* Game loop */
	// ============================================================
	while (!glfwWindowShouldClose(mainWindow)) {
		// process input
		processMovement(mainWindow);

		glClearColor(0.2f, 0.3f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* INIT RENDERER */
		Renderer::init(cam);

		/* DRAW RENDERABLES FROM ACTIVE SCENE */
		Renderer::render(shader, va);

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

void processMovement(GLFWwindow* window) {
	float camSpeed = 0.01f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { // move forward
		cam.setCamPos(cam.getCamPos() += camSpeed*(cam.getCamFront()));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { // move back
		cam.setCamPos(cam.getCamPos() -= camSpeed * (cam.getCamFront()));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { // move left
		cam.setCamPos(cam.getCamPos() -= glm::normalize(glm::cross(cam.getCamFront(), cam.getCamUp()))*camSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { // move right
		cam.setCamPos(cam.getCamPos() += glm::normalize(glm::cross(cam.getCamFront(), cam.getCamUp())) * camSpeed);
	}


}