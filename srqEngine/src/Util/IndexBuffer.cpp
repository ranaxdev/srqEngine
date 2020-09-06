#include<glad/glad.h>
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : count(count) {
	glGenBuffers(1, &(IndexBuffer::ID));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer::ID); // bound by default
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
	/*
	Note:
	- Using GLuint instead of unsigned int this time because compiler may make it a different size
	  depending on platform
	*/
}


/* Bind and unbind EBO to GL_ELEMENT_ARRAY_BUFFER*/
void IndexBuffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer::ID);
}

void IndexBuffer::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/* Return the index count */
unsigned int IndexBuffer::getCount() const {
	return IndexBuffer::count;
}