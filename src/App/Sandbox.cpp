#include <limits>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include <glad/glad.h>

#include "Sandbox.hpp"
#include "../Config.hpp"
#include "../Graphics/Vertex.hpp"
#include "../Interpreter/Lexer.hpp"
#include "../Interpreter/Interpreter.hpp"

Sandbox::Sandbox(GLFWwindow* window)
{
    p_window = window;
    m_framerate = 0;
    m_maxValue = BASE_MAX_FUNCTION;
    m_autoScroll = true;
    m_displayGrid = true;
    m_displayFramerate = 0;
    m_renderMode = { 
        { "Wireframe", []() {glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); } },
        { "Fill",      []() {glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); } },
        { "Points",    []() {glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);} }
    };
    m_currentMode = m_renderMode[1];
    m_gridColor = glm::vec3(0, 1, 0);

    m_drawMesh = true;
    m_meshColor = glm::vec3(1, 1, 1);
    m_gridOffset = glm::vec2(0, 0);

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

    m_gridMesh = Plane(
        glm::vec2(PLANE_SIZE_X, PLANE_SIZE_Y),
        m_gridColor,
        nullptr
    );
  
    m_functionMesh = Plane(
        glm::vec2(PLANE_SIZE_X, PLANE_SIZE_Y),
        m_gridColor,
        nullptr
    );
    
    //Set up camera and projection
    float aspectRatio = (float)WIN_WIDTH / (float)WIN_HEIGHT;
    glm::mat4x4 projection = glm::perspective(glm::radians(50.0f), aspectRatio, 0.1f, 10000.0f);
    m_shader.setMat4x4("projection", projection);
    m_camera = OrbitCamera(window, glm::vec3(0, 0, 0), 32);
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

    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (m_displayGrid)
    {
        m_shader.setBool("isMeshFunction", false);
        m_gridMesh.draw();
    }

    if (m_currentMode.name != "Points")
    {
        m_shader.setBool("isMeshFunction", m_drawMesh);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        m_functionMesh.draw();
    }
    
    m_currentMode.setRenderMode();
    m_shader.setBool("isMeshFunction", false);
    m_functionMesh.draw(); 

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    ImGui::BeginMainMenuBar();
    ImGui::Text("FPS %d", m_displayFramerate);
    ImGui::EndMainMenuBar();

    ImGui::DockSpaceOverViewport();
    ImGui::Begin("Functions");
    
    ImGui::InputText("Function", funcBuffer, sizeof(funcBuffer));
    ImGui::DragFloat("Max value", &m_maxValue, 0.01, 0, std::numeric_limits<float>::max());
    ImGui::DragFloat("Zoom", &m_camera.distance, 1, 0, std::numeric_limits<float>::max());
    ImGui::DragFloat2("Graph size", &planeSize[0], 0.1);
    ImGui::DragFloat2("Grid offset", &m_gridOffset[0], 0.1);
    
    m_shader.setFloat("maxFunctionOut", m_maxValue);
    if (ImGui::Button("Apply"))
    {
        //Regenerate meshes with function interpretation
        std::string function(funcBuffer);
        if (function.size() > 0)
        {
            //Lex the function here for avoid lex for each point of the grid
            Lexer lexer(function);
            Interpreter interpreter(*lexer.tokens);

            m_gridMesh = Plane(
                glm::vec2(planeSize[0], planeSize[1]),
                m_gridColor,
                nullptr
            );

            m_functionMesh = Plane(
                glm::vec2(planeSize[0], planeSize[1]),
                m_gridColor,
                &interpreter,
                m_gridOffset
            );

            m_logLine = interpreter.errors.size();
            for (size_t i = 0; i < interpreter.errors.size(); i++)
            {
                m_logs += interpreter.errors[i];
            }
        }
    }
    ImGui::End();

    ImGui::Begin("Console");
        if (ImGui::Button("Clear"))
        {
            m_logs = "";
        }
        ImGui::SameLine();
        ImGui::Checkbox("Scroll to bottom", &m_autoScroll);
        ImGui::Separator();

        ImGui::BeginChild("child");
            if (m_autoScroll)
            {
                ImGui::SetScrollY(ImGui::GetTextLineHeight() * m_logLine);
            }
            ImGui::TextUnformatted(m_logs.c_str());
        ImGui::EndChild();
    ImGui::End();

    ImGui::Begin("Graphics");
        if (ImGui::BeginCombo("Rendering mode", m_currentMode.name.c_str()))
        {
            for (size_t i = 0; i < m_renderMode.size(); i++)
            {
                if (ImGui::Selectable(m_renderMode[i].name.c_str(), m_renderMode[i].name == m_currentMode.name))
                {
                    m_currentMode = m_renderMode[i];
                    m_renderMode[i].setRenderMode();
                }
            }
            ImGui::EndCombo();
        } 
        ImGui::Checkbox("Display Grid", &m_displayGrid);
        ImGui::DragFloat("Camera height", &m_camera.offsetOrigin.y);
        ImGui::ColorEdit3("Grid color", &m_gridColor[0]);
        ImGui::SameLine();
        if (ImGui::Button("Apply"))
        {
            m_gridMesh = Plane(
                glm::vec2(planeSize[0], planeSize[1]),
                m_gridColor,
                nullptr
            );
        }  

        ImGui::Checkbox("Draw function mesh", &m_drawMesh);
        ImGui::ColorEdit3("function mesh color", &m_meshColor[0]);
        m_shader.setVec3("meshColor", m_meshColor);
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