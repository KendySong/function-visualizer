#include <vector>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include <glad/glad.h>

#include "../Config.hpp"
#include "../Graphics/Vertex.hpp"
#include "Application.hpp"
#include "Sandbox.hpp"

Sandbox::Sandbox()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    m_shader = Shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");
    glUseProgram(m_shader.getProgram());
   
    Vertex vertices[]
    {
        {{ -0.5, 0,  0.5 }, {0, 1, 0}},
        {{ -0.5, 0, -0.5 }, {0, 1, 0}},
        {{  0.5, 0,  0.5 }, {0, 1, 0}},
        {{  0.5, 0, -0.5 }, {0, 1, 0}},
        {{ -0.5, 0, -0.5 }, {0, 1, 0}},
        {{  0.5, 0,  0.5 }, {0, 1, 0}},
    };

    std::uint32_t vao = 0;
    std::uint32_t vbo = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 2 * sizeof(glm::vec3), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 2 * sizeof(glm::vec3), (void*)(sizeof(glm::vec3)));

    m_transform = glm::mat4x4(1.0f);
    m_position = glm::vec3(0, 0, 0);
    m_camera = Camera(2);
    
    m_projection = glm::perspective(glm::radians(90.0f), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.001f, 10000.0f);
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

    //Transform model
    m_transform = glm::mat4x4(1.0f);
    m_transform = glm::translate(m_transform, m_position);
    std::uint32_t locTransform = glGetUniformLocation(m_shader.getProgram(), "transform");
    glUniformMatrix4fv(locTransform, 1, GL_FALSE, glm::value_ptr(m_transform));
}

void Sandbox::render()
{
    glDrawArrays(GL_TRIANGLES, 0, 36);

    /*
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("File"))
    {
        ImGui::MenuItem("Load");
        ImGui::MenuItem("Save");
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();

    ImGui::DockSpaceOverViewport();
    ImGui::Begin("Functions");

    ImGui::End();

    ImGui::Begin("Render");

    ImGui::End();
    */
}