#include "scene.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../tools/math/vec3.hpp"
#include "../tools/math/mat4x4.hpp"

Scene::Scene(const std::string& name, const float aspectRatio) : name(name) 
{
    /*
        Initialize shaders
    */

    camera = Camera(aspectRatio, Vec3(0.0f, 0.0f, -3.0f), Quat::identity, 45.0f, 0.1f, 100.0f);

    Shader solidColor("../src/shaders/solidcolor.vert", "../src/shaders/solidcolor.frag");
    shaders.push_back(solidColor);

    /*
        3D shapes initialization
    */

    SceneObject object(solidColor, Vec3(0.0, 0.0, 0.0), Quat::identity, Vec3(1.0, 1.0, 1.0));
    objects.push_back(object);
}

/*
    Render loop for loading scene objects
*/


void Scene::play(GLFWwindow* window, const float deltaTime) 
{
    /*
        Process input
    */

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        //camera.position += camera.rotation.getForwardVector();
    }

    /*
        Render scene
    */

    glClearColor(0.0f, 0.4f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (SceneObject& object : objects) {
        object.render(deltaTime, camera);
    }
}

/*
    Cleanup objects and shaders associated with scene on program close
*/

void Scene::cleanup() 
{
    for (SceneObject& object : objects)
        object.cleanup();
    
    for (Shader& shader : shaders)
        shader.cleanup();
}
