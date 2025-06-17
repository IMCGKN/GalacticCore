#pragma once

#include <glad/glad.h>

#include <Helper.h>

class Shader
{
private:
	unsigned int ID;
	bool isUsed = false;

	std::map<std::string, int> uniformLocations;

public:
	Shader(const std::string& vFilePath, const std::string& fFilePath);
	Shader(const std::string& vShaderContent, const std::string& fShaderContent, bool v);
	~Shader();

	void Use();
	void Unuse();

	int GetUniformLocation(const std::string& name);

	void SetMat4(const std::string& name, const glm::mat4& v);
	void SetVec4(const std::string& name, const glm::vec4& v);
	void SetVec3(const std::string& name, const glm::vec3& v);
	void SetVec2(const std::string& name, const glm::vec2& v);
	void SetFloat(const std::string& name, float v);
	void SetInt(const std::string& name, int v);
	void SetBool(const std::string& name, bool v);
};
