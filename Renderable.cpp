#include "Renderable.h"

Renderable::Renderable(const std::vector<Vertex>& vertices, int vboUsage, const std::vector<unsigned int>& indices, int eboUsage)
{
	vao = std::make_unique<VAO>();

	vao->Use();

	vbo = std::make_unique<VBO>(vertices, GL_STATIC_DRAW);
	ebo = std::make_unique<EBO>(indices, GL_STATIC_DRAW);

	ebo->Use();

	vbo->Use();
	vao->LinkAttrib(0, 2, GL_FLOAT, sizeof(Vertex), (const void*)offsetof(Vertex, aPos));
	vao->LinkAttrib(1, 2, GL_FLOAT, sizeof(Vertex), (const void*)offsetof(Vertex, aUV));

	vao->Unuse();
}

Renderable::~Renderable()
{
}

void Renderable::ConstructTexture(const std::string& filepath, int _textureType, int _textureFormat, int minFilter, int magFilter)
{
	texture = std::make_unique<Texture>(filepath, _textureType, _textureFormat, minFilter, magFilter);
}

void Renderable::ConstructTexture(int resource, int _textureType, int _textureFormat, int minFilter, int magFilter)
{
	texture = std::make_unique<Texture>(resource, _textureType, _textureFormat, minFilter, magFilter);
}

void Renderable::Render(Shader& shader, unsigned int renderMode, const glm::mat4& model)
{
	shader.Use();
	shader.SetMat4("Model", model);

	if (texture != nullptr)
	{
		shader.SetInt("tex0", texture->GetTextureID());
		texture->Use();
	}

	vao->Use();

	if (ebo->GetIndexCount() > 0)
	{
		glDrawElements(renderMode, ebo->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
	}
	else
	{
		glDrawArrays(renderMode, 0, vbo->GetVertexCount());
	}

	vao->Unuse();

	if (texture != nullptr)
	{
		texture->Unuse();
	}

	shader.Unuse();
}

Texture& Renderable::GetTexture() const
{
	return *texture.get();
}
