#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include "Renderer.h"
#include "SceneMgmt/Entity.h"
#include "SceneMgmt/Scene.h"


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
	glfwMakeContextCurrent(mainWindow);

	/* Load glad */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "[ERROR] Failed to init GLAD!" << std::endl;
	}

	/* Config OpenGL options */
	glViewport(0, 0, 800, 600);

	/* Init renderer */
	float data[] = { 23,67,44,12 };
	unsigned int idx[] = { 1,2,3 };
	float tex[] = { 2,3,1 };
	Scene s1 = Scene();
	Scene::setActiveScene(&s1);
	
	Entity e1 = Entity();
	e1.addComponent(Entity::ComponentType::RENDERABLE, e1.getID(), data, idx, tex);
	
	std::cout << s1.renderables[0] << std::endl;

	Renderer r(mainWindow);
	
	glfwTerminate();
	return 0;
}