#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include<iostream>
#include <functional>
#include<algorithm>

#include "Util/Globals.h"

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
float calcsign(float x) {
	return (x > 0) - (x < 0);
}
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
	Model M_FLOOR = Model("res/models/floor.obj", "res/textures/floor.png"); // uses floor texture
	Model M_CUBE = Model("res/models/cube2.obj", "res/textures/brick.png");
	// ~p l a i n~
	Skybox sky = Skybox("skybox");
	// bind them (initialization - association with VAOs)
	M_FLOOR.bind();
	M_CUBE.bind();

	/* -----------------------------Transformations---------------------- */
	//M_CUBE.getPosition().x += 5.0f;
	glm::mat4 cube_trans = glm::translate(glm::mat4(1.0f), M_CUBE.getPosition());
	M_FLOOR.getPosition().y -= 1.0f;
	glm::mat4 floor_trans = glm::translate(glm::mat4(1.0f), M_FLOOR.getPosition());
	
	/* --------------------------------------Shader declarations------------------------------ */
	Shader shader = Shader("res/shaders/vertexgen.shader", "res/shaders/fragmentgen.shader");
	Shader skybox_shader = Shader("res/shaders/skybox/sky_vert.shader", "res/shaders/skybox/sky_frag.shader");
	// ==================================== Shader configurations ===================================
	skybox_shader.bind();
	skybox_shader.setInt("skybox", 0);


	
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
		
		if ((cam.getCamPos().x >= M_CUBE.getPosition().x-1.5 && cam.getCamPos().x <= M_CUBE.getPosition().x + 1.5) &&
			(cam.getCamPos().y >= M_CUBE.getPosition().y-1.5 && cam.getCamPos().y <= M_CUBE.getPosition().y + 1.5) &&
			(cam.getCamPos().z >= M_CUBE.getPosition().z-1.5 && cam.getCamPos().z <= M_CUBE.getPosition().z + 1.5)) {
			float dx = -abs(cam.getCamPos()).x + (M_CUBE.getPosition().x+1.5);
			float dy = -abs(cam.getCamPos()).y + (M_CUBE.getPosition().y+1.5);
			float dz = -abs(cam.getCamPos()).z + (M_CUBE.getPosition().z+1.5);
			float min = std::min({ dx,dy,dz });
			
			//std::cout << "X: " << dx << " / Y: " << dy << " / Z: " << dz << std::endl;
			if (min == dx) {
				float sign = calcsign(cam.getCamFront().x);
				cam.setCamPos(glm::vec3(cam.getCamPos().x -(sign * 0.01), cam.getCamPos().y, cam.getCamPos().z));
			}

			if (min == dy) {
				float sign = calcsign(cam.getCamFront().y);
				cam.setCamPos(glm::vec3(cam.getCamPos().x, cam.getCamPos().y -(sign* 0.01), cam.getCamPos().z));
			}

			if (min == dz) {
				float sign = calcsign(cam.getCamFront().z);
				cam.setCamPos(glm::vec3(cam.getCamPos().x, cam.getCamPos().y, cam.getCamPos().z - (sign * 0.01)));
			}
			

		}
		/* DRAW RENDERABLES FROM ACTIVE SCENE */
		Renderer::renderTexModel(shader, M_FLOOR, floor_trans);
		Renderer::renderTexModel(shader, M_CUBE, cube_trans);
		
		Renderer::renderSkybox(skybox_shader, sky); // render skybox last
		
		
		
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
