#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../tools/math/mat4x4.hpp"

class Shader
{
public:

    Shader(const std::string& vPath, const std::string& fPath);

    const GLuint getID() const { return ID; }

    virtual void cleanup();

    void setInt(std::string name, int n);
    void setFloat(std::string name, float n);
    void setVec3(std::string name, float x, float y, float z);
    void setVec4(std::string name, float x, float y, float z, float w);
    void setMat4x4(std::string name, const Mat4x4& matrix);

private:
    GLuint ID;

};

#endif // SHADER_H
