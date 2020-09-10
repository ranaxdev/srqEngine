#include <glad/glad.h>
#include "Buffer.h"

// **************** BUFFER LAYOUT CLASS ********************
// *********************************************************
BufferLayout::BufferLayout() {}
BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements) 
	: elements(elements)
{
	BufferLayout::calcStrideOffset();
}

void BufferLayout::calcStrideOffset() {
	unsigned int offset = 0;
	for (auto& e : elements) {
		e.offset = offset;
		offset += e.size;
		BufferLayout::stride += e.size;
	}
}

unsigned int BufferLayout::getStride() const {
	return BufferLayout::stride;
}

// **************** VERTEX BUFFER CLASS ********************
// *********************************************************

VertexBuffer::VertexBuffer(float* vertices, unsigned int size) {
	glGenBuffers(1, &(VertexBuffer::ID));
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer::ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	VertexBuffer::layout = {}; // empty layout by default
}

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &(VertexBuffer::ID)); }

void VertexBuffer::bind() const { glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer::ID); }
void VertexBuffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VertexBuffer::setlayout(const BufferLayout& layout) { VertexBuffer::layout = layout; }
BufferLayout VertexBuffer::getlayout() const { return layout; }


// **************** INDEX BUFFER CLASS ********************
// *********************************************************
IndexBuffer::IndexBuffer(unsigned int* indices, unsigned int count) : count(count) {
	glGenBuffers(1, &(IndexBuffer::ID));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer::ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &(IndexBuffer::ID)); }

void IndexBuffer::bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer::ID); }
void IndexBuffer::unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

unsigned int IndexBuffer::getCount() const {
	return IndexBuffer::count;
}

