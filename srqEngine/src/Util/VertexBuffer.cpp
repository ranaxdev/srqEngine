#include<glad/glad.h>
#include "VertexBuffer.h"

/* Generate and bind VBO*/
VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
	glGenBuffers(1, &(VertexBuffer::ID));
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer::ID); // bound by default
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

/* Bind and unbind VBO from GL_ARRAY_BUFFER */
void VertexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer::ID);
}

void VertexBuffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
