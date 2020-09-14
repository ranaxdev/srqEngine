#ifndef _H_MODEL
#define _H_MODEL

#include "Texture.h"

#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

// ********** IMPORTED MODEL CLASS ************
class Model {
public:
	Model(const char* filepath, const char* tex_filepath);
	~Model();
	
	// core data
	std::vector<float> data;
	
	int getTotalVectors() const;
	std::vector<glm::vec3>& getVertices();
	std::vector<glm::vec2>& getTextureCoords();
	std::vector<glm::vec3>& getNormalCoords();
	void update();

private:
	int totalVertices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> textureCoords;
	std::vector<glm::vec3> normalCoords;

	Texture tex;

	
	
};



// ===============================================================
// ===============================================================


// ********** MODEL IMPORTER CLASS ************
class ImportModel {
public:
	ImportModel();
	~ImportModel();

	void parseObject(const char* filepath);
	int getTotalVertices() const;

	std::vector<float>& getVertices();
	std::vector<float>& getTexCoords();
	std::vector<float>& getNormals();

private:
	// These are the returnable ones
	std::vector<float> vertices;
	std::vector<float> textures;
	std::vector<float> normals;

	// For parsing obj file
	std::vector<float> vertexVals;
	std::vector<float> texVals;
	std::vector<float> normalVals;

};

#endif