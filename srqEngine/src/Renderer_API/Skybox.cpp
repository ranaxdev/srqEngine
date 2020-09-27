#include "Skybox.h"
#include<glad/glad.h>
#include<iostream>
#include "../temp/stb_image.h"

/* Load cube map and create cube & setup texture */
Skybox::Skybox(std::string dir_name) {

	// texture names in directory
	std::string dir = "res/textures/" + dir_name + "/";
	Skybox::face_names = {
		dir + "right.jpg",
		dir + "left.jpg",
		dir + "top.jpg",
		dir + "bottom.jpg",
		dir + "front.jpg",
		dir + "back.jpg"
	};
    
	// load in face textures
	glGenTextures(1, &(Skybox::ID));
	glBindTexture(GL_TEXTURE_CUBE_MAP, Skybox::ID);
	int width, height, channels;

	for (unsigned int i = 0; i < face_names.size(); i++) { // load data for each face
        stbi_set_flip_vertically_on_load(0);
		unsigned char* face_data = stbi_load(face_names[i].c_str(), &width, &height, &channels, 0);
        if (face_data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, face_data);
		    stbi_image_free(face_data);
        }
        else {
            std::cout << "Failed to load " << face_names[i] << std::endl;
            stbi_image_free(face_data);
        }
	}

	// filters
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	// setup VAO/VBO
    float vertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
    Skybox::va = VertexArray();
    std::shared_ptr<VertexBuffer> vb = std::make_shared<VertexBuffer>(vertices, (unsigned int)(sizeof(vertices)));
    vb->setlayout(
        {
            {DataType::Float3, "a_Pos"}
        }
    );
    Skybox::va.addVBO(vb);
}

Skybox::~Skybox() {
    glDeleteTextures(1, &(Skybox::ID));
}

void Skybox::bind() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, Skybox::ID);
}

void Skybox::unbind() const {
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

VertexArray& Skybox::getVA() {
	return Skybox::va;
}