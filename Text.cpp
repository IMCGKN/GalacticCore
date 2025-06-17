#include "Text.h"

Text::Text(int viewportWidth, int viewportHeight, const std::string& string, float _x, float _y, float _scale)
{
	if (!gltInit())
		Error("Failed to Initialize GLText Library!");

	gltText = gltCreateText();
	gltSetText(gltText, string.c_str());

	x = _x + viewportWidth / 2.0f;
	y = _y + viewportHeight / 2.0f;
	scale = _scale;
}

Text::~Text()
{
	gltDeleteText(gltText);
}

void Text::UpdateText(const std::string& string)
{
	gltSetText(gltText, string.c_str());
}

void Text::Render(float r, float g, float b, float a)
{
	gltBeginDraw();

	gltColor(r, g, b, a);

	gltDrawText2DAligned(gltText, x, y, scale, GLT_CENTER, GLT_CENTER);

	gltEndDraw();
}
