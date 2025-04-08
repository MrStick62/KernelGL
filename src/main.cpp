#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>

#include "shaders/shader.hpp"
#include "scenes/scene.hpp"
#include "scenes/objects/scene_object.hpp"

/*
    Determines the default window size
*/

const unsigned int windowWidth = 800;
const unsigned int windowHeight = 600;

/*
    Variables used for toggling wireframe and potentially more rendering modes
*/

enum RenderMode {
    RM_STANDARD,
    RM_WIREFRAME,
    RM_SIZE,
};

int renderMode = RM_STANDARD;
bool canChangeRM = true;

/*
    Maximum frame rate
*/

const int maxFrameRate = 60;
const float minFrameTime = 1.0f / maxFrameRate;

/*
    Time point used to calculate delta time
*/

std::chrono::high_resolution_clock::time_point lastTime = std::chrono::high_resolution_clock::now();
float deltaTime = maxFrameRate;

/*
    Callback functions for the rendering loop
*/

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

void getDeltaTime();

int main()
{
    /*
        Initialization of GLFW and GLEW
    */

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "OpenGL Window", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n" << std::endl;
        return -1;
    }

    glViewport(0, 0, windowWidth, windowHeight);

    /*
        Initialize scene object
    */

    Scene scene("Main Scene", static_cast<float>(windowWidth) / static_cast<float>(windowHeight));

    /*
        Game (render) loop
    */

   glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) 
    {
        processInput(window);

        scene.play(window, deltaTime);
        getDeltaTime();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /*
        Cleanup
    */

    scene.cleanup();

    glfwTerminate();
    return 0;
}

/*
    Adjust 3D scale when window size changes
*/

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

/*
    Perform appropriate actions based on incoming input
*/

void processInput(GLFWwindow* window) 
{
    /*
        Close the window if [ESC] is pressed
    */

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    /*
        Toggle wireframe mode with [\]
    */

    if (glfwGetKey(window, GLFW_KEY_BACKSLASH) == GLFW_PRESS) 
    {
        if (canChangeRM) {
            renderMode = ++renderMode % RM_SIZE;

            if (renderMode == RM_STANDARD) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            } else if (renderMode == RM_WIREFRAME) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
        }

        canChangeRM = false;
    } 
    else
    {
        canChangeRM = true;
    }
}

/*
    Calculate delta time and cap frame rate
*/

void getDeltaTime() {
    std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
    float frameTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - lastTime).count();

    if (frameTime > minFrameTime) {
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>((minFrameTime - frameTime) * 1000)));
    }

    currentTime = std::chrono::high_resolution_clock::now();
    deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - lastTime).count();
    lastTime = std::chrono::high_resolution_clock::now();
}
