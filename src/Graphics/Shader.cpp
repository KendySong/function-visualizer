#include <sstream>
#include <fstream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "../App/Log.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	m_program = 0;
	std::pair<std::string, bool> vertexSource = this->loadShader(vertexPath);
	std::pair<std::string, bool> fragmentSource = this->loadShader(fragmentPath);
	const char* vSrc = vertexSource.first.c_str();
	const char* fSrc = fragmentSource.first.c_str();
	if (!vertexSource.second || !fragmentSource.second)
	{
		return;
	}

	std::uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, &vSrc, 0);
	glShaderSource(fragmentShader, 1, &fSrc, 0);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	if (!this->checkCompileStatus(vertexShader, "vertex shader") ||
		!this->checkCompileStatus(fragmentShader, "fragment shader"))
	{
		return;
	}

	m_program = glCreateProgram();
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);

	int linkStatus = false;
	glGetProgramiv(m_program, GL_LINK_STATUS, &linkStatus);
	if (!linkStatus)
	{
		int length = 0;
		std::string errorMsg = "";
		std::vector<char> errorMessage(length);

		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &length);
		glGetProgramInfoLog(m_program, length, &length, errorMessage.data());
		for (size_t i = 0; i < errorMessage.size(); i++)
		{
			errorMsg += errorMessage[i];
		}

#ifdef DEBUG
		Log::instance()->log("[ERROR] link error : " + errorMsg + "\n", RED);
#endif

		return;
	}

	glDetachShader(m_program, vertexShader);
	glDetachShader(m_program, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::setMat4x4(const char* name, const glm::mat4x4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(this->m_program, name), 1, false, glm::value_ptr(matrix));
}

void Shader::setVec3(const char* name, const glm::vec3& vec)
{
	glUniform3fv(glGetUniformLocation(m_program, name), 1, glm::value_ptr(vec));
}

std::uint32_t Shader::getProgram() noexcept
{
	return m_program;
}

bool Shader::checkCompileStatus(std::uint32_t shaderID, std::string name)
{
	int shaderCompileStatus = false;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompileStatus);
	if (!shaderCompileStatus)
	{
		int length = 0;
		std::string finalErrorMsg = "";

		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

		std::vector<char> errorMessage(length);
		glGetShaderInfoLog(shaderID, length, &length, errorMessage.data());
		for (size_t i = 0; i < errorMessage.size(); i++)
		{
			finalErrorMsg += errorMessage[i];
		}
#ifdef DEBUG
		Log::instance()->log("[ERROR] Compilation failed (" + name + ") : " + finalErrorMsg + "\n", RED);
#endif
		return false;
	}
	else
	{
		return true;
	}
}

std::pair<std::string, bool> Shader::loadShader(const char* shaderPath)
{
	std::pair<std::string, bool> result("", false);
	std::fstream fileReader(shaderPath);
	if (fileReader.is_open())
	{
		std::stringstream sStream;
		sStream << fileReader.rdbuf();
		std::string sShader = sStream.str();
		result.first = sShader;
		result.second = true;
		fileReader.close();
	}
	else
	{
#ifdef DEBUG
		Log::instance()->log("[ERROR] Shader not found : " + std::string(shaderPath) + "\n", RED);
#endif
	}

	return result;
}