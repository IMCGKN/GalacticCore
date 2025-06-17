#include "OptionsGameState.h"

OptionsGameState::OptionsGameState(Window* _window, float _globalVolume)
    : State(_window)
{
	optionsText = std::make_unique<Text>(window->GetWidth(), window->GetHeight(), "Options", 0.0f, -300.0f, 2.0f);
	exitButton = std::make_unique<Button>(window->GetWidth(), window->GetHeight(), "Exit", 0.0f, 300.0f, 2.0f);
	upSoundEffectVolumeButton = std::make_unique<Button>(window->GetWidth(), window->GetHeight(), "INC", 0.0f, -190.0f, 2.0f);
	soundEffectVolumeText = std::make_unique<Text>(window->GetWidth(), window->GetHeight(), "SOUND EFFECTS VOLUME: 25", 0.0f, -140.0f, 2.0f);
	downSoundEffectVolumeButton = std::make_unique<Button>(window->GetWidth(), window->GetHeight(), "DEC", 0.0f, -90.0f, 2.0f);
	upMusicVolumeButton = std::make_unique<Button>(window->GetWidth(), window->GetHeight(), "INC", 0.0f, 70.0f, 2.0f);
	musicVolumeText = std::make_unique<Text>(window->GetWidth(), window->GetHeight(), "MUSIC VOLUME: 65", 0.0f, 120.0f, 2.0f);
	downMusicVolumeButton = std::make_unique<Button>(window->GetWidth(), window->GetHeight(), "DEC", 0.0f, 170.0f, 2.0f);
}

OptionsGameState::~OptionsGameState()
{
}

void OptionsGameState::Update(const std::map<std::string, Mix_Chunk*>& soundEffects)
{
	exitButton->Update(*window, soundEffects.at("Click"));
	downSoundEffectVolumeButton->Update(*window, soundEffects.at("Click"));
	upSoundEffectVolumeButton->Update(*window, soundEffects.at("Click"));
	downMusicVolumeButton->Update(*window, soundEffects.at("Click"));
	upMusicVolumeButton->Update(*window, soundEffects.at("Click"));

	if (downSoundEffectVolumeButton->WasInteractedWith())
	{
		soundEffectVolume -= 3.0f;
	}
	else if (upSoundEffectVolumeButton->WasInteractedWith())
	{
		soundEffectVolume += 3.0f;
	}

	if (downMusicVolumeButton->WasInteractedWith())
	{
		musicVolume -= 3.0f;
	}
	else if (upMusicVolumeButton->WasInteractedWith())
	{
		musicVolume += 3.0f;
	}

	soundEffectVolume = glm::clamp(soundEffectVolume, 0.0f, 42.0f);
	std::string volumeString = "SOUND EFFECTS VOLUME: " + std::to_string((int)soundEffectVolume);
	soundEffectVolumeText->UpdateText(volumeString);
	for (auto& soundEffect : soundEffects)
		soundEffect.second->volume = soundEffectVolume;

	musicVolume = glm::clamp(musicVolume, 0.0f, 105.0f);
	volumeString = "MUSIC VOLUME: " + std::to_string((int)musicVolume);
	musicVolumeText->UpdateText(volumeString);
}

void OptionsGameState::Render()
{
	glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	optionsText->Render(1.0f, 1.0f, 1.0f, 1.0f);
	exitButton->Render();
	upSoundEffectVolumeButton->Render();
	downSoundEffectVolumeButton->Render();
	soundEffectVolumeText->Render(1.0f, 1.0f, 1.0f, 1.0f);
	upMusicVolumeButton->Render();
	downMusicVolumeButton->Render();
	musicVolumeText->Render(1.0f, 1.0f, 1.0f, 1.0f);

	window->SwapBuffers();
}

bool OptionsGameState::GetExitButtonInteractedWith() const
{
    return exitButton->WasInteractedWith();
}

float& OptionsGameState::GetSoundEffectVolume()
{
	return soundEffectVolume;
}

float& OptionsGameState::GetMusicVolume()
{
	return musicVolume;
}
