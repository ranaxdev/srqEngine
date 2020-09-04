#ifndef _H_SHADER
#define _H_SHADER

class Shader {
public:
	unsigned int ID;

	Shader(const char* vshaderPath, const char* fshaderPath);
	void use();
	void setInt(const char* name, int val);
	void setFloat(const char* name, float val);
	


private:
	void compileErrorChecking(unsigned int shader, const char* type);
};

#endif