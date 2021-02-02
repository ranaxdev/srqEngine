#include "ParticleGen.h"

ParticleGen::ParticleGen() {
	ParticleGen::pos = glm::vec3(0.0f);
	ParticleGen::particles.resize(100);

	// Generate random position and lifetime for particles
	for (int i = 0; i < particles.size(); i++) {
		particles[i].pos = glm::vec3(randFloat(-20.0f, 20.0f), 0.0f, randFloat(-20.0f, 20.0f));
		particles[i].life = randFloat(5.0f, 10.0f);
	}

	glGenBuffers(1, &(ParticleGen::vBuffer));
	glGenBuffers(1, &(ParticleGen::pBuffer));
	std::vector<float> vertices;
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);

	vertices.push_back(1.0f);
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);

	vertices.push_back(0.0f);
	vertices.push_back(1.0f);
	vertices.push_back(0.0f);

	vertices.push_back(1.0f);
	vertices.push_back(1.0f);
	vertices.push_back(0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, ParticleGen::vBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, ParticleGen::pBuffer);
	glBufferData(GL_ARRAY_BUFFER, particles.size() * 4 * sizeof(float), positions, GL_DYNAMIC_DRAW);

}

ParticleGen::~ParticleGen() {
	glDeleteBuffers(1, &(ParticleGen::vBuffer));
	glDeleteBuffers(1, &(ParticleGen::pBuffer));
}

void ParticleGen::update(float delta) {
	for (int i = 0; i < particles.size(); i++) {
		particles[i].life -= delta; // Lifetime decreases over time

		// Respawn if dead
		if (particles[i].life <= 0.0f) {
			particles[i].pos = glm::vec3(randFloat(-20.0f, 20.0f), 0.0f, randFloat(-20.0f, 20.0f));
			particles[i].life = randFloat(5.0f, 10.0f);
		}

		// Particles fall
		particles[i].pos -= glm::vec3(0.0f, delta * 2.0f, 0.0f);

		// Update buffers
		positions[i * 4 + 0] = particles[i].pos[0];
		positions[i * 4 + 1] = particles[i].pos[1];
		positions[i * 4 + 2] = particles[i].pos[2];
		positions[i * 4 + 3] = particles[i].life;

	}
}

void ParticleGen::render() {
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(4);

	glBindBuffer(GL_ARRAY_BUFFER, pBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, particles.size() * 4 * sizeof(float), positions);

	glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, pBuffer);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	glVertexAttribDivisor(4, 1);

	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, particles.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(4);

}

glm::vec3& ParticleGen::getPosition() {
	return ParticleGen::pos;
}

float ParticleGen::randFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float difference = b - a;
	float rNum = random * difference;
	return rNum;
}