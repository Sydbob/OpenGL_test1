#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "Shader.h"
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include "Texture.h" 
#include "Quad.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

float mixAmount = 0.2f;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{ 
	
	//glfw settings (profile - core), version (3.4 = major 3, minor 4)
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //required fr Mac OS X

	//function that draws a window
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	//framebuffer takes new window dimension and adjusts the viewport when user resizes it
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//function to make sure GLAD is initialised
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialise GLAD" << std::endl;
		return -1;
	}

	//enabling depth testing
	//glEnable(GL_DEPTH_TEST);
	//shaders
	Shader ourShader("shader.vs", "shader.fs"), ourShader2("shader.vs", "shader.fs");
	
	//the quad
	Quad BG, quad, quad2;
	BG.GenerateQuad();
	quad.GenerateQuad();
	quad2.GenerateQuad();
	
	
	

	//------------texture stuff--------

	//---Background texture-----
	Texture texture("container.jpg", 0);
	texture.GenerateTexture();
	Texture texture2("awesomefaceC.jpg", 1);
	texture2.GenerateTexture();
	
	//setting texture smaplers -------------
	//tell sampler which texture belongs to which sampler
	ourShader.use(); // activate shader first
	ourShader.setInt("texture1", 0);
	//glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 1);
	ourShader2.use();
	ourShader2.setInt("texture1", 1);
	//end of texture samplers-----------------
	

	//render loop
	//check if window was instructed to close
	while (!glfwWindowShouldClose(window))
	{
		//process the input
		processInput(window);

		//rendering commands
		//----------------
		//clearing the colour buffer at the start
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//texture binding
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.GetTextureID());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2.GetTextureID());

		//container rendering
		ourShader.use();
		BG.DrawQuad(ourShader, 1.0f);
		ourShader2.use();
		quad.DrawQuad(ourShader2, 0.5f);
		ourShader.use();
		quad2.DrawQuad(ourShader, 0.1f);

		/*
		//setting transformations
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0));
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		
		//getting matrices locations
		unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
		unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
		unsigned int projLoc = glGetUniformLocation(ourShader.ID, "projection");
		//passing matrices to shaders
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniform1f(glGetUniformLocation(ourShader.ID, "mixAmount"), mixAmount);*/

		/*for (unsigned int i = 1; i < 11; i++)
		{
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i-1]);
			float angle = 20.0f * i;
			if (i % 3 == 0)
				angle = glfwGetTime() * 25.0f;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}*/
		
		//----------------
		//end of rendering commands

		
		//swap colour buffer that was used to draw previous window
		glfwSwapBuffers(window);
		//check if events are triggeres (e.g. keyboard input), updates window state, class functions
		glfwPollEvents();
	}

	//clean/delete all resources
	glfwTerminate();

	return 0; 
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		mixAmount += 0.001f;
		if (mixAmount >= 1.0f)
			mixAmount = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		mixAmount -= 0.001f;
		if (mixAmount <= 0.0f)
			mixAmount = 0.0f;
	}
}

