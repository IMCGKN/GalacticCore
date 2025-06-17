#include <Graphics/Shader.h>

enum ShaderType : int8_t
{
	Frag,
	Vert
};

static void GetShaderCompileErrors(unsigned int shaderId, ShaderType type)
{
	int success;

	std::string typeString = type == Vert ? "Vertex" : "Fragment";
#ifndef NDEBUG
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);

		Warning("Failed to compile " << typeString << " shader.\nInfo Log: " << infoLog);
	}
	else
	{
		Warning("Succesfully compiled " << typeString << " shader.");
	}
#endif
}

Shader::Shader(const std::string& vFilePath, const std::string& fFilePath)
{
	std::string vFileContent = LoadFileContents(vFilePath);
	std::string fFileContent = LoadFileContents(fFilePath);

	const char* vShaderSource = vFileContent.c_str();
	const char* fShaderSource = fFileContent.c_str();

	unsigned int vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderSource, nullptr);
	glCompileShader(vertex);
	GetShaderCompileErrors(vertex, Vert);

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderSource, nullptr);
	glCompileShader(fragment);
	GetShaderCompileErrors(fragment, Frag);

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::Shader(const std::string& vShaderContent, const std::string& fShaderContent, bool v)
{
	const char* vShaderSource = vShaderContent.c_str();
	const char* fShaderSource = fShaderContent.c_str();

	unsigned int vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderSource, nullptr);
	glCompileShader(vertex);
	GetShaderCompileErrors(vertex, Vert);

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderSource, nullptr);
	glCompileShader(fragment);
	GetShaderCompileErrors(fragment, Frag);

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
	glDeleteProgram(ID);
}

void Shader::Use()
{
	if (!isUsed)
	{
		isUsed = true;
		glUseProgram(ID);
	}
}

void Shader::Unuse()
{
	if (isUsed)
	{
		isUsed = false;
		glUseProgram(0);
	}
}

int Shader::GetUniformLocation(const std::string& name)
{
	auto it = uniformLocations.find(name);

	if (it != uniformLocations.end())
	{
		return it->second;
	}
	else
	{
		int location = glGetUniformLocation(ID, name.c_str());

		uniformLocations.insert({ name, location });

		return location;
	}
}

void Shader::SetMat4(const std::string& name, const glm::mat4& v)
{
	Use();
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(v));
}

void Shader::SetVec4(const std::string& name, const glm::vec4& v)
{
	Use();
	glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(v));
}

void Shader::SetVec3(const std::string& name, const glm::vec3& v)
{
	Use();
	glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(v));
}

void Shader::SetVec2(const std::string& name, const glm::vec2& v)
{
	Use();
	glUniform2fv(GetUniformLocation(name), 1, glm::value_ptr(v));
}

void Shader::SetFloat(const std::string& name, float v)
{
	Use();
	glUniform1f(GetUniformLocation(name), v);
}

void Shader::SetInt(const std::string& name, int v)
{
	Use();
	glUniform1i(GetUniformLocation(name), v);
}

void Shader::SetBool(const std::string& name, bool v)
{
	Use();
	glUniform1i(GetUniformLocation(name), v);
}
