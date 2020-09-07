#include<glad/glad.h>
#include<iostream>
#include "Renderer.h"
#include "Util/Shader.h"
#include "Util/Globals.h"
#include "Util/VertexBuffer.h"
#include "SceneMgmt/Entity.h"

/* GLOBALS */
extern const int MAX_ENTITIES;


/* Constructor*/
// Render the currently active scene
Renderer::Renderer(GLFWwindow* window) : window(window) {
	
}

void Renderer::render() {
}

/* Destructor */
Renderer::~Renderer() {}