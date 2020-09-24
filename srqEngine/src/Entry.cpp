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

	//									LOAD MODELS     										//
	// ==========================================================================================
	// ~t e x t u r e d~
	Model M_FLOOR = Model("res/models/floor.obj", "res/textures/floor.png"); // uses floor texture
	// ~p l a i n~
	Model M_LITCUBE = Model("res/models/cube2.obj", glm::vec3(0.2f, 0.3f, 0.8f));
	Model M_LIGHT = Model("res/models/cube2.obj", glm::vec3(1.0f, 1.0f, 1.0f));
	
	// bind them (initialization - association with VAOs)
	M_FLOOR.bind();
	M_LITCUBE.bind();
	M_LIGHT.bind();
	
	/* -----------------------------Transformations---------------------- */
	glm::vec3 light_position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 light_transform = glm::mat4(1.0f);

	/* --------------------------------------Shader declarations------------------------------ */
	Shader shader = Shader("res/shaders/vertexgen.shader", "res/shaders/fragmentgen.shader");
	Shader litshader = Shader("res/shaders/lit/lit_vert.shader", "res/shaders/lit/lit_frag.shader");
	Shader lightsrcshader = Shader("res/shaders/lightSource/lightsrc_vert.shader", "res/shaders/lightSource/lightsrc_frag.shader");
	// ==================================== Shader configurations ===================================

	
	// ============================================================
	/* Game loop */
	// ============================================================
	while (!glfwWindowShouldClose(mainWindow)) {
		// delta time setup
		float curr = glfwGetTime();
		delta = curr - last;
		last = curr;

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* INIT RENDERER */
		Renderer::init(cam);
		
		/* DYNAMIC TRANSFORMATIOSN */
		// light 1 transforms
		light_position.x = sin(glfwGetTime()) * 3.0f;
		light_position.z = cos(glfwGetTime()) * 3.0f;
		light_position.y = 0.0f;

		
		light_transform = glm::mat4(1.0f);
		light_transform = glm::translate(light_transform, light_position);
		light_transform = glm::scale(light_transform, glm::vec3(0.2f));

		litshader.bind();
		litshader.setVec3("lightPos", light_position);

		M_LIGHT.setColor(1.0f,1.0f,1.0f);
		litshader.setVec3("objectColor", M_LITCUBE.getColor());
		litshader.setVec3("lightColor", M_LIGHT.getColor());

		lightsrcshader.bind();
		lightsrcshader.setVec3("lightColor", M_LIGHT.getColor());

		/* DRAW RENDERABLES FROM ACTIVE SCENE */
		Renderer::renderModel(lightsrcshader, M_LIGHT, light_transform);
		
		Renderer::renderModel(litshader, M_LITCUBE);
		


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
