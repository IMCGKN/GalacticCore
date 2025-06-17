#pragma once

#include <App/State.h>

#include <Game/Player.h>
#include <Game/BasicEnemy.h>
#include <Game/AABB.h>
#include <Game/Wave.h>
#include <Graphics/Camera.h>

#include <Graphics/UI/Text.h>
#include <Graphics/UI/Button.h>

class MainGameState : public State
{
private:
	std::vector<std::unique_ptr<Bullet>> enemyBullets;

	std::unique_ptr<Player> player;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<Wave> wave;

	std::unique_ptr<Button> quitButton;
	std::unique_ptr<Text> pauseText;
	std::unique_ptr<Text> waveIndexText;
	std::unique_ptr<Text> healthText;
	std::unique_ptr<Text> maxHealthText;

	std::unique_ptr<Text> scoreText;

	bool paused = false;

	int score = 0;

	float targetHeight;
	float targetWidth;

	glm::vec2 mousePos;

	bool gameOver = false;

public:
	MainGameState(Window* _window);
	~MainGameState();

	void Update(const std::map<std::string, Mix_Chunk*>& soundEffects) override;
	void Render() override;

	bool GetQuitButtonInteractedWith() const;

	glm::mat4 GetProjectionMatrix();

	void SwitchPaused();

	int& GetScore();
	bool GetGameOver();
};
