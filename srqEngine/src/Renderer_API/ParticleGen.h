#ifndef _H_PARTICLE
#define _H_PARTICLE

#include<glad/glad.h>
#include<vector>
#include <glm/glm.hpp>

struct Particle {
	glm::vec3 pos;
	float life;
};

class ParticleGen
{
public:
	ParticleGen();
	~ParticleGen();

	void update(float deleta);
	void render();
	glm::vec3& getPosition();

private:
	std::vector<Particle> particles;
	float positions[400];
	unsigned int vBuffer;
	unsigned int pBuffer;
	glm::vec3 pos;
	
	float randFloat(float a, float b);
};

#endif

