#pragma once

#include <Game/GameObject.h>

class ShootingEnemy : public GameObject
{
private:
	glm::vec2 movement = glm::vec2(0.0f, 0.0f);

	float speed = 21.0f;

public:
	ShootingEnemy(float x, float y, float w, float h, float zRot);
	ShootingEnemy(const glm::vec2& pos, const glm::vec2& size, float zRot);
	~ShootingEnemy();

	void Update(Window& window, float boundsLeft, float boundsRight, float boundsTop, float boundsBottom, const std::map<std::string, Mix_Chunk*>& soundEffects) override;
	void Render(Shader& shader, unsigned int renderMode) override;
};
