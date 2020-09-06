#ifndef _H_VERTEXBUFFER
#define _H_VERTEXBUFFER

class VertexBuffer {
public:
	VertexBuffer(const void* data, unsigned int size);
	
	void bind() const;
	void unbind() const;

private:
	unsigned int ID;
};


#endif