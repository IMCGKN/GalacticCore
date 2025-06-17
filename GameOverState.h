#pragma once

#include <App/State.h>

#include <Graphics/UI/Text.h>
#include <Graphics/UI/Button.h>

class GameOverState : public State
{
private:
	std::unique_ptr<Button> restartButton;
	std::unique_ptr<Button> exitButton;
	std::unique_ptr<Text> youWereDestroyedText;
	std::unique_ptr<Text> finalScoreText;

	int score = 0;

public:
	GameOverState(Window* _window);
	~GameOverState();

	void Update(const std::map<std::string, Mix_Chunk*>& soundEffects) override;
	void Render() override;

	bool GetRestartButtonInteractedWith() const;
	bool GetExitButtonInteractedWith() const;

	int& GetScore();
};
