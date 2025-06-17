#pragma once

#include <Window/Window.h>

#include <App/MainGameState.h>
#include <App/MainMenuState.h>
#include <App/OptionsGameState.h>
#include <App/GameOverState.h>

#include <SDL/SDL_mixer.h>

#include <Helper.h>

class App
{
private:
	std::unique_ptr<Window> window;
	std::unique_ptr<MainGameState> mainGameState;
	std::unique_ptr<MainMenuState> mainMenuState;
	std::unique_ptr<OptionsGameState> optionsGameState;
	std::unique_ptr<GameOverState> gameOverState;

	std::map<std::string, Mix_Chunk*> soundEffects;

	Mix_Music *music;

	int currentState = 0;
	int allStates = 0;

	float soundEffectVolume = 25.0f;
	float musicVolume = 65.0f;

public:
	void Run();

private:
	void MainLoop();

	void Update();
	void Render();
};
