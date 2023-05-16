#include <vector>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include <glad/glad.h>

#include "Sandbox.hpp"
#include "../Config.hpp"
#include "../Graphics/Texture.hpp"
#include "Application.hpp"

Sandbox::Sandbox()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    float vertices[]
    {
        -0.5f, -0.5f, -0.5f,   
         0.5f, -0.5f, -0.5f,  
         0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f, -0.5f,  
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,  

        -0.5f, -0.5f,  0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,  

        -0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f, -0.5f,  
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f,  

         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f, -0.5f,
    };

    unsigned int vao = 0;
    unsigned int vbo = 0;
   
    m_shader = Shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");
    glUseProgram(m_shader.getProgram());  

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);

    m_transform = glm::mat4x4(1.0f);
    m_position = glm::vec3(0, 0, 0);
    m_camera = Camera(2);
    
    m_projection = glm::perspective(glm::radians(90.0f), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.001f, 100.0f);
    std::uint32_t locView = glGetUniformLocation(m_shader.getProgram(), "view");
    std::uint32_t locProjection = glGetUniformLocation(m_shader.getProgram(), "projection");
    glUniformMatrix4fv(locView, 1, false, glm::value_ptr(m_camera.getView()));
    glUniformMatrix4fv(locProjection, 1, false, glm::value_ptr(m_projection));
}

void Sandbox::update(float deltaTime)
{
    //Manage camera
    double x, y;
    m_camera.processMovements(deltaTime); 
    glfwGetCursorPos(Application::instance()->getWindow(), &x, &y);
    m_camera.rotate(glm::vec2(x, y));
    std::uint32_t locView = glGetUniformLocation(m_shader.getProgram(), "view");
    glUniformMatrix4fv(locView, 1, false, glm::value_ptr(m_camera.getView()));

    //Transform cube
    m_transform = glm::mat4x4(1.0f);
    m_transform = glm::translate(m_transform, m_position);
    std::uint32_t locTransform = glGetUniformLocation(m_shader.getProgram(), "transform");
    glUniformMatrix4fv(locTransform, 1, GL_FALSE, glm::value_ptr(m_transform));
}

void Sandbox::render()
{
    glDrawArrays(GL_TRIANGLES, 0, 36);
}