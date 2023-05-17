#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Graphics/Shader.hpp"
#include "../Graphics/OrbitCamera.hpp"

class Sandbox
{
public :
    Sandbox();

    void update(float deltaTime);
    void render();
    
private :
    Shader m_shader;
    OrbitCamera m_camera;
    glm::mat4x4 m_projection;

    glm::vec3 m_position;
    glm::mat4x4 m_transform; 
    
};