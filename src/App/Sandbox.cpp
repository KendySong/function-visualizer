#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include <glad/glad.h>

#include "Sandbox.hpp"
#include "../Config.hpp"
#include "../Graphics/Vertex.hpp"
#include "Application.hpp"

Sandbox::Sandbox(GLFWwindow* window)
{
    p_window = window;
    m_displayFramerate = 0;
    m_framerate = 0;
    m_renderMode = { 
        { "Wireframe", []() {glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); } },
        { "Fill",      []() {glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); } },
        { "Points",    []() {glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);} }
    };
    m_currentMode = m_renderMode[0].name;

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
    glClearColor(0, 0, 0, 1);

    m_shader = Shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");
    glUseProgram(m_shader.getProgram());
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    glGenTextures(1, &m_frameTexture);
    glBindTexture(GL_TEXTURE_2D, m_frameTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIN_WIDTH, WIN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_frameTexture, 0);

    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIN_WIDTH, WIN_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

    m_plane = Plane(
        glm::vec2(PLANE_SIZE_X, PLANE_SIZE_Y), 
        glm::vec2(PLANE_GRID_X, PLANE_GRID_Y)
    );
    
    //Set up camera and projection
    float aspectRatio = (float)WIN_WIDTH / (float)WIN_HEIGHT;
    glm::mat4x4 projection = glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 10000.0f);
    m_shader.setMat4x4("projection", projection);
    m_camera = OrbitCamera(window, glm::vec3(0, 0, 0), 10);
}

void Sandbox::update(float deltaTime)
{
    double x, y;
    glfwGetCursorPos(p_window, &x, &y);
    m_camera.processMovements(deltaTime, glm::vec2(x, y));
    m_shader.setMat4x4("view", m_camera.view);

    m_framerate++;
    if (m_framerateTimer.getElapsedTime() >= 1)
    {
        m_displayFramerate = m_framerate;
        m_framerateTimer.restart();
        m_framerate = 0;
    }
}

void Sandbox::render()
{
    static char funcBuffer[512] = "";
    static float planeSize[2] = { PLANE_SIZE_X, PLANE_SIZE_Y };
    static int planeGrid[2] = { PLANE_GRID_X, PLANE_GRID_Y };

    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, m_plane.elementSize, GL_UNSIGNED_INT, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    ImGui::BeginMainMenuBar();
    ImGui::Text("FPS %d", m_displayFramerate);
    ImGui::EndMainMenuBar();

    ImGui::DockSpaceOverViewport();
    ImGui::Begin("Functions");
    
    ImGui::InputText("Function", funcBuffer, sizeof(funcBuffer));
    ImGui::DragFloat2("Graph size", &planeSize[0], 0.1);
    ImGui::DragInt2("Graph grid size", &planeGrid[0], 0.1);

    if (ImGui::Button("Apply"))
    {    
        m_plane = Plane(
            glm::vec2(planeSize[0], planeSize[1]),
            glm::vec2(planeGrid[0], planeGrid[1])
        );
        std::string function(funcBuffer);
    }
    ImGui::End();

    ImGui::Begin("Graphics");
        if (ImGui::BeginCombo("Rendering mode", m_currentMode.c_str()))
        {
            for (size_t i = 0; i < m_renderMode.size(); i++)
            {
                if (ImGui::Selectable(m_renderMode[i].name.c_str(), m_renderMode[i].name == m_currentMode))
                {
                    m_currentMode = m_renderMode[i].name;
                    m_renderMode[i].setRenderMode();
                }
            }
            ImGui::EndCombo();
        } 
    ImGui::End();

    ImGui::Begin("Render");  
        ImVec2 cursorPos = ImGui::GetCursorScreenPos();
        ImGui::GetWindowDrawList()->AddImage(
            (ImTextureID)m_frameTexture,
            ImVec2(ImGui::GetCursorPos().x, ImGui::GetCursorPos().y + 15),
            ImVec2(cursorPos.x + RENDER_WIDTH, cursorPos.y + RENDER_HEIGHT)
        );
    ImGui::End();
}