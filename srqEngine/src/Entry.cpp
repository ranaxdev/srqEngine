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
#include "Renderer_API/ParticleGen.h"

#include "Camera.h"

// ------------------------------------------------

/* GLOBALS */
extern const int MAX_ENTITIES;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

float delta = 0.0f;
float last = 0.0f;
float ambience = 1.0f;

bool enableParticle = false;
bool enableLights = false;
bool renderScene = false;

const double FPS_MAX = 60.0;
const double INTERVAL_MAX = 1.0 / FPS_MAX;

/*---------------- TEMPORARY - callback declarations ------------------- */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

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
	glfwSetKeyCallback(mainWindow, key_callback);

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

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_CCW);
	//									LOAD MODELS     										//
	// ==========================================================================================
	// ~t e x t u r e d~
	Model M_FLOOR = Model("res/models/floor.obj", "res/textures/floor.png", glm::vec3(30.0f, 30.0f, 1.0f), false);
	Model M_CUBE = Model("res/models/cube2.obj", "res/textures/brick.png", glm::vec3(1.0f, 1.0f, 1.0f), true); /* Set Color: */ M_CUBE.setColor(0.1f, 0.8f, 0.3f);
	Model M_LIGHT = Model("res/models/light.obj", "res/textures/brick.png", glm::vec3(0.5f, 0.5f, 0.5f), false); /* Set Color: */ M_LIGHT.setColor(0.6f, 1.0f, 1.0f);
	Model M_CUBE2 = Model("res/models/cube2.obj", "res/textures/brick.png", glm::vec3(1.0f, 1.0f, 1.0f), true);
	Model M_TERRAIN = Model("res/models/terrain.obj", "res/textures/brick.png", glm::vec3(1.0f, 1.0f, 1.0f), false);
		// showcase models
	Model M_ANIME = Model("res/models/anime.obj", "res/textures/anime.png", glm::vec3(1.0f, 1.0f, 1.0f), false);
	Model M_DOOR = Model("res/models/door.obj", "res/textures/door.png", glm::vec3(1.0f, 1.0f, 1.0f), false);
	Model M_GUIN = Model("res/models/penguin.obj", "res/textures/penguin.png", glm::vec3(1.0f, 1.0f, 1.0f), false);

	// ~p l a i n~
	Skybox sky = Skybox("skybox");
	ParticleGen M_PARTICLE = ParticleGen();
	// bind them (initialization - association with VAOs)
	M_FLOOR.bind();
	M_CUBE.bind();
	M_CUBE2.bind();
	M_LIGHT.bind();
	M_TERRAIN.bind();
	M_ANIME.bind();
	M_DOOR.bind();
	M_GUIN.bind();
	/* -----------------------------Transformations---------------------- */
	//M_CUBE.getPosition().z -= 10;
	glm::mat4 cube_trans = glm::translate(glm::mat4(1.0f), M_CUBE.getPosition()); /* Cube 1 model */


	M_LIGHT.getPosition().x += 5.0f;
	M_LIGHT.getPosition().z += 2.0f;
	M_LIGHT.getPosition().y -= 10.0f;
	glm::mat4 light_trans = glm::translate(glm::mat4(1.0f), M_LIGHT.getPosition()); /* Light source model */

	M_FLOOR.getPosition().y -= 1.0f;
	glm::mat4 floor_trans = glm::translate(glm::mat4(1.0f), M_FLOOR.getPosition()); /* Floor model */


	M_CUBE2.getPosition().x += 5.0f;
	M_CUBE2.getPosition().z += 220.0f;
	glm::mat4 cube2_trans = glm::translate(glm::mat4(1.0f), M_CUBE2.getPosition()); /* Cube 2 model */

	M_TERRAIN.getPosition().x -= 10.0f;
	M_TERRAIN.getPosition().z -= 30.0f;
	M_TERRAIN.getPosition().y -= 2.0f;
	glm::mat4 torus_trans = glm::translate(glm::mat4(1.0f), M_TERRAIN.getPosition()); /* Terrain model */
	
	M_PARTICLE.getPosition().y += 5.0f;
	M_PARTICLE.getPosition().z -= 10.0f;
	glm::mat4 particle_trans = glm::translate(glm::mat4(1.0f), M_PARTICLE.getPosition()); /* Particle model */

	M_ANIME.getPosition().x += 20.0f;
	M_ANIME.getPosition().y -= 1.0f;
	glm::mat4 anime_trans = glm::translate(glm::mat4(1.0f), M_ANIME.getPosition()); /* Anime model */
	anime_trans = glm::scale(anime_trans, glm::vec3(0.3f, 0.3f, 0.3f));

	M_DOOR.getPosition().x += 20.0f;
	M_DOOR.getPosition().y -= 0.8f;
	M_DOOR.getPosition().z -= 5.0f;
	glm::mat4 door_trans = glm::translate(glm::mat4(1.0f), M_DOOR.getPosition()); /* Anime model */
	door_trans = glm::scale(door_trans, glm::vec3(0.3f, 0.3f, 0.3f));

	M_GUIN.getPosition().x += 20.0f;
	M_GUIN.getPosition().y -= 0.8f;
	M_GUIN.getPosition().z += 5.0f;
	glm::mat4 guin_trans = glm::translate(glm::mat4(1.0f), M_GUIN.getPosition()); /* Anime model */
	//guin_trans = glm::scale(guin_trans, glm::vec3(0.3f, 0.3f, 0.3f));


	/* --------------------------------------Shader declarations------------------------------ */
	Shader shader = Shader("res/shaders/vertexgen.shader", "res/shaders/fragmentgen.shader");
	Shader skybox_shader = Shader("res/shaders/skybox/sky_vert.shader", "res/shaders/skybox/sky_frag.shader");
	Shader lit_shader = Shader("res/shaders/lit/lit_vert.shader", "res/shaders/lit/lit_frag.shader");
	Shader light_shader = Shader("res/shaders/light/light_vert.shader", "res/shaders/light/light_frag.shader");
	Shader particle_shader = Shader("res/shaders/particle/particle_vert.shader", "res/shaders/particle/particle_frag.shader");
	// ==================================== Shader configurations ===================================
	shader.bind();
	shader.setVec3("light_color", M_LIGHT.getColor());
	shader.setVec3("light_pos", M_LIGHT.getPosition());
	shader.setFloat("intensity", ambience);

	skybox_shader.bind();
	skybox_shader.setInt("skybox", 0);

	lit_shader.bind();
	lit_shader.setVec3("obj_color", M_CUBE.getColor());
	lit_shader.setVec3("light_color", M_LIGHT.getColor());
	lit_shader.setVec3("light_pos", M_LIGHT.getPosition());
	lit_shader.setVec3("view_pos", cam.getCamPos());
	lit_shader.setFloat("intensity", ambience);
	
	// ============================================================
	/* Game loop */
	// ============================================================
	while (!glfwWindowShouldClose(mainWindow)) {
		// delta time setup
		float curr = (float)glfwGetTime();
		delta = curr - last;
		
		if (delta >= INTERVAL_MAX) {
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
			lit_shader.setFloat("intensity", ambience);

			shader.bind();
			shader.setFloat("intensity", ambience);

			M_PARTICLE.update(delta);

			/* SHOWCASE MODEL TRANSFORMS */
			float angle = 0.1f;
			angle += delta;
			anime_trans = glm::rotate(anime_trans, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
			door_trans = glm::rotate(door_trans, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
			guin_trans = glm::rotate(guin_trans, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));


			/* DRAW RENDERABLES FROM ACTIVE SCENE */
			Renderer::renderTexModel(shader, M_FLOOR, floor_trans);

			if(renderScene){
			Renderer::renderTexModel(shader, M_ANIME, anime_trans);
			Renderer::renderTexModel(shader, M_DOOR, door_trans);
			Renderer::renderTexModel(shader, M_GUIN, guin_trans);


			Renderer::renderModel(lit_shader, M_TERRAIN, torus_trans);
			Renderer::renderModel(lit_shader, M_CUBE, cube_trans);
			}

			if (enableLights) {
			Renderer::renderModel(light_shader, M_LIGHT, light_trans); // render light source
			}

			Renderer::renderTexModel(shader, M_CUBE2, cube2_trans);
		
			if (enableParticle) {
				Renderer::renderParticle(particle_shader, M_PARTICLE, particle_trans);
			}
		
			Renderer::renderSkybox(skybox_shader, sky); // render skybox last
		

			/* Swap buffers */
			glfwSwapBuffers(mainWindow);

			// PROCESS INPUT (TEMP)
			glfwPollEvents();
		
			last = curr;
		}
		
	}
	glfwTerminate();
	return 0;
}


/* --------------------------- TEMPORARY - DEFINE CALLBACKS ----------------------  */
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		enableParticle = true;
	}
	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		ambience = 0.1f;
		enableLights = true;
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		renderScene = true;
	}


	/* Control ambience */
	if (key == GLFW_KEY_LEFT_BRACKET && action == GLFW_PRESS) {
		ambience -= 0.1f;
	}
	if (key == GLFW_KEY_RIGHT_BRACKET && action == GLFW_PRESS) {
		ambience+= 0.1f;
	}

}





