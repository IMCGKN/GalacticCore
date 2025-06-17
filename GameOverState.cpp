#include "GameOverState.h"

GameOverState::GameOverState(Window* _window)
    : State(_window)
{
	youWereDestroyedText = std::make_unique<Text>(window->GetWidth(), window->GetHeight(), "You were destroyed!", 0.0f, -200.0f, 2.0f);
	finalScoreText = std::make_unique<Text>(window->GetWidth(), window->GetHeight(), "Final score: ", 0.0f, -50.0f, 2.0f);
	restartButton = std::make_unique<Button>(window->GetWidth(), window->GetHeight(), "Restart", 0.0f, 100.0f, 2.0f);
	exitButton = std::make_unique<Button>(window->GetWidth(), window->GetHeight(), "Exit", 0.0f, 200.0f, 2.0f);
}

GameOverState::~GameOverState()
{
}

void GameOverState::Update(const std::map<std::string, Mix_Chunk*>& soundEffects)
{
	restartButton->Update(*window, soundEffects.at("Click"));
	exitButton->Update(*window, soundEffects.at("Click"));
}

void GameOverState::Render()
{
	glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	std::string scoreText = "Final score: " + std::to_string(score);
	finalScoreText->UpdateText(scoreText);

	youWereDestroyedText->Render(1.0f, 1.0f, 1.0f, 1.0f);
	finalScoreText->Render(1.0f, 1.0f, 1.0f, 1.0f);
	restartButton->Render();
	exitButton->Render();

	window->SwapBuffers();
}

bool GameOverState::GetRestartButtonInteractedWith() const
{
    return restartButton->WasInteractedWith();
}

bool GameOverState::GetExitButtonInteractedWith() const
{
    return exitButton->WasInteractedWith();
}

int& GameOverState::GetScore()
{
    return score;
}
