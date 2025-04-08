#include <iostream>
#include <math.h>

#include "scene_object.hpp"

#include "../../tools/stb_image.h"
#include "../../tools/math/mat4x4.hpp"

SceneObject::SceneObject(Shader& shader, Vec3 position, Quat rotation, Vec3 scale) : shader(shader), position(position), rotation(rotation), scale(scale)
{
    /*
        Temp hard-coded initialization until model loader is complete
    */

    float verticies[] = {
         0.5f,  0.5f,  0.5f,     0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,     1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,     0.0f, 0.1f, 1.0f,   0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,     0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,     0.0f, 0.1f, 1.0f,   0.0f, 1.0f,
    };

    unsigned int indicies[] = {
        // FRONT
        0, 1, 2,
        2, 3, 0,
        // BACK
        4, 5, 6,
        6, 7, 4,
        // LEFT
        3, 2, 6,
        6, 7, 3,
        // RIGHT
        0, 1, 5,
        5, 4, 0,
        // TOP
        0, 4, 7,
        7, 3, 0,
        // BOTTOM
        1, 5, 6,
        6, 2, 1
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    VertexArray = VAO;
    VertexBuffer = VBO;
    ElementBuffer = EBO;

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);

    /*
        Load texture
    */

    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("../assets/images/cat.jpg", &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    data = stbi_load("../assets/images/epic.png", &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glUseProgram(shader.getID());
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);
}

/*
    Render loop
*/

void SceneObject::render(const float deltaTime, const Camera& camera) 
{
    glUseProgram(shader.getID());

    // TEMP

    float time = glfwGetTime();
    float red = std::sin(time) / 2.0f + 0.5f;
    float green = std::sin(time + 2 * M_PI / 3) / 2.0f + 0.5f;
    float blue = std::sin(time + 4 * M_PI / 3) / 2.0f + 0.5f;
    shader.setVec3("colorMultiplier", red, green, blue);
        
    // TEMP END

    //position = Vec3((sin(time) / 2), 0.0f, 0.0f);
    rotation = Quat::fromForwardUp(Vec3(sin(time), 0.0f, cos(time)), Vec3::upVector);

    Mat4x4 trans;
    trans.translate(position);
    trans.scale(scale);
    trans.rotate(rotation);
    shader.setMat4x4("transform", trans);
    shader.setMat4x4("view", camera.view);
    shader.setMat4x4("projection", camera.projection);

    glBindVertexArray(VertexArray);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void SceneObject::cleanup() 
{
    glDeleteVertexArrays(1, &VertexArray);
    glDeleteBuffers(1, &VertexBuffer);
    glDeleteBuffers(1, &ElementBuffer);
}
