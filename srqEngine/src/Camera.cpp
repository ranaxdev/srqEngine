#include<glm/gtx/string_cast.hpp>
#include<iostream>
#include "Camera.h"
#include "Util/Globals.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
Camera::Camera() {
	/* Define defaults (start of scene) */
	Camera::viewprojectionMatrix = glm::mat4(1.0f); // identity
	Camera::viewMatrix = glm::mat4(1.0f);
	Camera::projectionMatrix = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
	
	Camera::camPos = glm::vec3(0.0f,1.0f,5.0f);
	Camera::camFront = glm::vec3(0.0f, 0.0f, -1.0f);
	Camera::camUp = glm::vec3(0.0f, 1.0f, 0.0f);

	Camera::yaw = -90.0f;
	Camera::pitch = 0.0f;
	Camera::lastX = (float)SCREEN_WIDTH / 2.0f;
	Camera::lastY = (float)SCREEN_HEIGHT / 2.0f;
	Camera::initmouse = true;
}

Camera::~Camera() {}


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

/* Get view and projection seperately */
glm::mat4& Camera::getView() {return Camera::viewMatrix; }
glm::mat4& Camera::getProjection() { return Camera::projectionMatrix; }

/* Return camera vars */
glm::vec3& Camera::getCamFront() { return Camera::camFront; }
glm::vec3& Camera::getCamPos() { return Camera::camPos; }
glm::vec3& Camera::getCamUp() { return Camera::camUp; }

/* Set camera position and front */
void Camera::setCamFront(glm::vec3 cf) { Camera::camFront = cf; }
void Camera::setCamPos(glm::vec3 cp) { Camera::camPos = cp; }



/* Update input */
void Camera::update(GLFWwindow* window, float delta) {
	/* UPDATE MOVEMENT*/
	// ===================================================================================================
	float camSpeed = 8.0f * delta;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { // move forward
		Camera::camPos += camSpeed * Camera::camFront;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { // move back
		Camera::camPos -= camSpeed * Camera::camFront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { // move left
		Camera::camPos -= glm::normalize(glm::cross(Camera::camFront, Camera::camUp)) * camSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { // move right
		Camera::camPos += glm::normalize(glm::cross(Camera::camFront, Camera::camUp)) * camSpeed;
	}
	// temp exit
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwTerminate();
	}

	/* TEMP COLLISION DETECTION FOR DEBUGGING */
	// ===================================================================================================
	
	


	/* UPDATE ROTATION */
	// ===================================================================================================

	double xpos;
	double ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	if (initmouse) {
		lastX = xpos;
		lastY = ypos;
		initmouse = false;
	}
	float xoff = xpos - lastX;
	float yoff = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sense = 0.1f;
	xoff *= sense;
	yoff *= sense;

	yaw += xoff;
	pitch += yoff;

	if (pitch > 89.0f) { pitch = 89.0f; }
	if (pitch < -89.0f) { pitch = -89.0f; }

	
	Camera::camFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	Camera::camFront.y = sin(glm::radians(pitch));
	Camera::camFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

}