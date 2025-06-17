#pragma once

#include <Game/GameObject.h>

class Bullet : public GameObject
{
private:
	glm::vec2 movement = glm::vec2(0.0f, 0.0f);

	float speed = 65.0f;

	float lifeTime = 0.0f;
	float maxLifeTime = 8.0f;

public:
	Bullet(float x, float y, float w, float h, float zRot);
	Bullet(const glm::vec2& pos, const glm::vec2& size, float zRot);
	~Bullet();

	void Update(Window& window, float boundsLeft, float boundsRight, float boundsTop, float boundsBottom, const std::map<std::string, Mix_Chunk*>& soundEffects) override;
	void Render(Shader& shader, unsigned int renderMode) override;

	void SetMovementX(float x);
	void SetMovementY(float y);

	float& GetLifeTime();
};
