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

	/* Setup shaders */
	
	Shader shader = Shader("res/shaders/vertexgen.shader", "res/shaders/fragmentgen.shader");
	
	
	//									LOAD MODELS     										//
	// ==========================================================================================
	
	Model M_FLOOR = Model("res/models/floor.obj", "res/textures/floor.png"); // uses floor texture
	Model M_WALL = Model("res/models/map.obj", "res/textures/brick.png");
	Model M_PYR = Model("res/models/pyr.obj", "res/textures/pyr.png");

	// ==========================================================================================//

	/* VAO/VBO/Data init */
	VertexArray va = VertexArray();
	/* DATA FOR FLOOR */
	std::shared_ptr<VertexBuffer> vb = std::make_shared<VertexBuffer>(&(M_FLOOR.v_values[0]), (unsigned int)(M_FLOOR.v_values.size()*sizeof(unsigned int)));
	std::shared_ptr<VertexBuffer> vb2 = std::make_shared<VertexBuffer>(&(M_FLOOR.t_values[0]), (unsigned int)(M_FLOOR.v_values.size()*sizeof(unsigned int)));
	vb->setlayout(
		{
			{DataType::Float3, "a_Pos"}
		}
	);
	vb2->setlayout(
		{
			{DataType::Float2, "a_Tex"}
		}
	);
	va.addVBOSingleAttrib(vb, 0);
	va.addVBOSingleAttrib(vb2, 1);

	/* DATA FOR WALLS */
	VertexArray va2 = VertexArray();
	std::shared_ptr<VertexBuffer> vb3 = std::make_shared<VertexBuffer>(&(M_WALL.v_values[0]), (unsigned int)(M_WALL.v_values.size() * sizeof(unsigned int)));
	std::shared_ptr<VertexBuffer> vb4 = std::make_shared<VertexBuffer>(&(M_WALL.t_values[0]), (unsigned int)(M_WALL.v_values.size() * sizeof(unsigned int)));
	vb3->setlayout(
		{
			{DataType::Float3, "a_Pos"}
		}
	);
	vb4->setlayout(
		{
			{DataType::Float2, "a_Tex"}
		}
	);
	va2.addVBOSingleAttrib(vb3, 0);
	va2.addVBOSingleAttrib(vb4, 1);

	/* DATA FOR PYRAMID */
	VertexArray va3 = VertexArray();
	std::shared_ptr<VertexBuffer> vb5 = std::make_shared<VertexBuffer>(&(M_PYR.v_values[0]), (unsigned int)(M_PYR.v_values.size() * sizeof(unsigned int)));
	std::shared_ptr<VertexBuffer> vb6 = std::make_shared<VertexBuffer>(&(M_PYR.t_values[0]), (unsigned int)(M_PYR.v_values.size() * sizeof(unsigned int)));
	vb5->setlayout(
		{
			{DataType::Float3, "a_Pos"}
		}
	);
	vb6->setlayout(
		{
			{DataType::Float2, "a_Tex"}
		}
	);
	va3.addVBOSingleAttrib(vb5, 0);
	va3.addVBOSingleAttrib(vb6, 1);


	/* Model transforms (refactor later) */
	// Floor model transforms: move down
	glm::mat4 trans_M_FLOOR = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,-0.5f,0.0f));
	// Wall model transform: move down
	glm::mat4 trans_M_WALL = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.5f, 0.0f));
	glm::mat4 trans_M_PYR = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.5f, 0.0f));

	// ============================================================
	/* Game loop */
	// ============================================================
	while (!glfwWindowShouldClose(mainWindow)) {
		// delta time setup
		float curr = glfwGetTime();
		delta = curr - last;
		last = curr;


		glClearColor(0.2f, 0.3f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* INIT RENDERER */
		Renderer::init(cam);

		/* DRAW RENDERABLES FROM ACTIVE SCENE */
		Renderer::render(shader, va, M_FLOOR, trans_M_FLOOR);
		
		Renderer::render(shader, va2, M_WALL, trans_M_WALL);

		Renderer::render(shader, va3, M_PYR, trans_M_PYR);

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
