#include "GameObject.h"

GameObject::GameObject(float x, float y, float w, float h, float zRot)
{
	transform.Position = glm::vec2(x, y);
	transform.Size = glm::vec2(w, h);
	transform.zRotation = zRot;
}

GameObject::GameObject(const glm::vec2& pos, const glm::vec2& size, float zRot)
{
	transform.Position = pos;
	transform.Size = size;
	transform.zRotation = zRot;
}

GameObject::~GameObject()
{
}

void GameObject::ConstructRenderableAndTexture(const std::string& texturePath, unsigned int textureFormat)
{
	std::vector<Vertex> vertices = {
		{ { 0.0f, 0.0f }, { 0.0f, 0.0f } },
		{ { 1.0f, 0.0f }, { 1.0f, 0.0f } },
		{ { 1.0f, 1.0f }, { 1.0f, 1.0f } },
		{ { 0.0f, 1.0f }, { 0.0f, 1.0f } }
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		0, 2, 3
	};
	renderable = std::make_unique<Renderable>(vertices, GL_STATIC_DRAW, indices, GL_STATIC_DRAW);
	renderable->ConstructTexture(texturePath, GL_TEXTURE_2D, textureFormat, GL_NEAREST, GL_NEAREST);

	transform.Size.x = renderable->GetTexture().GetWidth();
	transform.Size.y = renderable->GetTexture().GetHeight();
}

void GameObject::ConstructRenderableAndTexture(int resource, unsigned int textureFormat)
{
	std::vector<Vertex> vertices = {
		{ { 0.0f, 0.0f }, { 0.0f, 0.0f } },
		{ { 1.0f, 0.0f }, { 1.0f, 0.0f } },
		{ { 1.0f, 1.0f }, { 1.0f, 1.0f } },
		{ { 0.0f, 1.0f }, { 0.0f, 1.0f } }
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		0, 2, 3
	};
	renderable = std::make_unique<Renderable>(vertices, GL_STATIC_DRAW, indices, GL_STATIC_DRAW);
	renderable->ConstructTexture(resource, GL_TEXTURE_2D, textureFormat, GL_NEAREST, GL_NEAREST);

	transform.Size.x = renderable->GetTexture().GetWidth();
	transform.Size.y = renderable->GetTexture().GetHeight();
}

void GameObject::ConstructAABB()
{
	aabb = std::make_unique<AABB>(transform.Position, transform.Size);
}

void GameObject::ResetShootTimer()
{
	shootTimer = shootColdown;
}

Transform& GameObject::GetTransform()
{
	return transform;
}

AABB& GameObject::GetAABB()
{
	return *aabb.get();
}

GameObjectType& GameObject::GetType()
{
	return gameObjectType;
}

bool GameObject::CanShoot() const
{
	return shootTimer <= 0.0f;
}

float& GameObject::GetShootColdown()
{
	return shootColdown;
}
