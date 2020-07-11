// GLFWTesting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Imports
#define _USE_MATH_DEFINES
#include <iostream>
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//File interactions
#include "ErrorCallback.h"
#include "CRender.h"
#include "Vector2D.h"
#include "CShape.h"
#include "Camera.h"
#include "ObjectReader.h"
#include "ObjectWriter.h"
#include "CommandHandler.h"
Camera cam;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(void)
{
    //Create CShape and cam
    cam = Camera(0, 0, 0, M_PI / 2.01, M_PI / 2);

    CShape cube = loadFile("Cube.txt");
    
    CShape icosahedron = loadFile("Icosahedron.txt");

    //Create CShape and cam
    GLFWwindow* window;


    glfwSetErrorCallback(error_callback);
    

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(750, 750, "3D Rendering", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    gladLoadGL();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    //double time = glfwGetTime(); // for animations

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        CRender::clear();
        double startTime = glfwGetTime();
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);


        cube.transform(cam);
        cube.render();
        icosahedron.transform(cam);
        icosahedron.render();
        //update movement
        cam.applyMovement();
        //update movement

        glBegin(GL_LINES);
        int size = CRender::lineStartVertices.size();
        for (int i = 0; i < size; i++) {
            Vector2D point1 = CRender::lineStartVertices.at(i);
            Vector2D point2 = CRender::lineEndVertices.at(i);
            glVertex2f(point1.x, point1.y);
            glVertex2f(point2.x, point2.y);
        }
        glEnd();
        double frameTime = glfwGetTime() - startTime;
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        std::cout << frameTime*1000 << " ms\n"; // test frame response time
    }

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_A) {
        if (action == GLFW_PRESS) {
            cam.moveLeft = true;
        }
        else if (action == GLFW_RELEASE) {
            cam.moveLeft = false;
        }
    }
    if (key == GLFW_KEY_W) {
        if (action == GLFW_PRESS) {
            cam.moveForward = true;
        }
        else if (action == GLFW_RELEASE) {
            cam.moveForward = false;
        }
    }
    if (key == GLFW_KEY_S) {
        if (action == GLFW_PRESS) {
            cam.moveBackward = true;
        }
        else if (action == GLFW_RELEASE) {
            cam.moveBackward = false;
        }
    }
    if (key == GLFW_KEY_D) {
        if (action == GLFW_PRESS) {
            cam.moveRight = true;
        }
        else if (action == GLFW_RELEASE) {
            cam.moveRight = false;
        }
    }
    if (key == GLFW_KEY_LEFT) {
        if (action == GLFW_PRESS) {
            cam.lookLeft = true;
        }
        else if (action == GLFW_RELEASE) {
            cam.lookLeft = false;
        }
    }
    if (key == GLFW_KEY_RIGHT) {
        if (action == GLFW_PRESS) {
            cam.lookRight = true;
        }
        else if (action == GLFW_RELEASE) {
            cam.lookRight = false;
        }
    }
    if (key == GLFW_KEY_DOWN) {
        if (action == GLFW_PRESS) {
            cam.lookDown = true;
        }
        else if (action == GLFW_RELEASE) {
            cam.lookDown = false;
        }
    }
    if (key == GLFW_KEY_UP) {
        if (action == GLFW_PRESS) {
            cam.lookUp = true;
        }
        else if (action == GLFW_RELEASE) {
            cam.lookUp = false;
        }
    }
    if (key == GLFW_KEY_SPACE) {
        if (action == GLFW_PRESS) {
            cam.moveUp = true;
        }
        else if (action == GLFW_RELEASE) {
            cam.moveUp = false;
        }
    }
    if (key == GLFW_KEY_LEFT_SHIFT) {
        if (action == GLFW_PRESS) {
            cam.moveDown = true;
        }
        else if (action == GLFW_RELEASE) {
            cam.moveDown = false;
        }
    }
    if (key == GLFW_KEY_SLASH) {
        handleCommand();
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
