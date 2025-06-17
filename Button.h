#pragma once

#include <Helper.h>

#include <Graphics/UI/Text.h>

#include <Window/Window.h>
#include <SDL/SDL_mixer.h>

struct Color
{
	float r;
	float g;
	float b;
	float a;
};

class Button
{ 
private:
	std::unique_ptr<Text> text;
	Color color;

	float w;
	float h;

	float mouseX, mouseY;

	bool wasInteractedWith = false;
	bool previousMouseState = false;

public:
	Button(int vw, int vh, const std::string& string, float x, float y, float scale);
	~Button();

	void Update(Window& window, Mix_Chunk* soundEffect);
	void Render();

	bool WasInteractedWith();
	Color& GetColor();
};
