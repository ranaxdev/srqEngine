#ifndef _H_BUFFER
#define _H_BUFFER

#include<string>
#include<vector>

/* Buffer Layout Class & Supplements */

enum class DataType { Float, Float2, Float3, Float4, Mat3, Mat4 }; // To match shader data types
// size of each type in bytes
static unsigned int DataTypeSize(DataType type) {
	switch (type)
	{
	case DataType::Float:    return 4;
	case DataType::Float2:   return 4 * 2;
	case DataType::Float3:   return 4 * 3;
	case DataType::Float4:   return 4 * 4;
	case DataType::Mat3:     return 4 * 3 * 3;
	case DataType::Mat4:     return 4 * 4 * 4;

	}
}

struct BufferElement {
	std::string name;
	unsigned int offset;
	unsigned int size;
	unsigned int count;
	bool normalized;
	DataType type;

	BufferElement(DataType type, const std::string& name)
		: name(name), type(type), size(DataTypeSize(type)), offset(0), count(size/4), normalized(false)
		// NOTE: CHANGE /4 LATER DEPENDING ON THE ACTUAL BYTE SIZE OF PRIMITIVE  ^^^^
		// Better way is to create func getElementCount and define each with switch(type)
	{}
};
class BufferLayout {

public:
	BufferLayout(const std::initializer_list<BufferElement>& elements);

	unsigned int getStride() const;

	// iters
	std::vector<BufferElement>::iterator begin() { return elements.begin(); }
	std::vector<BufferElement>::iterator end() { return elements.end(); }

private:
	std::vector<BufferElement> elements;
	unsigned int stride = 0;
	
	void calcStrideOffset(); // Does so for each element in vec bufferelement
	
};



// 
// 
// 
//
//


/* Vertex Buffer Class */
class VertexBuffer
{
public:
	VertexBuffer(float* vertices, unsigned int size);
	~VertexBuffer();

	void bind() const;
	void unbind() const;


private:
	unsigned int ID;
};


// 
// 
// 
//
//


/* Index Buffer Class */
class IndexBuffer
{
public:
	IndexBuffer(unsigned int* indices, unsigned int count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	unsigned int getCount() const;

private:
	unsigned int count;
	unsigned int ID;
};


#endif
