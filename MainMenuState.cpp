#include <App/MainMenuState.h>

MainMenuState::MainMenuState(Window* _window)
	: State(_window)
{
	mainText = std::make_unique<Text>(window->GetWidth(), window->GetHeight(), "Galactic Core", 0.0f, -200.0f, 2.1f);
	imcgknText = std::make_unique<Text>(window->GetWidth(), window->GetHeight(), "Made by: IMCG KN", 0.0f, 300.0f, 2.1f);
	playButton = std::make_unique<Button>(window->GetWidth(), window->GetHeight(), "Play", 0.0f, 0.0f, 2.0f);
	optionsButton = std::make_unique<Button>(window->GetWidth(), window->GetHeight(), "Options", 0.0f, 100.0f, 2.0f);
	exitButton = std::make_unique<Button>(window->GetWidth(), window->GetHeight(), "Exit", 0.0f, 200.0f, 2.0f);
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::Update(const std::map<std::string, Mix_Chunk*>& soundEffects)
{
	playButton->Update(*window, soundEffects.at("Click"));
	optionsButton->Update(*window, soundEffects.at("Click"));
	exitButton->Update(*window, soundEffects.at("Click"));
}

void MainMenuState::Render()
{
	glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	mainText->Render(1.0f, 1.0f, 1.0f, 1.0f);
	imcgknText->Render(0.0f, 0.0f, 1.0f, 1.0f);
	playButton->Render();
	optionsButton->Render();
	exitButton->Render();

	window->SwapBuffers();
}

bool MainMenuState::GetPlayButtonInteractedWith() const
{
	return playButton->WasInteractedWith();
}

bool MainMenuState::GetOptionButtonInteractedWith() const
{
	return optionsButton->WasInteractedWith();
}

bool MainMenuState::GetExitButtonInteractedWith() const
{
	return exitButton->WasInteractedWith();
}
