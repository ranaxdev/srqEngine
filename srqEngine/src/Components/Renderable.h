#ifndef _H_RENDERABLE
#define _H_RENDARABLE

struct Renderable {
	/* Identifier */
	static const unsigned int m_ID;
	/* Constructor takes in positional vertex/index data */
	Renderable(const float vertices[], const unsigned int indicies[]);

};

#endif