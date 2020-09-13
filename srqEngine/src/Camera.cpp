#include "Camera.h"
#include "Util/Globals.h"
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
Camera::Camera() {
	/* Define defaults (start of scene) */
	Camera::viewprojectionMatrix = glm::mat4(1.0f); // identity
	Camera::viewMatrix = glm::mat4(1.0f);
	Camera::projectionMatrix = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
	
	Camera::camPos = glm::vec3(0.0f,0.0f,3.0f);
	Camera::camFront = glm::vec3(0.0f, 0.0f, -1.0f);
	Camera::camUp = glm::vec3(0.0f, 1.0f, 0.0f);

	Camera::yaw = -90.0f;
	Camera::pitch = 0.0f;
}

Camera::~Camera() {}

/* Update position */
void Camera::update() {
	
}

/* Recalculate view projection matrix */
void Camera::recalcVP() {
	Camera::viewMatrix = glm::lookAt(Camera::camPos, Camera::camPos + Camera::camFront, Camera::camUp);
	Camera::viewprojectionMatrix = Camera::projectionMatrix * Camera::viewMatrix;
}


/* Return view projection matrix */
glm::mat4& Camera::getVP() {
	Camera::recalcVP(); // recalculate VP
	return Camera::viewprojectionMatrix;
}


/* Return camera vars */
glm::vec3& Camera::getCamFront() { return Camera::camFront; }
glm::vec3& Camera::getCamPos() { return Camera::camPos; }
glm::vec3& Camera::getCamUp() { return Camera::camUp; }

/* Set camera position and front */
void Camera::setCamFront(glm::vec3 cf) { Camera::camFront = cf; }
void Camera::setCamPos(glm::vec3 cp) { Camera::camPos = cp; }