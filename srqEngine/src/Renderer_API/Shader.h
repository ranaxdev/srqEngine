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
	void setVec3(const char* name, glm::vec3 val);

	/* CONFIGS */
	void AddVec3Config(const char* name, float a, float b, float c);

	/* GETTERS */
	std::vector<std::function<void()>>& getConfig();

	
private:
	void compileErrorChecking(unsigned int shader, const char* type);
	std::vector<std::function<void()>> config;
};

#endif