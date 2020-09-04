#ifndef _H_RENDERABLE
#define _H_RENDARABLE

struct Renderable {
	/* Identifier */
	static const unsigned int m_ID;
	/* Entity ID it is attached to */
	int m_attachedEntityID;
	
	/* Constructor */
	Renderable(const int belongsTo, const float* vertices, const unsigned int* indices);

};

#endif