#include "Model.h"
#include "../Util/Globals.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// ******** IMPORTED MODEL **************					// texture initialized
Model::Model(const char* filepath, const char* tex_filepath) : tex(tex_filepath) {
	ImportModel import = ImportModel();
	import.parseObject(filepath);
	
	Model::totalVertices = import.getTotalVertices();

	std::vector<float> iv = import.getVertices();
	std::vector<float> it = import.getTexCoords();
	std::vector<float> in = import.getNormals();

	for (std::size_t i = 0; i < Model::totalVertices; i++) {
		Model::vertices.push_back(glm::vec3(iv[i * 3], iv[i * 3 + 1], iv[i * 3 + 2]));
		Model::textureCoords.push_back(glm::vec2(it[i * 2], it[i * 2 + 1]));
		Model::normalCoords.push_back(glm::vec3(in[i * 3], in[i * 3 + 1], in[i * 3 + 2]));
	}

	// generate useable attrib vectors
	for (int i = 0; i < Model::totalVertices; i++) {
		Model::v_values.push_back((Model::vertices[i]).x);
		Model::v_values.push_back((Model::vertices[i]).y);
		Model::v_values.push_back((Model::vertices[i]).z);
		Model::t_values.push_back((Model::textureCoords[i]).s);
		Model::t_values.push_back((Model::textureCoords[i]).t);
		Model::n_values.push_back((Model::normalCoords[i]).x);
		Model::n_values.push_back((Model::normalCoords[i]).y);
		Model::n_values.push_back((Model::normalCoords[i]).z);
	}

	// bind texture
	Model::tex.bind();
}
Model::~Model(){}

void Model::update() {
	Model::tex.bind();
}

int Model::getTotalVectors() const { return Model::totalVertices; }
std::vector<glm::vec3>& Model::getVertices() { return Model::vertices; }
std::vector<glm::vec2>& Model::getTextureCoords() { return Model::textureCoords; }
std::vector<glm::vec3>& Model::getNormalCoords() { return Model::normalCoords; }



// =========================================================================
// =========================================================================

// ******** MODEL IMPORTER **************

ImportModel::ImportModel() {}
ImportModel::~ImportModel(){}

/* Open object file and parse vertices, texture coordinates and normals */
void ImportModel::parseObject(const char* filepath){
	float x, y, z;
	std::ifstream filestream(filepath, std::ios::in);
	std::string line = "";

	while (!filestream.eof()) {
		std::getline(filestream, line);
		
		// Vertex value found (v identifier)
		if (line.compare(0, 2, "v ") == 0) {
			std::stringstream ss(line.erase(0, 1));
			ss >> x;
			ss >> y;
			ss >> z;
			ImportModel::vertexVals.push_back(x);
			ImportModel::vertexVals.push_back(y);
			ImportModel::vertexVals.push_back(z);

		}
		// Texture coordinate found (vt identifier)
		if (line.compare(0, 2, "vt") == 0) {
			std::stringstream ss(line.erase(0, 2));
			ss >> x;
			ss >> y;
			ImportModel::texVals.push_back(x);
			ImportModel::texVals.push_back(y);
		}
		// Normal found (vn identifier)
		if (line.compare(0, 2, "vn") == 0) {
			std::stringstream ss(line.erase(0, 2));
			ss >> x;
			ss >> y;
			ss >> z;
			ImportModel::normalVals.push_back(x);
			ImportModel::normalVals.push_back(y);
			ImportModel::normalVals.push_back(z);
		}
		// FACES
		if (line.compare(0, 2, "f ") == 0) {
			std::string corner, v, t, n;
			std::stringstream ss(line.erase(0, 2));
			for (int i = 0; i < 3; i++) {
				std::getline(ss, corner, ' ');
				std::stringstream corner_ss(corner);
				std::getline(corner_ss, v, '/');
				std::getline(corner_ss, t, '/');
				std::getline(corner_ss, n, '/');

				std::size_t vcount = ((std::size_t)(std::stoi(v)) - 1) * 3;
				std::size_t tcount = ((std::size_t)(std::stoi(t)) - 1) * 2;
				std::size_t ncount = (std::size_t(std::stoi(n)) - 1) * 3;

				ImportModel::vertices.push_back(ImportModel::vertexVals[vcount + 0]);
				ImportModel::vertices.push_back(ImportModel::vertexVals[vcount + 1]);
				ImportModel::vertices.push_back(ImportModel::vertexVals[vcount + 2]);

				ImportModel::textures.push_back(ImportModel::texVals[tcount + 0]);
				ImportModel::textures.push_back(ImportModel::texVals[tcount + 1]);

				ImportModel::normals.push_back(ImportModel::normalVals[ncount + 0]);
				ImportModel::normals.push_back(ImportModel::normalVals[ncount + 1]);
				ImportModel::normals.push_back(ImportModel::normalVals[ncount + 2]);
			}
		}
	}
}

// GETTERS
int ImportModel::getTotalVertices() const { return ImportModel::vertices.size() / 3; }
std::vector<float>& ImportModel::getVertices() { return ImportModel::vertices; }
std::vector<float>& ImportModel::getTexCoords() { return ImportModel::textures; }
std::vector<float>& ImportModel::getNormals() { return ImportModel::normals; }