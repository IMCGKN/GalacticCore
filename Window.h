#pragma once

#include <SDL/SDL.h>
#include <glad/glad.h>

#include <Helper.h>

enum KeyState
{
	Idle, // only true for one frame
	Up // only true for one frame after release
};

class Window
{
private:
	SDL_Window* window = nullptr;
	SDL_GLContext glcontext;
	SDL_Event event;

	int width = 50, height = 20;

	bool isOpen = false;

	double deltaTime = 0.0;
	double lastFrame = 0.0;

	float scrollAmount = 1.0f;

	std::unordered_map<SDL_Scancode, KeyState> keys;
	std::unordered_map<uint8_t, KeyState> mouseButtons;

public:
	Window(int w, int h, const std::string& title, bool _fullscreen);
	~Window();

	bool IsOpen() const;

	/// <summary>
	/// Call it on the start of the frame
	/// ! ! ! This function also calculates deltaTime ! ! !
	/// </summary>
	void PollEvents();
	/// <summary>
	/// Call it on the end of Render Function
	/// </summary>
	void SwapBuffers();
	/// <summary>
	/// Call it at the end of the frame
	/// </summary>
	void UpdateKeys();

	float GetDeltaTime() const;
	void GetMousePos(float* x, float* y);
	void GetMousePosInWorldPos(float* x, float* y, const glm::mat4& projection);
	void GetMouseDelta(float* x, float* y);
	bool CheckKeyUp(SDL_Scancode key);
	bool CheckKeyDown(SDL_Scancode key);
	bool CheckMouseButtonUp(uint8_t key);
	bool CheckMouseButtonDown(uint8_t key);
	int GetWidth() const;
	int GetHeight() const;
	float GetScrollAmount() const;
	float GetAspectRatio() const;

	void SwitchClose();
};
