#ifndef _H_MODEL
#define _H_MODEL
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

// ********** IMPORTED MODEL CLASS ************
class Model {
public:
	Model(const char* filepath);
	~Model();

	int getTotalVectors() const;
	std::vector<glm::vec3>& getVertices();
	std::vector<glm::vec2>& getTextureCoords();
	std::vector<glm::vec3>& getNormalCoords();


private:
	int totalVertices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> textureCoords;
	std::vector<glm::vec3> normalCoords;
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