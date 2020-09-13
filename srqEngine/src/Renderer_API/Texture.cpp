#include<glad/glad.h>
#include "../temp/stb_image.h"
#include "Texture.h"


Texture::Texture(const char* filepath) : 
	ID(0),filepath(filepath), localBuffer(nullptr),width(0), height(0), BPP(0)
{
	// load image
	stbi_set_flip_vertically_on_load(1); // flip img because of PNG format
	localBuffer = stbi_load(Texture::filepath, &(Texture::width), &(Texture::height), &(Texture::BPP), 4);

	// generate and bind texture by default
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	// set texture settings
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// process texture buffer data 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Texture::width, Texture::height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	// free image data memory
	stbi_image_free(localBuffer);
}

Texture::~Texture() {
	glDeleteTextures(1, &ID);
}


/* Bind and unbind textures from texture slots */
void Texture::bind(unsigned int slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}


/* GETTERS */
int Texture::getWidth() const { return Texture::width; }
int Texture::getHeight() const { return Texture::height; }