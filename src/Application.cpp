#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"
#include "Shader.h"

#include "Camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 720;

//lighting
glm::vec3 lightPos(1.2f, 1.0f, 1.0f);

int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (glewInit() != GLEW_OK)
		std::cout << "Failed To Initialize GLEW!!!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;
	

	glEnable(GL_DEPTH_TEST);

	Shader lightingShader("I:\\C++\\OpenGlWithLighting\\OpenGl\\src\\Shaders\\VS.txt", "I:\\C++\\OpenGlWithLighting\\OpenGl\\src\\Shaders\\FS.txt");
	Shader lightingCubeShader("I:\\C++\\OpenGlWithLighting\\OpenGl\\src\\Shaders\\VLightingCube.txt", "I:\\C++\\OpenGlWithLighting\\OpenGl\\src\\Shaders\\FLightingCube.txt");

	//Shader shader("I:\\C++\\OpenGlWithLighting\\OpenGl\\src\\Shaders\\VS.txt", "I:\\C++\\OpenGlWithLighting\\OpenGl\\src\\Shaders\\FS.txt");
	
	/*float vertices[] = {
		//Position			  //Color		  //Texture
	 0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,		1.0f, 1.0f,			// top right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,		1.0f, 0.0f,			// bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,		0.0f, 0.0f,			// bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,		0.0f, 1.0f			// top left 
	}; */


	//cube verts
	/*float vertices[] =
	{
		//positions		//textureCoords
   -0.5f, -0.5f, -0.5f,		//0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,		//1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,		//1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,		//1.0f, 1.0f,
   -0.5f,  0.5f, -0.5f,		//0.0f, 1.0f,
   -0.5f, -0.5f, -0.5f,		//0.0f, 0.0f,
							//
   -0.5f, -0.5f,  0.5f,		//0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,		//1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,		//1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,		//1.0f, 1.0f,
   -0.5f,  0.5f,  0.5f,		//0.0f, 1.0f,
   -0.5f, -0.5f,  0.5f,		//0.0f, 0.0f,
							//
   -0.5f,  0.5f,  0.5f,		//1.0f, 0.0f,
   -0.5f,  0.5f, -0.5f,		//1.0f, 1.0f,
   -0.5f, -0.5f, -0.5f,		//0.0f, 1.0f,
   -0.5f, -0.5f, -0.5f,		//0.0f, 1.0f,
   -0.5f, -0.5f,  0.5f,		//0.0f, 0.0f,
   -0.5f,  0.5f,  0.5f,		//1.0f, 0.0f,
							//
	0.5f,  0.5f,  0.5f,		//1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,		//1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,		//0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,		//0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,		//0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,		//1.0f, 0.0f,
							//
   -0.5f, -0.5f, -0.5f,		//0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,		//1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,		//1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,		//1.0f, 0.0f,
   -0.5f, -0.5f,  0.5f,		//0.0f, 0.0f,
   -0.5f, -0.5f, -0.5f,		//0.0f, 1.0f,
							//
   -0.5f,  0.5f, -0.5f,		//0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,		//1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,		//1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,		//1.0f, 0.0f,
   -0.5f,  0.5f,  0.5f,		//0.0f, 0.0f,
   -0.5f,  0.5f, -0.5f,		//0.0f, 1.0f
	};*/

	float vertices[] = {
		// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};


	/*unsigned int indeces[] = {
		0, 1, 3,
		1, 2, 3
	};*/



	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW); */
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//Light
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//Texture
	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("I:\\C++\\OpenGlWithLighting\\OpenGl\\src\\Textures\\Jcontainer2.jpg", &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture1" << std::endl;
	}
	stbi_image_free(data);
	
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	data = stbi_load("I:\\C++\\OpenGlWithLighting\\OpenGl\\src\\Textures\\Jcontainer2_specular.jpg", &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture2" << std::endl;
	}
	stbi_image_free(data);



	glBindVertexArray(0);



	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 3.0f));


	lightingShader.SetInt("material.diffuse", 0);
	lightingShader.SetInt("material.specular", 1);


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::vec3 lightColor;
		lightColor.x = 1.0f;
		lightColor.y = 1.0f;
		lightColor.z = 1.0f;
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);


		//NormalObject
		lightingShader.Use();
		lightingShader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("lightPos", lightPos);

		lightingShader.SetFloat("material.shininess", 32.0f);

		// directional light
		lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		lightingShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		lightingShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
		// point light 1
		lightingShader.setVec3("pointLights[0].position", pointLightPositions[0]);
		lightingShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.SetFloat("pointLights[0].constant", 1.0f);
		lightingShader.SetFloat("pointLights[0].linear", 0.09f);
		lightingShader.SetFloat("pointLights[0].quadratic", 0.032f);
		// point light 2
		lightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
		lightingShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setVec3("pointLights[1].diffuse", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.SetFloat("pointLights[1].constant", 1.0f);
		lightingShader.SetFloat("pointLights[1].linear", 0.09f);
		lightingShader.SetFloat("pointLights[1].quadratic", 0.032f);
		// point light 3
		lightingShader.setVec3("pointLights[2].position", pointLightPositions[2]);
		lightingShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setVec3("pointLights[2].diffuse", 1.0f, 0.0f, 0.0f);
		lightingShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.SetFloat("pointLights[2].constant", 1.0f);
		lightingShader.SetFloat("pointLights[2].linear", 0.09f);
		lightingShader.SetFloat("pointLights[2].quadratic", 0.032f);
		// point light 4
		lightingShader.setVec3("pointLights[3].position", pointLightPositions[3]);
		lightingShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.SetFloat("pointLights[3].constant", 1.0f);
		lightingShader.SetFloat("pointLights[3].linear", 0.09f);
		lightingShader.SetFloat("pointLights[3].quadratic", 0.032f);

		lightingShader.setVec3("viewPos", camera.Position);

		//view/Projection transformations
		camera.Inputs(window);
		camera.UpdateMatrix(60.0f, 0.1f, 100.0f);
		camera.Matrix(lightingShader, "camMatrix");

		glm::mat4 model = glm::mat4(1.0f);
		lightingShader.setMat4("model", model);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		glBindVertexArray(VAO);

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = glfwGetTime() * 10.0f * (i + 1);
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			lightingShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}



		
		//glDrawArrays(GL_TRIANGLES, 0, 36);



		lightingCubeShader.Use();


		for (unsigned int i = 0; i < 4; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			lightingCubeShader.setMat4("model", model);
			camera.Matrix(lightingCubeShader, "camMatrix");
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		/*model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		lightingCubeShader.setMat4("model", model);
		camera.Matrix(lightingCubeShader, "camMatrix");

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36); */

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);    //fill or wireframe rendering...




		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}