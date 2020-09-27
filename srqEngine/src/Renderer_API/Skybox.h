#ifndef _H_SKYBOX_
#define _H_SKYBOX_

#include<vector>
#include<string>
#include "VertexArray.h"
class Skybox
{
public:
	Skybox(std::string dir_name);
	~Skybox();

	void bind() const;
	void unbind() const;

	VertexArray& getVA();

private:
	unsigned int ID;
	VertexArray va;
	std::vector<std::string> face_names;
};

#endif