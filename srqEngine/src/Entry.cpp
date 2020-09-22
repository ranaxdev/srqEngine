#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include<iostream>
#include <functional>

#include "Util/Globals.h"


#include "Renderer.h"
#include "Renderer_API/Shader.h"
#include "Renderer_API/Texture.h"
#include "Renderer_API/Buffer.h"
#include "Renderer_API/VertexArray.h"
#include "Renderer_API/Model.h"

#include "Camera.h"


// ------------------------------------------------

/* GLOBALS */
extern const int MAX_ENTITIES;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

float delta = 0.0f;
float last = 0.0f;

/*---------------- TEMPORARY - callback declarations ------------------- */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

/* Camera */
Camera cam = Camera();

/* Entry point */
int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Main window */
	GLFWwindow* mainWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "srqEngine",NULL, NULL);
	if (mainWindow == NULL) {
		std::cout << "[ERROR] Failed to create window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(mainWindow); // make it the current context
	/* TEMPORARY: SET GLFW CALLBACKS */
	glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);
	
	/* Config GLFW Options */
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	/* Load glad */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "[ERROR] Failed to init GLAD!" << std::endl;
	}

	/* Config OpenGL options */
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	/* --------------------------------------Shader declarations------------------------------ */
	Shader shader = Shader("res/shaders/vertexgen.shader", "res/shaders/fragmentgen.shader");
	Shader lightShader = Shader("res/shaders/vertexlight.shader", "res/shaders/fragmentlight.shader");
	Shader lightsourceShader = Shader("res/shaders/lightsourcevertex.shader", "res/shaders/lightsourcefragment.shader");
	// ==================================== Shader configurations ===================================
	// light shader
	lightShader.AddVec3Config("lightColor", 1.0f, 1.0f, 1.0f);
	lightShader.AddVec3Config("objColor", 0.2f, 0.3f, 0.8f);
	//lightShader.AddVec3Config("lightPos", 1.2f, 1.0f, 2.0f);
	/*-------------------------------------------------------------------------------------------*/


	//									LOAD MODELS     										//
	// ==========================================================================================
	// declare models
	Model M_FLOOR = Model("res/models/floor.obj", "res/textures/floor.png"); // uses floor texture
	Model M_WALL = Model("res/models/bark.obj", "res/textures/bark.jpg");
	Model M_PYR = Model("res/models/leaves.obj", "res/textures/leaf.jpg");
	// bind them (initialization - association with VAOs)
	M_FLOOR.bind();
	M_WALL.bind();
	M_PYR.bind();

	// ==========================================================================================//

	/* -----------------------------Transformations---------------------- */
	
	// ---------------------------------------------------------------------
	glm::mat4 trans = glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
	// ============================================================
	/* Game loop */
	// ============================================================
	while (!glfwWindowShouldClose(mainWindow)) {
		// delta time setup
		float curr = glfwGetTime();
		delta = curr - last;
		last = curr;


		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* INIT RENDERER */
		Renderer::init(cam);
		
		trans = glm::rotate(trans, glm::radians(delta* 20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		/* DRAW RENDERABLES FROM ACTIVE SCENE */
		Renderer::renderModel(shader, M_PYR.getVA(), M_PYR,trans);
		Renderer::renderModel(shader, M_WALL.getVA(), M_WALL,trans);
		/* Swap buffers */
		glfwSwapBuffers(mainWindow);


		// PROCESS INPUT (TEMP)
		glfwPollEvents();
		cam.update(mainWindow, delta);
		
	}

	glfwTerminate();
	return 0;
}


/* --------------------------- TEMPORARY - DEFINE CALLBACKS ----------------------  */
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
