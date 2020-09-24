#ifndef _H_MODEL
#define _H_MODEL

#include "Texture.h"
#include "VertexArray.h"
#include "Buffer.h"
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

// ********** IMPORTED MODEL CLASS ************
class Model {
public:
	Model(const char* filepath, const char* tex_filepath); // Textured Model
	Model(const char* filepath, glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f)); // Plain model (default red)
	~Model();
	
	// core data
	std::vector<float> data;
	
	int getTotalVectors() const;
	std::vector<glm::vec3>& getVertices();
	std::vector<glm::vec2>& getTextureCoords();
	std::vector<glm::vec3>& getNormalCoords();

	VertexArray& getVA();
	
	glm::vec3 getColor();
	void setColor(float a, float b, float c);

	void update();
	void bind();

private:
	int totalVertices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> textureCoords;
	std::vector<glm::vec3> normalCoords;

	glm::vec3 modelColor;

	VertexArray va;
	Texture tex;

	void constructData(const char* filepath);

	
	
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