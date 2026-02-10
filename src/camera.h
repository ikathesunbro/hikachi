#pragma once

#include <iostream>

#include <GLAD/glad.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "shader.h"

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 lookAt);

	glm::vec3 camPos;
	glm::vec3 camDirection;
		
private:
	void setMVP(Shader shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection);

	glm::vec3 camUp;
	glm::vec3 camRight;
	glm::vec3 camFront;
};
