#include "OrbitCamera.hpp"
#include "../App/Application.hpp"
#include "../Config.hpp"

#include <iostream>

OrbitCamera::OrbitCamera(GLFWwindow* window, glm::vec3 center, float distance)
{
	p_window = window;
	m_up = glm::vec3(0, 1, 0);
	m_center = center;
	m_distance = distance;
}

void OrbitCamera::processMovements(float deltaTime, glm::vec2 mouse)
{
	if (glfwGetMouseButton(p_window, GLFW_MOUSE_BUTTON_RIGHT))
	{
		glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		m_rotation += (mouse - m_last) * SENSITIVITY;

		m_position.x = sin(m_rotation.x) * cos(m_rotation.y);
		m_position.y = sin(m_rotation.y);
		m_position.z = cos(m_rotation.x) * cos(m_rotation.y);
			
		this->view = glm::lookAt(m_position * m_distance + glm::vec3(0, 1, 0), m_center, m_up);
	}
	else
	{
		glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	m_last = mouse;
}