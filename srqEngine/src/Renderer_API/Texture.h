#ifndef _H_TEXTURE
#define _H_TEXTURE
#include<vector>

class Texture {
public:
	Texture(const char* filepath);
	~Texture();

	void bind() const;
	void unbind() const;

	int getWidth() const;
	int getHeight() const;

	static std::vector<unsigned int> slots;
private:
	unsigned int ID;
	const char* filepath;
	unsigned char* localBuffer;
	int width, height, BPP;
	

};

#endif