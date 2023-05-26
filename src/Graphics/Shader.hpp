#pragma once
#include <string>

#include <glm/glm.hpp>

class Shader
{
public:
	Shader() = default;
	Shader(const char* vertexPath, const char* fragmentPath);

	void setMat4x4(const char* name, const glm::mat4x4& matrix);
	void setVec3(const char* name, const glm::vec3& vec);
	void setFloat(const char* name, float value);
	void setBool(const char* name, bool value);
	std::uint32_t getProgram() noexcept;

private:
	bool checkCompileStatus(std::uint32_t objectID, std::string name);
	std::pair<std::string, bool> loadShader(const char* shaderPath);

	std::uint32_t m_program;
};