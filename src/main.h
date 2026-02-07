#pragma once

#include <iostream>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "STB/stb_image.h"

#include "shader.h"

// Global Settings
const unsigned int SRC_WIDTH{ 800 };
const unsigned int SRC_HEIGHT{ 600 };

float mixValue{ 0.0f };

// Data
float vertices[] = {
    // Position          // Colors           // Texture
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f   
};

unsigned int indices[] = {
        0, 1, 3, 
        1, 2, 3  
};

// Functions
void processInput(GLFWwindow* window);

void framebufferSizeCallback(GLFWwindow* window, int width, int height);