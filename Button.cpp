#include "Button.h"

Button::Button(int vw, int vh, const std::string& string, float x, float y, float scale)
{
    if (!gltInit())
        Error("Failed to Initialize GLText Library!");

    text = std::make_unique<Text>(vw, vh, string, x, y, scale);

    w = gltGetTextWidth(text->gltText, text->scale);
    h = gltGetTextHeight(text->gltText, text->scale);
}

Button::~Button()
{
}

void Button::Update(Window& window, Mix_Chunk* soundEffect)
{
    window.GetMousePos(&mouseX, &mouseY);
    
    float left   = text->x - w / 2.0f;
    float right  = text->x + w / 2.0f;
    float top    = text->y + h / 2.0f;
    float bottom = text->y - h / 2.0f;

    if(mouseX >= left && mouseX <= right && mouseY >= bottom && mouseY <= top)
    {
        color.r = 1.0f;
        color.g = 0.0f;
        color.b = 0.0f;
        color.a = 1.0f;

        if (window.CheckMouseButtonDown(SDL_BUTTON_LEFT))
        {
            color.r = 0.8f;
            color.g = 0.2f;
            color.b = 0.0f;
            color.a = 0.8f;
        }

        if (window.CheckMouseButtonUp(SDL_BUTTON_LEFT))
        {
            wasInteractedWith = true;
            Mix_PlayChannel(-1, soundEffect, 0);
        }
    }
    else
    {
        color.r = 1.0f;
        color.g = 1.0f;
        color.b = 1.0f;
        color.a = 1.0f;
    }
}

void Button::Render()
{
    text->Render(color.r, color.g, color.b, color.a);
}

bool Button::WasInteractedWith()
{
    if (wasInteractedWith)
    {
        wasInteractedWith = false;
        return true;
    }
    return false;
}

Color& Button::GetColor()
{
    return color;
}
