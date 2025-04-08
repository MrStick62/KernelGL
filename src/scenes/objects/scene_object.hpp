#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../../tools/math/vec3.hpp"
#include "../../shaders/shader.hpp"
#include "camera.hpp"

class SceneObject {
public:
    SceneObject(Shader& shader, Vec3 position, Quat rotation, Vec3 scale);

    virtual void render(const float deltaTime, const Camera& camera);
    virtual void cleanup();

    Vec3 position;
    Vec3 scale;
    Quat rotation;

protected:
    Shader shader;

    GLuint VertexArray;
    GLuint VertexBuffer;
    GLuint ElementBuffer;

    // something that stores verticies and such
};

#endif // SCENE_OBJECT_H
