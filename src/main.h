#pragma once

#include <iostream>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

// Global Settings
const unsigned int SRC_WIDTH{ 800 };
const unsigned int SRC_HEIGHT{ 600 };

// Data
float vertices[] = {
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   
};



// Functions
void processInput(GLFWwindow* window);

void framebufferSizeCallback(GLFWwindow* window, int width, int height);