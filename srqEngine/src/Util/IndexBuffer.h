#ifndef _H_INDEXBUFFER
#define _H_INDEXBUFFER

class IndexBuffer {
public:
	IndexBuffer(const unsigned int* data, unsigned int count);

	void bind() const;
	void unbind() const;
	unsigned int getCount() const;

private:
	unsigned int ID;
	unsigned int count;
};


#endif