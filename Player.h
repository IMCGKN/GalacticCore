#pragma once

#include <Game/GameObject.h>

#include <Game/Bullet.h>

class Player : public GameObject
{
private:
	std::vector<std::unique_ptr<Bullet>> bullets;

	glm::vec2 movement = glm::vec2(0.0f, 0.0f);

	float speed = 0.99f;
	float shootColdown = 0.31f;
	float shootTimer = 0.0f;

	int health = 0;
	int maxHealth = 5;

public:
	Player(float x, float y, float w, float h, float zRot);
	Player(const glm::vec2& pos, const glm::vec2& size, float zRot);
	~Player();

	void Update(Window& window, float boundsLeft, float boundsRight, float boundsTop, float boundsBottom, const std::map<std::string, Mix_Chunk*>& soundEffects) override;
	void Render(Shader& shader, unsigned int renderMode) override;

	int& GetHealth();
	std::vector<std::unique_ptr<Bullet>>& GetBullets();

private:
	void Shoot();
};
