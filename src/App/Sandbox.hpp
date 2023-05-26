#pragma once
#include <vector>

#include <ImGui/imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Timer.hpp"
#include "RenderMode.hpp"
#include "../Graphics/Shader.hpp"
#include "../Graphics/Plane.hpp"
#include "../Graphics/OrbitCamera.hpp"

class Sandbox
{
public :
    Sandbox() = default;
    Sandbox(GLFWwindow* window);

    void update(float deltaTime);
    void render();
    
private :
    std::uint32_t m_displayFramerate;
    std::uint32_t m_framerate;
    Timer m_framerateTimer;

    std::vector<RenderMode> m_renderMode;
    RenderMode m_currentMode;

    Shader m_shader;
    OrbitCamera m_camera;
    
    Plane m_gridMesh;
    Plane m_functionMesh;
    bool m_drawMesh;
    glm::vec3 m_meshColor;

    float m_maxValue;
    bool m_displayGrid;
    glm::vec3 m_gridColor;

    std::uint32_t m_fbo;
    std::uint32_t m_rbo;
    ImVec2 m_imageCorner;
    std::uint32_t m_frameTexture;
    
    bool m_autoScroll;
    std::string m_logs;
    std::uint32_t m_logLine;
   
    GLFWwindow* p_window;
};