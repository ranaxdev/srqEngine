#ifndef _H_VERTEXARRAY
#define _H_VERTEXARRAY

#include "Buffer.h"

#include<vector>
#include<memory>

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;

	void addVBO(const std::shared_ptr<VertexBuffer>& vbo);
	void setEBO(const std::shared_ptr<IndexBuffer>& ebo);

	void addVBOSingleAttrib(const std::shared_ptr<VertexBuffer>& vbo, unsigned int index);

	const std::vector<std::shared_ptr<VertexBuffer>> getVBOs() const;
	const std::shared_ptr<IndexBuffer> getEBO() const;

	
private:
	unsigned int ID;
	std::vector<std::shared_ptr<VertexBuffer>> vbuffers;
	std::shared_ptr<IndexBuffer> ibuffer;
};

#endif