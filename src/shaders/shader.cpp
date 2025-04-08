#include <iostream>
#include <fstream>
#include <sstream>

#include "shader.hpp"

Shader::Shader(const std::string& vPath, const std::string& fPath) 
{
    /*
        Read shader code files and store them appropriately
    */

    std::string vCodeString, fCodeString;

    try 
    {
        std::ifstream vFile(vPath), fFile(fPath);
        std::stringstream vBuffer, fBuffer;
        
        vBuffer << vFile.rdbuf();
        fBuffer << fFile.rdbuf();

        vFile.close();
        fFile.close();

        vCodeString = vBuffer.str();
        fCodeString = fBuffer.str();

    } catch (std::exception e) 
    {
        std::cerr << "ERROR::SHADER::FAILED_TO_READ_FILE" << std::endl;
    }

    const char* vShaderCode = vCodeString.c_str();
    const char* fShaderCode = fCodeString.c_str();

    /*
        Initialize and compile the shaders
    */

    unsigned int vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
    glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    /*
        Verify compile success
    */

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    /*
        Initialize and compile the shader program
    */

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    /*
        Shader cleanup
    */

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    ID = shaderProgram;
}

void Shader::cleanup() {
    glDeleteShader(ID);
}

void Shader::setInt(std::string name, int n)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), n);
}

void Shader::setFloat(std::string name, float n)
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), n);
}

void Shader::setVec3(std::string name, float x, float y, float z) 
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec4(std::string name, float x, float y, float z, float w) 
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setMat4x4(std::string name, const Mat4x4& matrix) {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, matrix.glFormat());
}
