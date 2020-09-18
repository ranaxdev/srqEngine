#ifndef _H_SHADER
#define _H_SHADER
#include <glm/glm.hpp>
#include<vector>
#include<functional>

/* Shader class */

class Shader {
public:
	unsigned int ID;

	Shader(const char* vshaderPath, const char* fshaderPath);
	void bind() const;
	void unbind() const;

	void setInt(const char* name, int val);
	void setFloat(const char* name, float val);
	void setMat4(const char* name, glm::mat4& val);
	void setVec3(const char* name, glm::vec3& val);

	std::vector<std::function<void()>> config;
	
private:
	void compileErrorChecking(unsigned int shader, const char* type);
	
};

#endif