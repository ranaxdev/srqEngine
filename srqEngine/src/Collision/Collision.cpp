#include "Collision.h"
#include<iostream>
#include<glm/gtx/string_cast.hpp>
std::vector<std::shared_ptr<Model>> Collision::collidables;

Collision::Collision() {}

float Collision::calcsign(float x) {
	return (x > 0) - (x < 0);
}

void Collision::updateCollisions(Camera& cam) {
	std::cout << glm::to_string(cam.getCamPos()) << std::endl;
	for (auto& m : collidables) {
		if ((cam.getCamPos().x >= m->getPosition().x - (m->getSize().x + 0.5) && cam.getCamPos().x <= m->getPosition().x + (m->getSize().x + 0.5)) &&
			(cam.getCamPos().y >= m->getPosition().y - (m->getSize().y + 0.5) && cam.getCamPos().y <= m->getPosition().y + (m->getSize().y + 0.5)) &&
			(cam.getCamPos().z >= m->getPosition().z - (m->getSize().z + 0.5) && cam.getCamPos().z <= m->getPosition().z + (m->getSize().z + 0.5))) {
			float dx = glm::distance(cam.getCamPos().x, m->getPosition().x);
			float dy = glm::distance(cam.getCamPos().y, m->getPosition().y);
			float dz = glm::distance(cam.getCamPos().z, m->getPosition().z);
			float max = std::max({ dx,dy,dz });
			//std::cout << "X: " << dx << " / Y: " << dy << " / Z: " << dz << std::endl;
			
			if (max == dx) {
				
				float sign = calcsign(cam.getCamFront().x);
				cam.setCamPos(glm::vec3(cam.getCamPos().x - (sign * 0.01), cam.getCamPos().y, cam.getCamPos().z));
			}

			if (max == dy) {
				
				float sign = calcsign(cam.getCamFront().y);
				cam.setCamPos(glm::vec3(cam.getCamPos().x, cam.getCamPos().y + (0.01), cam.getCamPos().z)); // no sign here normal always points up, cant collide with bottom of obj
			}

			if (max == dz) {
				
				float sign = calcsign(cam.getCamFront().z);
				cam.setCamPos(glm::vec3(cam.getCamPos().x, cam.getCamPos().y, cam.getCamPos().z - (sign * 0.01)));
			}
			

		}
	}
}