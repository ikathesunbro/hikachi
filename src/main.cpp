#include "main.h"

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
	glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);

	GLFWwindow* window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "TEST VERSION", NULL, NULL);
	
	if (!window)
	{
		std::cout << "Failed to create window :(" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD :(" << std::endl;
		glfwTerminate();
		return -1;		
	}


	Shader shader("shader/default.vert", "shader/default.frag");

	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	int texWidth, texHeight, nrChannels;
	unsigned char* texData = stbi_load("textures/container.jpg", &texWidth, &texHeight, &nrChannels, 0);

	if (texData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture :(" << std::endl;
	}
	stbi_image_free(texData);
	
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	stbi_set_flip_vertically_on_load(true);
	texData = stbi_load("textures/awesomeface.png", &texWidth, &texHeight, &nrChannels, 0);
	stbi_set_flip_vertically_on_load(false);

	if (texData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture :(" << std::endl;
	}
	
	stbi_image_free(texData);

	shader.use();
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);
	
	glUseProgram(0);

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glEnable(GL_DEPTH_TEST);

	setRandomPositions(positions, 100, 30);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		float radius = 30.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		
		shader.use();
		shader.setFloat("mixValue", mixValue);
		shader.setFloat("time", glfwGetTime());
	
		glBindVertexArray(VAO);
		
		for (unsigned int i = 0; i < positions.size(); i++)
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), positions[i]);
			model = glm::rotate(model, glm::radians((float)((glfwGetTime() + i) * 100)), glm::vec3(0.4f, 0.3f, 1.0f));
			model = glm::scale(model, glm::vec3((float)(sin(glfwGetTime() * 0.5) * 0.2 + 1.4)));

			glm::mat4 view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(sin(glfwGetTime()) * 5), glm::vec3(0.0f, 1.0f, 0.0f));

			glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1190.0f, 0.05f, 500.0f);

			shader.setMat4f("model", model);
			shader.setMat4f("view", view);
			shader.setMat4f("projection", projection);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixValue -= 0.001f;
		if (mixValue <= 0.0f) mixValue = 0.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixValue += 0.001f;
		if (mixValue >= 1.0f) mixValue = 1.0f;
	}
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void setRandomPositions(std::vector<glm::vec3> &positions, unsigned int count, float area)
{
	srand(static_cast <unsigned> (time(0)));

	auto random = [](float scale)
		{
			return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f) * scale;
		};

	for (unsigned int i = 0; i < count; i++)
	{
		positions.push_back(glm::vec3(random(area), random(area), random(area)));
	}
}