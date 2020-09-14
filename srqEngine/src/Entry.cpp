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
	GLFWwindow* mainWindow = glfwCreateWindow(800, 600, "srqEngine", NULL, NULL);
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
	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	/* Setup shaders */
	
	Shader shader = Shader("res/shaders/vertexgen.shader", "res/shaders/fragmentgen.shader");
	
	
	//									MODEL LOADING TEST										//
	// ==========================================================================================
	
	Model model = Model("res/models/weird.obj");
	std::vector<glm::vec3> vert = model.getVertices();
	std::vector<glm::vec2> tex = model.getTextureCoords();
	std::vector<glm::vec3> norm = model.getNormalCoords();
	
	std::vector<float> pvalues;
	std::vector<float> tvalues;
	std::vector<float> nvalues;
	
	for (int i = 0; i < model.getTotalVectors(); i++) {
		pvalues.push_back((vert[i]).x);
		pvalues.push_back((vert[i]).y);
		pvalues.push_back((vert[i]).z);
		tvalues.push_back((tex[i]).s);
		tvalues.push_back((tex[i]).t);
		nvalues.push_back((norm[i]).x);
		nvalues.push_back((norm[i]).y);
		nvalues.push_back((norm[i]).z);
	}
	
	std::cout << model.getTotalVectors() << std::endl;
	
	// ==========================================================================================//


	
	/* TEMP - VAO/VBO/Data init */
	std::shared_ptr<VertexBuffer> vb = std::make_shared<VertexBuffer>(&pvalues[0], (unsigned int)(pvalues.size()*sizeof(unsigned int)));
	std::shared_ptr<VertexBuffer> vb2 = std::make_shared<VertexBuffer>(&tvalues[0], (unsigned int)(tvalues.size()*sizeof(unsigned int)));
	
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

	VertexArray va = VertexArray();
	va.addVBOSingleAttrib(vb, 0);
	va.addVBOSingleAttrib(vb2, 1);

	Texture t = Texture("res/textures/logo.png");
	t.bind(0);

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
		Renderer::render(shader, va);

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
