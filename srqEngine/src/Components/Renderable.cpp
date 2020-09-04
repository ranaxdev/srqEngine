#include "Renderable.h"
#include<iostream>
/* Global identifer - a renderable has ID 0 */
const unsigned int Renderable::m_ID = 0;


/* Constructor - positional data */
Renderable::Renderable(const int belongsTo, const float* vertices, const unsigned int* indices){
	Renderable::m_attachedEntityID = belongsTo;
	std::cout << "[RENDERABLE] SUCCESS" << std::endl;
	std::cout << "Attached to entity ID: " << Renderable::m_attachedEntityID << std::endl;
};
