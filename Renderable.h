#pragma once

#include <Helper.h>

#include <Window/Window.h>

#include <Graphics/Shader.h>
#include <Graphics/Texture.h>
#include <Graphics/VAO.h>
#include <Graphics/VBO.h>
#include <Graphics/EBO.h>

class Renderable
{
private:
	std::unique_ptr<VAO> vao;
	std::unique_ptr<VBO> vbo;
	std::unique_ptr<EBO> ebo;

	std::unique_ptr<Texture> texture;

public:
	Renderable(const std::vector<Vertex>& vertices, int vboUsage, const std::vector<unsigned int>& indices, int eboUsage);
	~Renderable();

	void ConstructTexture(const std::string& filepath, int _textureType, int _textureFormat, int minFilter, int magFilter);
	void ConstructTexture(int resource, int _textureType, int _textureFormat, int minFilter, int magFilter);

	void Render(Shader& shader, unsigned int renderMode, const glm::mat4& model);

	Texture& GetTexture() const;
};
