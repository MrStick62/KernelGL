#ifndef SCENE_H
#define SCENE_H

#include "objects/scene_object.hpp"
#include "objects/camera.hpp"

#include <vector>

class GLFWwindow;

class Scene {
public:
    Scene(const std::string& name, const float aspectRatio);

    const std::string& getName() const { return name; };
    
    void play(GLFWwindow* window, const float deltaTime);
    void cleanup();

private:
    std::string name;

    std::vector<SceneObject> objects;
    std::vector<Shader> shaders;

    Camera camera;

};

#endif // SCENE_H
