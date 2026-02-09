#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include <GLAD/glad.h>

class Shader
{
public:
	unsigned int ID;
	
	Shader(const char* vertexPath, const char* fragmentPath);

	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4f(const std::string& name, glm::mat4 value) const;

private:
	void checkCompileErrors(unsigned int shader, std::string type);
};