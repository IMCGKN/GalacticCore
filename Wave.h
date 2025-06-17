#pragma once

#include <Game/GameObject.h>
#include <Game/BasicEnemy.h>
#include <Game/ShootingEnemy.h>
#include <Game/Bullet.h>
#include <Game/Healing.h>

#include <Graphics/Shader.h>

#include <Helper.h>

class Wave
{
private:
	std::vector<std::unique_ptr<GameObject>> gameObjects;

	static const int maxHorizontalSize = 6;
	static const int maxVerticalSize = 4;
	int currentHorizontalSize = 0;
	int currentVerticalSize = 0;

	bool waveDone = false;
	int currentWaveIndex = 0;

	int startingDifficulty = 0;

public:
	Wave(int difficulty);
	~Wave();

	void GenerateWave(int difficulty);
	void GenerateHealingWave();

	void Update(Window& window, float boundsLeft, float boundsRight, float boundsTop, float boundsBottom, const std::map<std::string, Mix_Chunk*>& soundEffects, std::vector<std::unique_ptr<Bullet>>& enemyBullets);
	void Render(Shader& shader);

	std::vector<std::unique_ptr<GameObject>>& GetGameObjects();
	bool IsDone() const;
	int GetWaveIndex() const;
};
