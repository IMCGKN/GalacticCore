#include <App/App.h>

#include "resource.h"
#include <Windows.h>

static SDL_RWops* LoadWAVFromResource(int resourceID, const wchar_t* resourceType) {
	HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(resourceID), resourceType);
	if (!hRes) return nullptr;

	HGLOBAL hData = LoadResource(NULL, hRes);
	if (!hData) return nullptr;

	DWORD dataSize = SizeofResource(NULL, hRes);
	void* pData = LockResource(hData);
	if (!pData) return nullptr;

	// Copy to memory buffer SDL can own
	Uint8* buffer = (Uint8*)SDL_malloc(dataSize);
	if (!buffer) return nullptr;

	SDL_memcpy(buffer, pData, dataSize);
	SDL_RWops* rw = SDL_RWFromConstMem(buffer, dataSize);

	// Set up custom close function to free memory when SDL_RWops is closed
	rw->close = [](SDL_RWops* context) -> int {
		SDL_free((void*)context->hidden.mem.base);
		SDL_FreeRW(context);
		return 0;
		};

	return rw;
}

void App::Run()
{
	srand(time(NULL));
	window = std::make_unique<Window>(480, 720, "Galactic Core - IMCG KN", false);

	if (!Mix_Init(MIX_INIT_WAVPACK | MIX_INIT_MP3 | MIX_INIT_OGG))
		Error("Failed to Initialize SDL_mixer!");

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

	SDL_RWops* musRW = LoadWAVFromResource(BACKGROUND, L"WAVE");
	music = Mix_LoadMUS_RW(musRW, 1);

	Mix_VolumeMusic(musicVolume);
	Mix_PlayMusic(music, -1);

	soundEffects["Click"] = Mix_LoadWAV_RW(LoadWAVFromResource(CLICK, L"WAVE"), 1);
	soundEffects["Shoot"] = Mix_LoadWAV_RW(LoadWAVFromResource(SHOOT, L"WAVE"), 1);
	soundEffects["Death"] = Mix_LoadWAV_RW(LoadWAVFromResource(DEATH, L"WAVE"), 1);
	soundEffects["PowerUp"] = Mix_LoadWAV_RW(LoadWAVFromResource(POWERUP, L"WAVE"), 1);
	soundEffects["Click"]->volume = soundEffectVolume;
	soundEffects["Shoot"]->volume = soundEffectVolume;
	soundEffects["Death"]->volume = soundEffectVolume;
	soundEffects["PowerUp"]->volume = soundEffectVolume;

	mainGameState = std::make_unique<MainGameState>(window.get());
	allStates++;
	mainMenuState = std::make_unique<MainMenuState>(window.get());
	allStates++;
	gameOverState = std::make_unique<GameOverState>(window.get());
	allStates++;
	optionsGameState = std::make_unique<OptionsGameState>(window.get(), soundEffectVolume);
	allStates++;

	MainLoop();
}

void App::MainLoop()
{
	while (window->IsOpen())
	{
		Update();

		Render();
	}

	Mix_CloseAudio();
	Mix_Quit();
}

void App::Update()
{
	window->PollEvents();

	if (currentState == 0)
	{
		mainMenuState->Update(soundEffects);

		if (mainMenuState->GetPlayButtonInteractedWith())
		{
			currentState = 2;
		}
		else if (mainMenuState->GetOptionButtonInteractedWith())
		{
			currentState = 1;
		}
		else if (mainMenuState->GetExitButtonInteractedWith())
		{
			window->SwitchClose();
		}
	}
	else if (currentState == 1)
	{
		optionsGameState->Update(soundEffects);
		soundEffectVolume = optionsGameState->GetSoundEffectVolume();
		musicVolume = optionsGameState->GetMusicVolume();
		Mix_VolumeMusic(musicVolume);

		if (optionsGameState->GetExitButtonInteractedWith())
		{
			currentState = 0;
		}
	}
	else if (currentState == 2)
	{
		mainGameState->Update(soundEffects);
		
		if (mainGameState->GetQuitButtonInteractedWith())
		{
			mainGameState->SwitchPaused();
			mainGameState.reset();
			currentState = 0;
			mainGameState = std::make_unique<MainGameState>(window.get());
			srand(time(NULL));
		}

		if (mainGameState->GetGameOver())
		{
			gameOverState->GetScore() = mainGameState->GetScore();
			mainGameState->SwitchPaused();
			mainGameState.reset();
			currentState = 3;
			mainGameState = std::make_unique<MainGameState>(window.get());
			srand(time(NULL));
		}
	}
	else if (currentState == 3)
	{
		gameOverState->Update(soundEffects);

		if (gameOverState->GetExitButtonInteractedWith())
		{
			currentState = 0;
		}
		else if (gameOverState->GetRestartButtonInteractedWith())
		{
			currentState = 2;
		}
	}

	window->UpdateKeys();
}

void App::Render()
{
	if (currentState == 0)
	{
		mainMenuState->Render();
	}
	else if (currentState == 1)
	{
		optionsGameState->Render();
	}
	else if(currentState == 2)
	{
		mainGameState->Render();
	}
	else if (currentState == 3)
	{
		gameOverState->Render();
	}
}
