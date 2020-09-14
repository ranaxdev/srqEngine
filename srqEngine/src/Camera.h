#ifndef _H_CAMERA
#define _H_CAMERA

#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera {
public:
	Camera();
	~Camera();

	void update(GLFWwindow* window, float delta);
	glm::mat4& getVP();

	glm::vec3& getCamFront();
	glm::vec3& getCamPos();
	glm::vec3& getCamUp();

	void setCamFront(glm::vec3 cf);
	void setCamPos(glm::vec3 cp);
	
private:
	glm::mat4 viewprojectionMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

	glm::vec3 camPos;
	glm::vec3 camFront;
	glm::vec3 camUp;

	float yaw;
	float pitch;
	float lastX;
	float lastY;
	
	bool initmouse;

	void recalcVP();
};

#endif