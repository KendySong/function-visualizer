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
		glm::vec2 offset = mouse - m_last;
		offset *= SENSITIVITY;
		m_rotation += offset;

		m_position.x = sin(m_rotation.x);
		m_position.z = cos(m_rotation.x);

		m_last = mouse;
		this->view = glm::lookAt(m_position * m_distance, m_center, m_up);		
	}
	else
	{
		glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}