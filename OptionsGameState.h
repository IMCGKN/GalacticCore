#pragma once

#include <App/State.h>

#include <Graphics/UI/Text.h>
#include <Graphics/UI/Button.h>

#include <SDL/SDL_mixer.h>

class OptionsGameState : public State
{
private:
	std::unique_ptr<Button> exitButton;
	std::unique_ptr<Button> upMusicVolumeButton;
	std::unique_ptr<Button> upSoundEffectVolumeButton;
	std::unique_ptr<Button> downMusicVolumeButton;
	std::unique_ptr<Button> downSoundEffectVolumeButton;
	std::unique_ptr<Text> optionsText;
	std::unique_ptr<Text> musicVolumeText;
	std::unique_ptr<Text> soundEffectVolumeText;

	float soundEffectVolume = 25.0f;
	float musicVolume = 65.0f;

public:
	OptionsGameState(Window* _window, float _globalVolume);
	~OptionsGameState();

	void Update(const std::map<std::string, Mix_Chunk*>& soundEffects) override;
	void Render() override;

	bool GetExitButtonInteractedWith() const;
	float& GetSoundEffectVolume();
	float& GetMusicVolume();
};
