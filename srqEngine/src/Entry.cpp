#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include<iostream>
#include <functional>
#include<algorithm>

#include "Util/Globals.h"
#include "Collision/Collision.h"

#include "Renderer.h"
#include "Renderer_API/Shader.h"
#include "Renderer_API/Texture.h"
#include "Renderer_API/Buffer.h"
#include "Renderer_API/VertexArray.h"
#include "Renderer_API/Model.h"
#include "Renderer_API/Skybox.h"

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
	GLFWwindow* mainWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "srqEngine", NULL, NULL);
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
	glEnable(GL_CULL_FACE);
	glCullFace(GL_CCW);
	//									LOAD MODELS     										//
	// ==========================================================================================
	// ~t e x t u r e d~
	Model M_FLOOR = Model("res/models/floor.obj", "res/textures/floor.png", glm::vec3(30.0f, 30.0f, 1.0f), false);
	Model M_CUBE = Model("res/models/cube2.obj", "res/textures/brick.png", glm::vec3(1.0f, 1.0f, 1.0f), true); /* Set Color: */ M_CUBE.setColor(0.1f, 0.8f, 0.3f);
	Model M_LIGHT = Model("res/models/light.obj", "res/textures/brick.png", glm::vec3(0.5f, 0.5f, 0.5f), false); /* Set Color: */ M_LIGHT.setColor(0.6f, 1.0f, 1.0f);
	Model M_CUBE2 = Model("res/models/cube2.obj", "res/textures/brick.png", glm::vec3(1.0f, 1.0f, 1.0f), true);
	// ~p l a i n~
	Skybox sky = Skybox("skybox");
	// bind them (initialization - association with VAOs)
	M_FLOOR.bind();
	M_CUBE.bind();
	M_CUBE2.bind();
	M_LIGHT.bind();
	
	/* -----------------------------Transformations---------------------- */
	//M_CUBE.getPosition().z -= 10;
	glm::mat4 cube_trans = glm::translate(glm::mat4(1.0f), M_CUBE.getPosition()); /* Cube 1 model */


	M_LIGHT.getPosition().x += 5.0f;
	M_LIGHT.getPosition().z += 2.0f;
	glm::mat4 light_trans = glm::translate(glm::mat4(1.0f), M_LIGHT.getPosition()); /* Light source model */

	M_FLOOR.getPosition().y -= 1.0f;
	glm::mat4 floor_trans = glm::translate(glm::mat4(1.0f), M_FLOOR.getPosition()); /* Floor model */


	M_CUBE2.getPosition().x += 5.0f;
	M_CUBE2.getPosition().z += 12.0f;
	glm::mat4 cube2_trans = glm::translate(glm::mat4(1.0f), M_CUBE2.getPosition()); /* Cube 2 model */


	/* --------------------------------------Shader declarations------------------------------ */
	Shader shader = Shader("res/shaders/vertexgen.shader", "res/shaders/fragmentgen.shader");
	Shader skybox_shader = Shader("res/shaders/skybox/sky_vert.shader", "res/shaders/skybox/sky_frag.shader");
	Shader lit_shader = Shader("res/shaders/lit/lit_vert.shader", "res/shaders/lit/lit_frag.shader");
	Shader light_shader = Shader("res/shaders/light/light_vert.shader", "res/shaders/light/light_frag.shader");
	// ==================================== Shader configurations ===================================
	shader.bind();
	shader.setVec3("light_color", M_LIGHT.getColor());
	shader.setVec3("light_pos", M_LIGHT.getPosition());

	skybox_shader.bind();
	skybox_shader.setInt("skybox", 0);

	lit_shader.bind();
	lit_shader.setVec3("obj_color", M_CUBE.getColor());
	lit_shader.setVec3("light_color", M_LIGHT.getColor());
	lit_shader.setVec3("light_pos", M_LIGHT.getPosition());
	lit_shader.setVec3("view_pos", cam.getCamPos());
	
	// ============================================================
	/* Game loop */
	// ============================================================
	while (!glfwWindowShouldClose(mainWindow)) {
		// delta time setup
		float curr = (float)glfwGetTime();
		delta = curr - last;
		last = curr;

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		/* INIT RENDERER */
		Renderer::init(cam);
		/* UPDATES */
		cam.update(mainWindow, delta);
		Collision::updateCollisions(cam);
		
		
		// set light pos
		if (glfwGetKey(mainWindow, GLFW_KEY_E) == GLFW_PRESS) {			
			M_LIGHT.getPosition() = cam.getCamPos(); // Set light position to current camera position
			light_trans = glm::translate(glm::mat4(1.0f), M_LIGHT.getPosition());

			// update light position uniform in shaders
			lit_shader.bind();
			lit_shader.setVec3("light_pos", M_LIGHT.getPosition()); 

			shader.bind();
			shader.setVec3("light_pos", M_LIGHT.getPosition()); // update light position uniform
		}
		lit_shader.bind();
		lit_shader.setVec3("view_pos", cam.getCamPos());
		
		/* DRAW RENDERABLES FROM ACTIVE SCENE */
		Renderer::renderTexModel(shader, M_FLOOR, floor_trans);
		//Renderer::renderTexModel(shader, M_CUBE, cube_trans);
		Renderer::renderModel(lit_shader, M_CUBE, cube_trans);
		Renderer::renderModel(light_shader, M_LIGHT, light_trans);
		Renderer::renderTexModel(shader, M_CUBE2, cube2_trans);
		
		Renderer::renderSkybox(skybox_shader, sky); // render skybox last
		
		
		
		/* Swap buffers */
		glfwSwapBuffers(mainWindow);

		// PROCESS INPUT (TEMP)
		glfwPollEvents();
		
		
	}

	glfwTerminate();
	return 0;
}


/* --------------------------- TEMPORARY - DEFINE CALLBACKS ----------------------  */
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
