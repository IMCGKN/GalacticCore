#pragma once

#include <Helper.h>

#include <Game/AABB.h>
#include <Graphics/Shader.h>
#include <Graphics/Renderable.h>

#include <SDL/SDL_mixer.h>

struct Transform
{
	glm::vec2 Position;
	glm::vec2 Size;
	float zRotation;
};

enum GameObjectType
{
	Enemy,
	EnemyShooter,
	HealingObj
};

class GameObject
{
protected:
	Transform transform;

	std::unique_ptr<Renderable> renderable;
	std::unique_ptr<AABB> aabb;

	GameObjectType gameObjectType = GameObjectType::Enemy;

	float shootColdown = 2.3f;
	float shootTimer = 0.0f;

public:
	GameObject(float x, float y, float w, float h, float zRot);
	GameObject(const glm::vec2& pos, const glm::vec2& size, float zRot);
	~GameObject();

	void ConstructRenderableAndTexture(const std::string& texturePath, unsigned int textureFormat);
	void ConstructRenderableAndTexture(int resource, unsigned int textureFormat);
	void ConstructAABB();

	virtual void Update(Window& window, float boundsLeft, float boundsRight, float boundsTop, float boundsBottom, const std::map<std::string, Mix_Chunk*>& soundEffects) = 0;
	virtual void Render(Shader& shader, unsigned int renderMode) = 0;

	void ResetShootTimer();
	
	Transform& GetTransform();
	AABB& GetAABB();
	GameObjectType& GetType();
	bool CanShoot() const;
	float& GetShootColdown();
};
