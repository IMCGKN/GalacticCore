#pragma once

#include <App/State.h>

#include <Graphics/UI/Text.h>
#include <Graphics/UI/Button.h>

class MainMenuState : public State
{
private:
	std::unique_ptr<Button> playButton;
	std::unique_ptr<Button> optionsButton;
	std::unique_ptr<Button> exitButton;
	std::unique_ptr<Text> mainText;
	std::unique_ptr<Text> imcgknText;

public:
	MainMenuState(Window* _window);
	~MainMenuState();

	void Update(const std::map<std::string, Mix_Chunk*>& soundEffects) override;
	void Render() override;

	bool GetPlayButtonInteractedWith() const;
	bool GetOptionButtonInteractedWith() const;
	bool GetExitButtonInteractedWith() const;
};
