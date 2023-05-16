#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Graphics/Shader.hpp"
#include "../Graphics/Camera.hpp"
#include "../Graphics/DiffuseLight.hpp"

class Sandbox
{
public :
    Sandbox();

    void update(float deltaTime);
    void render();
    
private :
    Shader m_shader;

    glm::vec3 m_position;
    glm::mat4x4 m_transform;

    Camera m_camera;
    glm::mat4x4 m_projection;
};