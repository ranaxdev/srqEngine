#ifndef _H_TEXTURE
#define _H_TEXTURE

class Texture {
public:
	Texture(const char* filepath);
	~Texture();

	void bind(unsigned int slot) const;
	void unbind() const;

	int getWidth() const;
	int getHeight() const;

private:
	unsigned int ID;
	const char* filepath;
	unsigned char* localBuffer;
	int width, height, BPP;

};

#endif