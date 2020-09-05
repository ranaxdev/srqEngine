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

	float data2[] = { 2,2,2 };
	unsigned int idx2[] = { 0,2,3 };
	float tex2[] = { 0,0,0 };
	Scene s1 = Scene("SCENE_1");
	Scene s2 = Scene("SCENE_2");
	Scene::setActiveScene(&s1);
	
	Entity e1 = Entity(&s1);
	e1.addComponent(Entity::ComponentType::RENDERABLE, e1.getID(), data, idx, tex);
	
	Entity e2 = Entity(&s2);
	e2.addComponent(Entity::ComponentType::RENDERABLE, e2.getID(), data2, idx2, tex2);
	Scene::setActiveScene(&s2);
	std::cout << "\n\n";
	std::cout << Scene::getActiveScene()->name << std::endl;
	std::cout << Scene::getActiveScene()->renderables[0].pos_data[0] << std::endl;
	Renderer r(mainWindow);
	
	glfwTerminate();
	return 0;
}