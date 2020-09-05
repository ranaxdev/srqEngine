#ifndef _H_RENDERABLE
#define _H_RENDERABLE

class Renderable {
public:
	static const unsigned int m_ID;
	int m_attachedEntityID;
	float* pos_data;
	unsigned int* indices;
	float* texcoords;

	Renderable(const int belongsTo, float* vertices, unsigned int* indices, float* texcoords);

private:
	void setupRenderable();
	unsigned int VAO;
};

#endif