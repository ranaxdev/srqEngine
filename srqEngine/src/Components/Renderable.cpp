#include "Renderable.h"
#include<iostream>
/* Global identifer - a renderable has ID 0 */
const unsigned int Renderable::m_ID = 0;

/* Process positional data and entity ID, and associate it with an entity */
Renderable::Renderable(const int belongsTo, float* vertices, unsigned int* indices, float* texcoords)
	: m_attachedEntityID(belongsTo), pos_data(vertices), indices(indices), texcoords(texcoords)
{
	std::cout << "[RENDERABLE] SUCCESSFULLY ATTACHED TO ENTITY: " << Renderable::m_attachedEntityID << std::endl;
};

