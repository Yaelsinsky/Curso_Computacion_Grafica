// Práctica 2. Dibujo de primitivas en 2D
// Camarena Arevalo Yael Eduardo 
// Fecha de entrega: 15 de febrero de 2026
// 318279864

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de Primitivas en 2D - Yael Camarena", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
    // --- MACETA (Tonos cafés) ---
    -0.25f, -0.9f, 0.0f,   0.35f, 0.22f, 0.15f, // 0: Base Izq
     0.25f, -0.9f, 0.0f,   0.35f, 0.22f, 0.15f, // 1: Base Der
     0.35f, -0.4f, 0.0f,   0.45f, 0.30f, 0.20f, // 2: Tope Der
    -0.35f, -0.4f, 0.0f,   0.45f, 0.30f, 0.20f, // 3: Tope Izq
     0.0f,  -0.65f, 0.0f,  0.25f, 0.15f, 0.10f, // 4: Centro

    // --- CUERPO CACTUS (Tonos verdes) ---
    -0.15f, -0.4f, 0.0f,   0.29f, 0.44f, 0.23f, // 5: Base Tronco Izq
     0.15f, -0.4f, 0.0f,   0.29f, 0.44f, 0.23f, // 6: Base Tronco Der
     0.15f,  0.5f, 0.0f,   0.46f, 0.60f, 0.38f, // 7: Punta Tronco Der
    -0.15f,  0.5f, 0.0f,   0.18f, 0.27f, 0.14f, // 8: Punta Tronco Izq
     0.0f,   0.7f, 0.0f,   0.46f, 0.60f, 0.38f, // 9: Cúspide
     0.0f,   0.1f, 0.0f,   0.25f, 0.40f, 0.20f, // 10: Centro Tronco

    // --- BRAZO IZQUIERDO ---
    -0.15f,  0.0f, 0.0f,   0.29f, 0.44f, 0.23f, // 11: Unión
    -0.45f, -0.1f, 0.0f,   0.18f, 0.27f, 0.14f, // 12: Codo exterior
    -0.45f,  0.3f, 0.0f,   0.46f, 0.60f, 0.38f, // 13: Punta superior
    -0.30f,  0.3f, 0.0f,   0.29f, 0.44f, 0.23f, // 14: Punta interior

    // --- BRAZO DERECHO ---
     0.15f,  0.2f, 0.0f,   0.29f, 0.44f, 0.23f, // 15: Unión
     0.45f,  0.1f, 0.0f,   0.18f, 0.27f, 0.14f, // 16: Codo exterior
     0.45f,  0.5f, 0.0f,   0.46f, 0.60f, 0.38f, // 17: Punta superior
     0.30f,  0.5f, 0.0f,   0.29f, 0.44f, 0.23f, // 18: Punta interior

	};
	unsigned int indices[] = {  // note that we start from 0!
		// Maceta
		0, 1, 4,   1, 2, 4,   2, 3, 4,   3, 0, 4,
		// Tronco
		5, 6, 10,  6, 7, 10,  7, 9, 10,  9, 8, 10,  8, 5, 10,
		// Brazo Izquierdo
		11, 12, 14, 12, 13, 14,
		// Brazo Derecho
		15, 16, 18, 16, 17, 18
	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);


       glPointSize(20);
        //glDrawArrays(GL_POINTS,0,4);
        
        //glDrawArrays(GL_LINES,0,2);
        //glDrawArrays(GL_LINE_LOOP,0,4);
        
        //glDrawArrays(GL_TRIANGLES,1,4);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        

        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}