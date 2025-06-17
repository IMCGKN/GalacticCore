#pragma once

#include <Helper.h>

#include <glad/glad.h>
#define GLT_IMPLEMENTATION
#include <gltext.h>

#include <Window/Window.h>

class Text
{
public:
	GLTtext* gltText;
	float x;
	float y;
	float scale;

public:
	Text(int viewportWidth, int viewportHeight, const std::string& string, float _x, float _y, float _scale);
	~Text();

	void UpdateText(const std::string& string);

	void Render(float r, float g, float b, float a);
};
