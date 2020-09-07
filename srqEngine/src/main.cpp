#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include<iostream>
#include "Renderer.h"
#include "Util/Globals.h"
#include "Util/Shader.h"
#include "Util/VertexBuffer.h"
#include "Util/Texture.h"
#include "SceneMgmt/Entity.h"

/* GLOBALS */
extern const int MAX_ENTITIES;

/*---------------- TEMPORARY - callback declarations ------------------- */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

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

	/* Init renderer */
	Renderer r = Renderer();
	
	/* Define model data*/
	float pos_data[] = { 
		-0.5f,0.5f,0.0f, 0.0f, 0.0f,
		-0.5,0.0f,0.0f,  1.0f, 0.0f,
		0.0f,0.0f,0.0f,  0.0f, 1.0f };

	float pos_data2[] = { 
		0.0,0.5f,0.0f, 0.0f, 0.0f,
		-0.5,0.0f,0.0f, 1.0f, 0.0f,
		0.5f,0.0f,0.0f, 0.0f, 1.0f };
	unsigned int idx[] = { 0,0,0 };
	float tex[] = { 0,0,0 };
	
	/* Link shader and use it*/
	Shader shader = Shader("res/shaders/vertexgen.shader", "res/shaders/fragmentgen.shader");
	shader.bind();
	
	/* ECS Init, bind entities to scene and add componenets to them */
	Scene s1 = Scene();
	Entity e1 = Entity(&s1);
	Entity e2 = Entity(&s1);
	
	Scene::setActiveScene(&s1); // set scene as active 

	e1.addComponent(Entity::ComponentType::RENDERABLE, e1.getID(), pos_data, idx, tex);
	e2.addComponent(Entity::ComponentType::RENDERABLE, e2.getID(), pos_data2, idx, tex);
	
	/* bind and parse renderable objects */
	unsigned int VAO[MAX_ENTITIES];
	glGenVertexArrays(Scene::getActiveScene()->renderables.size(), VAO);

	for (int i = 0; i < Scene::getActiveScene()->renderables.size(); i++) {
		glBindVertexArray(VAO[i]);
		VertexBuffer vbo = VertexBuffer(Scene::getActiveScene()->renderables[i].pos_data, 15*sizeof(float));
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)0);
		glEnableVertexAttribArray(0);
		
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	
	/* ********************** TEMP: TEXTURES (REFACTOR LATER) ********************** */
	Texture logoTex = Texture("res/textures/logo.png");
	logoTex.bind(0);
	shader.setInt("logoTex", 0);
	/* **********************************************************************************/


	/* MVP Transformation/uniform setting */
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, -.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)(800.0f / 600.0f), 0.1f, 100.0f);

	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);

	

	/* Main loop */
	while (!glfwWindowShouldClose(mainWindow)) {
		glClearColor(0.2f, 0.3f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* DRAW RENDERABLES FROM ACTIVE SCENE */
		r.render(VAO, Scene::getActiveScene()->renderables.size());

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