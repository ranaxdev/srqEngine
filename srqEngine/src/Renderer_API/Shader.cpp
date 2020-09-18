#include<glad/glad.h>
#include "Shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
/* Load and process vertex/fragment shader from file path */
Shader::Shader(const char* vshaderPath, const char* fshaderPath) {
	std::string vshaderCode;
	std::string fshaderCode;
	std::ifstream vshaderFile;
	std::ifstream fshaderFile;
	/* Exception handling */
	vshaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	fshaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);

	/* Try to open files, read from them and store the code */
	try {
		vshaderFile.open(vshaderPath);
		fshaderFile.open(fshaderPath);
		std::stringstream vshaderstream, fshaderstream;
		vshaderstream << vshaderFile.rdbuf();
		fshaderstream << fshaderFile.rdbuf();
		vshaderCode = vshaderstream.str();
		fshaderCode = fshaderstream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "[ERROR] SHADER FILE NOT SUCCESSFULLY READ" << std::endl;
	}

	const char* vertexCode = vshaderCode.c_str();
	const char* fragmentCode = fshaderCode.c_str();

	/* Create the shaders, compile, attach/link program then delete them */
	unsigned int vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexCode, NULL);
	glCompileShader(vertex);
	compileErrorChecking(vertex, "VERTEX_SHADER");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentCode, NULL);
	glCompileShader(fragment);
	compileErrorChecking(fragment, "FRAGMENT_SHADER");

	Shader::ID = glCreateProgram();
	glAttachShader(Shader::ID, vertex);
	glAttachShader(Shader::ID, fragment);
	glLinkProgram(Shader::ID);
	compileErrorChecking(Shader::ID, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);


}

/* Use the program */
void Shader::bind() const {
	glUseProgram(Shader::ID);
}
void Shader::unbind() const {
	glUseProgram(0);
}

/* Set uniforms quickly utility */
void Shader::setInt(const char* name, int val) {
	glUniform1i(glGetUniformLocation(Shader::ID, name), val);
}
void Shader::setFloat(const char* name, float val) {
	glUniform1f(glGetUniformLocation(Shader::ID, name), val);
}
void Shader::setMat4(const char* name, glm::mat4& val) {
	glUniformMatrix4fv(glGetUniformLocation(Shader::ID, name), 1, GL_FALSE , &val[0][0]);
}
void Shader::setVec3(const char* name, glm::vec3 val) {
	glUniform3fv(glGetUniformLocation(Shader::ID, name), 1, &val[0]);
}


/* Compilation/Linking error checking */
void Shader::compileErrorChecking(unsigned int shader, const char* type) {
	int success;
	char infolog[1024];
	/* Check for shader compilation errors */
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infolog);
			std::cout << "[ERROR] SHADER COMPILATION ERROR TYPE: " << type << std::endl;
			std::cout << infolog << std::endl;
			std::cout << "----------------------------------------------------" << std::endl;
		}
	}
	/* Checking for program linking error */
	else {
		glGetProgramiv(Shader::ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(Shader::ID, 1024, NULL, infolog);
			std::cout << "[ERROR] PROGRAM LINKING ERROR: " << std::endl;
			std::cout << infolog << std::endl;
			std::cout << "----------------------------------------------------" << std::endl;
		}
	}
}


/* ---------------------Configurations--------------------- */
// return config DS
std::vector<std::function<void()>>& Shader::getConfig() {
	return Shader::config;
}
// Add configuration to config DS (lambda-express)
//	[VECTOR 3]
void Shader::AddVec3Config(const char* name, float a, float b, float c) {
	glm::vec3 vec3 = glm::vec3(a, b, c);
	auto func = [this, name, vec3]() {Shader::setVec3(name, vec3); };
	Shader::config.push_back(func);
}


/*--------------------------------------------------------*/
