#include<glad/glad.h>
#include "VertexArray.h"
#include "../Util/Globals.h"

VertexArray::VertexArray() {
	// not bound by default
	glGenVertexArrays(1, &(VertexArray::ID));

}


VertexArray::~VertexArray() {}


void VertexArray::bind() const { glBindVertexArray(VertexArray::ID); }

void VertexArray::unbind() const { glBindVertexArray(0); }


/* Binding done here, Adds to vbo vector, must have valid layout */
void VertexArray::addVBO(const std::shared_ptr<VertexBuffer>& vbo) {
	// assert layout has size > 0 here
	//
	//********************************

	glBindVertexArray(VertexArray::ID);
	vbo->bind();

	unsigned int index = 0;
	for (const auto& element : vbo->getlayout()) {
		glVertexAttribPointer(index, element.count, GL_DATA_TYPE_LOOKUP(element.type), element.normalized ? GL_TRUE : GL_FALSE, vbo->getlayout().getStride(), (const void*)(element.offset));
		glEnableVertexAttribArray(index);
		index++;
	}
	// store vbo in vec
	VertexArray::vbuffers.push_back(vbo);
}


/* To read chunks from vertices */
void VertexArray::setEBO(const std::shared_ptr<IndexBuffer>& ebo) {
	glBindVertexArray(VertexArray::ID);
	ebo->bind();
	VertexArray::ibuffer = ebo;
}


/* GETTERS */
const std::vector<std::shared_ptr<VertexBuffer>> VertexArray::getVBOs() const { return VertexArray::vbuffers; }
const std::shared_ptr<IndexBuffer> VertexArray::getEBO() const { return VertexArray::ibuffer;  }

