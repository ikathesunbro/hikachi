#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 lookAt)
{
	camPos = position;
	camDirection = lookAt;

	glm::vec3 difference = glm::normalize(camDirection - camPos);
	
	camRight = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), difference);
	camUp = glm::cross(camRight, difference);
	camFront = glm::cross(camRight, camUp);
}

void Camera::setMVP(Shader shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
	shader.setMat4f("model", model);
	shader.setMat4f("view", view);
	shader.setMat4f("projection", projection);
}
