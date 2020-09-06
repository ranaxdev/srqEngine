#ifndef _H_RENDERABLE
#define _H_RENDERABLE

struct Renderable {
	static const unsigned int m_ID;
	int m_attachedEntityID;
	float* pos_data;
	unsigned int* indices;
	float* texcoords;

	Renderable(const int belongsTo, float* vertices, unsigned int* indices, float* texcoords);
};

#endif