#include<glad/glad.h>
#include "Renderable.h"
#include<iostream>
/* Global identifer - a renderable has ID 0 */
const unsigned int Renderable::m_ID = 0;

/* Process positional data and entity ID, and associate it with an entity */
Renderable::Renderable(const int belongsTo, float* vertices, unsigned int* indices, float* texcoords)
	: pos_data(vertices), indices(indices), texcoords(texcoords)
{
	Renderable::m_attachedEntityID = belongsTo;
	std::cout << "[RENDERABLE] SUCCESSFULLY ATTACHED TO ENTITY: " << Renderable::m_attachedEntityID << std::endl;

	/* Generate VAO for this renderable entity */
	glGenVertexArrays(1, &(Renderable::VAO));
};


/* Parse and store pos/tex data into VBO/EBO into VAO */
void Renderable::setupRenderable() {
	// bind VAO to work on it
	glBindVertexArray(Renderable::VAO);

	// Generate VBO, EBO for positional data 
	unsigned int VBO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind VBO, EBO buffers
	glBindBuffer(VBO, GL_ARRAY_BUFFER);
	glBindBuffer(EBO, GL_ELEMENT_ARRAY_BUFFER);

	// Parse data into index and position buffers
	glBufferData(GL_ARRAY_BUFFER, sizeof(Renderable::pos_data), Renderable::pos_data, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Renderable::indices), Renderable::indices, GL_STATIC_DRAW);

	// Setup different attribs: position, texture
	// POSITION
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
	// TEXTURE
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);

}