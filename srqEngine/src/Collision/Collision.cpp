#include "Collision.h"
#include<iostream>
#include<glm/gtx/string_cast.hpp>
std::vector<std::shared_ptr<Model>> Collision::collidables;

Collision::Collision() {}

float Collision::calcsign(float x) {
	return (x > 0) - (x < 0);
}

void Collision::updateCollisions(Camera& cam) {
	for (auto& m : collidables) {
		if ((cam.getCamPos().x >= m->getPosition().x - (m->getSize().x + 0.5) && cam.getCamPos().x <= m->getPosition().x + (m->getSize().x + 0.5)) &&
			(cam.getCamPos().y >= m->getPosition().y - (m->getSize().y + 0.5) && cam.getCamPos().y <= m->getPosition().y + (m->getSize().y + 0.5)) &&
			(cam.getCamPos().z >= m->getPosition().z - (m->getSize().z + 0.5) && cam.getCamPos().z <= m->getPosition().z + (m->getSize().z + 0.5))) {
			float dx = -abs(cam.getCamPos()).x + (m->getPosition().x + (m->getSize().x + 0.5));
			float dy = -abs(cam.getCamPos()).y + (m->getPosition().y + (m->getSize().y + 0.5));
			float dz = -abs(cam.getCamPos()).z + (m->getPosition().z + (m->getSize().z + 0.5));
			float min = std::min({ dx,dy,dz });

			std::cout << "X: " << dx << " / Y: " << dy << " / Z: " << dz << std::endl;
			
			if (min == dx) {
				float sign = calcsign(cam.getCamFront().x);
				cam.setCamPos(glm::vec3(cam.getCamPos().x - (sign * 0.01), cam.getCamPos().y, cam.getCamPos().z));
			}

			if (min == dy) {
				float sign = calcsign(cam.getCamFront().y);
				cam.setCamPos(glm::vec3(cam.getCamPos().x, cam.getCamPos().y - (sign * 0.01), cam.getCamPos().z));
			}

			if (min == dz) {
				float sign = calcsign(cam.getCamFront().z);
				cam.setCamPos(glm::vec3(cam.getCamPos().x, cam.getCamPos().y, cam.getCamPos().z - (sign * 0.01)));
			}


		}
	}
}