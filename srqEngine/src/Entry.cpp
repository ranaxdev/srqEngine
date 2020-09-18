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

	/* --------------------------------------Shader declarations------------------------------ */
	Shader shader = Shader("res/shaders/vertexgen.shader", "res/shaders/fragmentgen.shader");
	Shader lightShader = Shader("res/shaders/vertexlight.shader", "res/shaders/fragmentlight.shader");
	Shader lightsourceShader = Shader("res/shaders/vertexlight.shader", "res/shaders/lightsourcefragment.shader");
	// ==================================== Shader configurations ===================================
	// light shader
	glm::vec3 lightcolor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 objcolor = glm::vec3(1.0f, 0.5f, 0.33f);
	auto lightcolorFunc = [&]() {lightShader.setVec3("obj_light", lightcolor); };
	auto objcolorFunc = [&]() {lightShader.setVec3("lightColor", objcolor); };
	lightShader.config.push_back(lightcolorFunc);
	lightShader.config.push_back(objcolorFunc);
	
	
	/*-------------------------------------------------------------------------------------------*/


	//									LOAD MODELS     										//
	// ==========================================================================================
	// declare models
	Model M_FLOOR = Model("res/models/floor.obj", "res/textures/floor.png"); // uses floor texture
	Model M_WALL = Model("res/models/map.obj", "res/textures/brick.png");
	Model M_PYR = Model("res/models/pyr.obj", "res/textures/pyr.png");
	// bind them (initialization - association with VAOs)
	M_FLOOR.bind();
	M_WALL.bind();
	M_PYR.bind();

	// ==========================================================================================//
	float cubeData[] = {
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,

	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,

	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f
	};
	VertexArray va = VertexArray();
	std::shared_ptr<VertexBuffer> vb = std::make_shared<VertexBuffer>(cubeData, sizeof(cubeData));
	vb->setlayout(
		{
			{DataType::Float3, "a_Pos"}
		}
	);
	va.addVBO(vb);


	/* -----------------------------Transformations---------------------- */
	// light source transforms
	glm::vec3 lightsourcePos = glm::vec3(1.2f, 1.0f, 2.0f);
	glm::mat4 trans_lightsrc = glm::translate(glm::mat4(1.0f), lightsourcePos);
	trans_lightsrc = glm::scale(trans_lightsrc, glm::vec3(0.2f));
	// ---------------------------------------------------------------------


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
		/* DRAW RENDERABLES FROM ACTIVE SCENE */
		// render light source 
		Renderer::renderPlain(lightsourceShader, va, trans_lightsrc);

		//render light (set uniforms before)
		Renderer::renderPlain(lightShader, va);

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
