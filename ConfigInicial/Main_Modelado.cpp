// Práctica 4. Modelado geométrico
// Camarena Arevalo Yael Eduardo 
// Fecha de entrega: 1 de marzo de 2026
// 318279864

#include<iostream>
#include <vector>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f;
// Función para generar un cubo con un color RGB específico para todos sus vértices
std::vector<float> generateCube(float r, float g, float b) {
	return {
		// Front
		-0.5f, -0.5f,  0.5f, r, g, b,  0.5f, -0.5f,  0.5f, r, g, b,  0.5f,  0.5f,  0.5f, r, g, b,
		 0.5f,  0.5f,  0.5f, r, g, b, -0.5f,  0.5f,  0.5f, r, g, b, -0.5f, -0.5f,  0.5f, r, g, b,
		 // Back
		 -0.5f, -0.5f, -0.5f, r, g, b,  0.5f, -0.5f, -0.5f, r, g, b,  0.5f,  0.5f, -0.5f, r, g, b,
		  0.5f,  0.5f, -0.5f, r, g, b, -0.5f,  0.5f, -0.5f, r, g, b, -0.5f, -0.5f, -0.5f, r, g, b,
		  // Right
		   0.5f, -0.5f,  0.5f, r, g, b,  0.5f, -0.5f, -0.5f, r, g, b,  0.5f,  0.5f, -0.5f, r, g, b,
		   0.5f,  0.5f, -0.5f, r, g, b,  0.5f,  0.5f,  0.5f, r, g, b,  0.5f, -0.5f,  0.5f, r, g, b,
		   // Left
		   -0.5f,  0.5f,  0.5f, r, g, b, -0.5f,  0.5f, -0.5f, r, g, b, -0.5f, -0.5f, -0.5f, r, g, b,
		   -0.5f, -0.5f, -0.5f, r, g, b, -0.5f, -0.5f,  0.5f, r, g, b, -0.5f,  0.5f,  0.5f, r, g, b,
		   // Bottom
		   -0.5f, -0.5f, -0.5f, r, g, b,  0.5f, -0.5f, -0.5f, r, g, b,  0.5f, -0.5f,  0.5f, r, g, b,
			0.5f, -0.5f,  0.5f, r, g, b, -0.5f, -0.5f,  0.5f, r, g, b, -0.5f, -0.5f, -0.5f, r, g, b,
			// Top
			-0.5f,  0.5f, -0.5f, r, g, b,  0.5f,  0.5f, -0.5f, r, g, b,  0.5f,  0.5f,  0.5f, r, g, b,
			 0.5f,  0.5f,  0.5f, r, g, b, -0.5f,  0.5f,  0.5f, r, g, b, -0.5f,  0.5f, -0.5f, r, g, b
	};
}

// Estructura para guardar la posición y el color de cada voxel
struct CubeInfo {
	float x, y, z;
	int colorID; // 0=Amarillo, 1=Negro, 2=Azul, 3=Rojo
};

int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Modelado geometrico - Yael Camarena", nullptr, nullptr);

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
	GLint colorLoc = glGetUniformLocation(ourShader.Program, "ourColor");
    // Construcción geométrica de la abeja CUBO POR CUBO
    std::vector<CubeInfo> beeCubes;
    auto addCube = [&](float x, float y, float z, int c) {
        beeCubes.push_back({ x, y, z, c });
        };

    // --- 1. CABEZA ---
    // Cara Frontal Z = -3
    for (int x = -2; x <= 2; x++) addCube(x, 8, -3, 0); // Amarillo superior
    for (int x = -3; x <= 3; x++) addCube(x, 7, -3, 0); // Amarillo cejas
    addCube(-3, 6, -3, 1); addCube(-2, 6, -3, 1);  // Ojo izquierdo sup
    for (int x = -1; x <= 1; x++) addCube(x, 6, -3, 0); // Puente nariz amarillo
    addCube(2, 6, -3, 1);  addCube(3, 6, -3, 1);   // Ojo derecho sup
    addCube(-3, 5, -3, 1); addCube(-2, 5, -3, 1);  // Ojo izquierdo inf
    for (int x = -1; x <= 1; x++) addCube(x, 5, -3, 0); // Hocico amarillo
    addCube(2, 5, -3, 1);  addCube(3, 5, -3, 1);   // Ojo derecho inf
    addCube(-3, 4, -3, 3); addCube(-2, 4, -3, 3);  // Ojo rojo izquierda
    for (int x = -1; x <= 1; x++) addCube(x, 4, -3, 0); // Boca amarilla
    addCube(2, 4, -3, 3);  addCube(3, 4, -3, 3);   // Ojo roj derecha

    // Relleno Cabeza Z = -2 y Z = -1
    for (int z = -2; z <= -1; z++) {
        for (int x = -2; x <= 2; x++) addCube(x, 8, z, 0);
        for (int y = 4; y <= 7; y++) {
            for (int x = -3; x <= 3; x++) addCube(x, y, z, 0);
        }
    }

    // --- 2. ANTENAS ---
    // Izquierda
    addCube(-2, 9, -2, 1); addCube(-2, 10, -2, 1); addCube(-3, 10, -2, 1);
    // Derecha
    addCube(2, 9, -2, 1);  addCube(2, 10, -2, 1);  addCube(3, 10, -2, 1);

    // --- 3. CUERPO (Tórax y Abdomen) ---
    for (int z = 0; z <= 7; z++) {
        // Franjas de colores: Z=(2,3 y 6,7) son negras, el resto amarillo
        int color = (z == 2 || z == 3 || z == 6 || z == 7) ? 1 : 0;
        for (int y = 3; y <= 8; y++) {
            for (int x = -3; x <= 3; x++) {
                addCube(x, y, z, color);
            }
        }
    }

    // --- 4. COLA Y AGUIJÓN ---
    for (int x = -2; x <= 2; x++) {
        for (int y = 4; y <= 8; y++) {
            addCube(x, y, 8, 0); // Cola amarilla
        }
    }
    addCube(0, 5, 9, 1); // Aguijón negro

    // --- 5. PATAS ---
    // Delanteras
    addCube(-2, 2, 0, 1); addCube(-2, 1, 0, 1); addCube(-3, 0, -1, 1);
    addCube(2, 2, 0, 1);  addCube(2, 1, 0, 1);  addCube(3, 0, -1, 1);
    // Medias
    addCube(-3, 2, 4, 1); addCube(-3, 1, 4, 1); addCube(-4, 0, 4, 1);
    addCube(3, 2, 4, 1);  addCube(3, 1, 4, 1);  addCube(4, 0, 4, 1);
    // Traseras
    addCube(-2, 2, 7, 1); addCube(-2, 1, 7, 1); addCube(-2, 0, 8, 1);
    addCube(2, 2, 7, 1);  addCube(2, 1, 7, 1);  addCube(2, 0, 8, 1);

    // --- 6. ALAS ---
    // Izquierda
    addCube(-2, 9, 3, 2);  addCube(-3, 9, 3, 2);
    addCube(-2, 9, 4, 2);  addCube(-3, 9, 4, 2);
    addCube(-3, 10, 3, 2); addCube(-4, 10, 3, 2);
    addCube(-3, 10, 4, 2); addCube(-4, 10, 4, 2);
    addCube(-3, 10, 5, 2); addCube(-4, 10, 5, 2);
    addCube(-4, 11, 2, 2); addCube(-5, 11, 2, 2);
    addCube(-4, 11, 3, 2); addCube(-5, 11, 3, 2);
    addCube(-4, 12, 2, 2); addCube(-5, 12, 2, 2);
    // Derecha
    addCube(2, 9, 3, 2);  addCube(3, 9, 3, 2);
    addCube(2, 9, 4, 2);  addCube(3, 9, 4, 2);
    addCube(3, 10, 3, 2); addCube(4, 10, 3, 2);
    addCube(3, 10, 4, 2); addCube(4, 10, 4, 2);
    addCube(3, 10, 5, 2); addCube(4, 10, 5, 2);
    addCube(4, 11, 2, 2); addCube(5, 11, 2, 2);
    addCube(4, 11, 3, 2); addCube(5, 11, 3, 2);
    addCube(4, 12, 2, 2); addCube(5, 12, 2, 2);

    // --- SETUP DE BUFFERS POR COLOR ---
    // (0: Amarillo, 1: Negro, 2: Azul, 3: Rojo)
    GLuint VAO[4], VBO[4];
    glGenVertexArrays(4, VAO);
    glGenBuffers(4, VBO);

    std::vector<float> colY = generateCube(1.0f, 0.7f, 0.0f); // Amarillo mostaza
    std::vector<float> colB = generateCube(0.15f, 0.15f, 0.15f); // Negro
    std::vector<float> colU = generateCube(0.1f, 0.6f, 1.0f); // Azul cielo
    std::vector<float> colR = generateCube(0.9f, 0.2f, 0.3f); // Rojo 

    std::vector<float>* colors[4] = { &colY, &colB, &colU, &colR };

    for (int i = 0; i < 4; i++) {
        glBindVertexArray(VAO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, colors[i]->size() * sizeof(float), colors[i]->data(), GL_STATIC_DRAW);

        // Posicion
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        // Color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
    }

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window)) {
        Inputs(window);
        glfwPollEvents();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Fondo blanco
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.Use();
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(movX, movY, movZ));
        view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
        GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");

        glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        int currentVAO = -1;

        // LA ABEJA RECORRIENDO EL ARREGLO
        for (const auto& cube : beeCubes) {
            if (currentVAO != cube.colorID) {
                glBindVertexArray(VAO[cube.colorID]);
                currentVAO = cube.colorID;
            }

            glm::mat4 model = glm::mat4(1.0f);

            // Primero la escala base para que los cubos se ajusten a la pantalla
            model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

            // Trasladamos basándonos en nuestras coordenadas matriciales.
            // Restamos -5 en Y y -3 en Z para que el centro de la abeja quede en el origen exacto de rotación
            model = glm::translate(model, glm::vec3(cube.x, cube.y - 5.0f, cube.z - 3.0f));

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


		glBindVertexArray(0);
				

		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(4, VAO);
	glDeleteBuffers(4, VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		 movY += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		 movY -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.4f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.4f;
 }


