#include "Camera.hpp"
#include "../App/Application.hpp"
#include "../Config.hpp"

Camera::Camera(float speed)
{
	m_firstMove = true;
	m_canRotate = false;
	m_lastMouse = glm::vec2(0);
	m_rotation = glm::vec2(-90, 0);

	m_speed = speed;
	m_view = glm::mat4x4(1.0f);
	m_position = glm::vec3(0);
	m_up = glm::vec3(0, 1, 0);
	m_direction = glm::vec3(0, 0, -1);
}

void Camera::processMovements(float deltaTime)
{
	GLFWwindow* p_window = Application::instance()->getWindow();
	if (glfwGetKey(p_window, GLFW_KEY_W))
	{
		m_position -= m_direction * deltaTime * m_speed;
	}

	if (glfwGetKey(p_window, GLFW_KEY_A))
	{
		m_position += glm::normalize(glm::cross(m_direction, m_up)) * deltaTime * m_speed;
	}

	if (glfwGetKey(p_window, GLFW_KEY_S))
	{
		m_position += m_direction * deltaTime * m_speed;
	}

	if (glfwGetKey(p_window, GLFW_KEY_D))
	{
		m_position -= glm::normalize(glm::cross(m_direction, m_up)) * deltaTime * m_speed;
	}

	if (glfwGetKey(p_window, GLFW_KEY_SPACE))
	{
		m_position.y += deltaTime * m_speed;
	}

	if (glfwGetKey(p_window, GLFW_KEY_LEFT_SHIFT))
	{
		m_position.y -= deltaTime * m_speed;
	}

	if (glfwGetMouseButton(p_window, GLFW_MOUSE_BUTTON_RIGHT))
	{
		m_canRotate = true;
		glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else 
	{
		double x, y;
		glfwGetCursorPos(p_window, &x, &y);
		m_lastMouse.x = x;
		m_lastMouse.y = y;

		m_canRotate = false;
		glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	m_view = glm::lookAt(m_position, m_position - m_direction, m_up);
}

void Camera::rotate(glm::vec2 mousePos)
{
	if (!m_canRotate)
	{
		return;
	}

	glm::vec2 offset = mousePos - m_lastMouse;
	offset *= SENSITIVITY;	
	m_lastMouse = mousePos;
	m_rotation += offset;

	if (m_rotation.y > 89.9)
	{
		m_rotation.y = 89.9;
	}

	if (m_rotation.y < -89.9)
	{
		m_rotation.y = -89.9;
	}

	glm::vec2 radianRotation(glm::radians(m_rotation.x), glm::radians(m_rotation.y));
	m_direction.x = cos(radianRotation.x) * cos(radianRotation.y);
	m_direction.y = sin(radianRotation.y);
	m_direction.z = sin(radianRotation.x) * cos(radianRotation.y);
	m_direction = glm::normalize(m_direction);
}

glm::mat4x4& Camera::getView() noexcept
{
	return m_view;
}

glm::vec3& Camera::getPosition() noexcept
{
	return m_position;
}