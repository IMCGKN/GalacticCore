#include <Window/Window.h>
#include "Window.h"

Window::Window(int w, int h, const std::string& title, bool _fullscreen)
	: width(w), height(h)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		Error("Failed to initialize SDL!");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		Warning("SDL Error: " << SDL_GetError());
		Error("Failed to create SDL_Window!");
	}
	glcontext = SDL_GL_CreateContext(window);
	if (glcontext == NULL)
	{
		Warning("SDL Error: " << SDL_GetError());
		Error("Failed to create SDL_GL_Context!");
	}

	SDL_GL_MakeCurrent(window, glcontext);

	if (_fullscreen)
	{
		SDL_DisplayMode dm;
		if (SDL_GetCurrentDisplayMode(0, &dm) == 0)
		{
			SDL_SetWindowSize(window, dm.w, dm.h);
		}
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		Error("Failed to load GLAD library!");
	}

#ifndef NDEBUG
	Log("Version: " << (char*)glGetString(GL_VERSION));
	Log("GPU: " << (char*)glGetString(GL_RENDERER));
#endif

	SDL_GL_GetDrawableSize(window, &width, &height);
	glViewport(0, 0, width, height);

	isOpen = true;

	lastFrame = (double)SDL_GetPerformanceCounter();
}

Window::~Window()
{
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Window::IsOpen() const
{
	return isOpen;
}

void Window::PollEvents()
{
	double newFrame = (double)SDL_GetPerformanceCounter();
	deltaTime = ((newFrame - lastFrame) / (double)SDL_GetPerformanceFrequency());
	lastFrame = newFrame;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isOpen = false;
			break;
		case SDL_KEYUP:
			keys[event.key.keysym.scancode] = KeyState::Up;
			break;
		case SDL_MOUSEBUTTONUP:
			mouseButtons[event.button.button] = KeyState::Up;
			break;
		case SDL_MOUSEWHEEL:
			scrollAmount *= (1.0f - event.wheel.y * 0.1f); // Scales proportionally
			scrollAmount = glm::clamp(scrollAmount, 0.0001f, 1.0f);
			break;
		}
	}
}

void Window::SwapBuffers()
{
	SDL_GL_SwapWindow(window);
}

void Window::UpdateKeys()
{
	for (auto& key : keys)
	{
		if (key.second == KeyState::Up)
			key.second = KeyState::Idle;
	}

	for (auto& mouseButton : mouseButtons)
	{
		if (mouseButton.second == KeyState::Up)
			mouseButton.second = KeyState::Idle;
	}
}

float Window::GetDeltaTime() const
{
	return static_cast<float>(deltaTime);
}

void Window::GetMousePos(float* x, float* y)
{
	int screenX;
	int screenY;
	SDL_GetMouseState(&screenX, &screenY);

	*x = static_cast<float>(screenX);
	*y = static_cast<float>(screenY);
}

void Window::GetMousePosInWorldPos(float* x, float* y, const glm::mat4& projection)
{
	int screenX, screenY;
	SDL_GetMouseState(&screenX, &screenY);

	int width, height;
	SDL_GetWindowSize(window, &width, &height);

	float ndcX = (2.0f * screenX) / width - 1.0f;
	float ndcY = 1.0f - (2.0f * screenY) / height;

	glm::vec4 ndcPos(ndcX, ndcY, 0.0f, 1.0f);

	glm::mat4 invProj = glm::inverse(projection);
	glm::vec4 worldPos = invProj * ndcPos;
	worldPos /= worldPos.w;

	*x = worldPos.x;
	*y = worldPos.y;
}

void Window::GetMouseDelta(float* x, float* y)
{
	int deltaX;
	int deltaY;
	SDL_GetRelativeMouseState(&deltaX, &deltaY);

	*x = static_cast<float>(deltaX);
	*y = static_cast<float>(deltaY);
}

bool Window::CheckKeyUp(SDL_Scancode key)
{
	return keys[key] == Up;
}

bool Window::CheckKeyDown(SDL_Scancode key)
{
	return SDL_GetKeyboardState(NULL)[key];
}

bool Window::CheckMouseButtonUp(uint8_t key)
{
	return mouseButtons[key] == Up;
}

bool Window::CheckMouseButtonDown(uint8_t key)
{
	return SDL_GetMouseState(nullptr, nullptr) == key;
}

int Window::GetWidth() const
{
	return width;
}

int Window::GetHeight() const
{
	return height;
}

float Window::GetScrollAmount() const
{
	return scrollAmount;
}

float Window::GetAspectRatio() const
{
	return static_cast<float>(width) / static_cast<float>(height);
}

void Window::SwitchClose()
{
	isOpen = !isOpen;
}
