// Práctica 5. Modelado jerárquico
// Camarena Arevalo Yael Eduardo 
// Fecha de entrega: 8 de marzo de 2026
// 318279864

#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);


const GLint WIDTH = 1200, HEIGHT = 800;

//For Keyboard
float	movX = 0.0f,
movY = 3.0f,
movZ = -10.0f,
rot = 0.0f;

//For model
float	hombro = 0.0f,
codo = 0.0f,
muneca = 0.0f,
falange1 = 20.0f,
falange2 = -20.0f,
falange3 = -10.0f;

int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Modelado jerarquico - Yael Camarena", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers
	// use with Orthographic Projection




	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f,  0.5f, 0.5f,
		0.5f,  0.5f, 0.5f,
		-0.5f,  0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,

		-0.5f, -0.5f,-0.5f,
		 0.5f, -0.5f,-0.5f,
		 0.5f,  0.5f,-0.5f,
		 0.5f,  0.5f,-0.5f,
		-0.5f,  0.5f,-0.5f,
		-0.5f, -0.5f,-0.5f,

		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  -0.5f, 0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);



	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	glm::mat4 projection = glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{

		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);
		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
		glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp



		//View set up 
		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
		GLint uniformColor = ourShader.uniformColor;

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));


		glBindVertexArray(VAO);

		//Model Bicep
		model = glm::rotate(model, glm::radians(hombro), glm::vec3(0.0f, 1.0, 0.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.6f, 2.0f, 0.6f));
		color = glm::vec3(0.5f, 0.5f, 0.5f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Model antebrazo
		model = glm::translate(modelTemp, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(codo), glm::vec3(1.0f, 0.0f, 0.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.0f, -0.75f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 1.5f, 0.4f));
		color = glm::vec3(0.7f, 0.7f, 0.7f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Model Palma 
		model = glm::translate(modelTemp, glm::vec3(0.0f, -0.75f, 0.0f));
		model = glm::rotate(model, glm::radians(muneca), glm::vec3(0.0f, 1.0f, 0.0f));
		modelTemp2 = model = glm::translate(model, glm::vec3(0.0f, -0.2f, 0.0f));
		model = glm::scale(model, glm::vec3(1.2f, 0.4f, 1.2f));
		color = glm::vec3(0.1f, 0.1f, 0.6f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		float radioPalma = 0.55f;

		for (int i = 0; i < 5; i++) {
			float anguloDedo = i * 72.0f;

			// Falange 1
			model = glm::rotate(modelTemp2, glm::radians(anguloDedo), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::translate(model, glm::vec3(radioPalma, -0.2f, 0.0f));
			model = glm::rotate(model, glm::radians(falange1), glm::vec3(0.0f, 0.0f, 1.0f));
			modelTemp = model = glm::translate(model, glm::vec3(0.0f, -0.4f, 0.0f));
			model = glm::scale(model, glm::vec3(0.15f, 0.8f, 0.15f));
			color = glm::vec3(0.0f, 1.0f, 1.0f);
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);

			// Falange 2
			model = glm::translate(modelTemp, glm::vec3(0.0f, -0.4f, 0.0f));
			model = glm::rotate(model, glm::radians(falange2), glm::vec3(0.0f, 0.0f, 1.0f));
			modelTemp = model = glm::translate(model, glm::vec3(0.0f, -0.3f, 0.0f));
			model = glm::scale(model, glm::vec3(0.12f, 0.6f, 0.12f));
			color = glm::vec3(1.0f, 0.0f, 1.0f);
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);

			// Falange 3
			model = glm::translate(modelTemp, glm::vec3(0.0f, -0.3f, 0.0f));
			model = glm::rotate(model, glm::radians(falange3), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::translate(model, glm::vec3(0.0f, -0.2f, 0.0f));
			model = glm::scale(model, glm::vec3(0.1f, 0.4f, 0.1f));
			color = glm::vec3(1.0f, 1.0f, 0.0f);
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		glBindVertexArray(0);


		// Swap the screen buffers
		glfwSwapBuffers(window);

	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
}

void Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		movY += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		movY -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rot += 0.18f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rot -= 0.18f;

	// CONTROLES GARRAS
	// Falange 1: J (cierra) / U (abre)
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		if (falange1 < 20.0f) falange1 += 0.4f;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		if (falange1 > 10.0f) falange1 -= 0.4f;

	// Falange 2: K (abre) / I (cierra)
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		if (falange2 < 45.0f) falange2 += 0.4f;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		if (falange2 > -45.0f) falange2 -= 0.4f;

	// Falange 3: L (abre) / O (cierra)
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		if (falange3 < 60.0f) falange3 += 0.4f;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		if (falange3 > -10.0f) falange3 -= 0.4f;
}