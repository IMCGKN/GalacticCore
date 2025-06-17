#pragma once

#include <Window/Window.h>

#include <Helper.h>

class Camera
{
private:
	glm::vec2 cameraPos = glm::vec2(0.0f, 0.0f);
	glm::vec2 movement = glm::vec2(0.0f, 0.0f);

	float cameraSpeed = 55.0f;

	Window* window;

public:
	Camera(float camSpeed, Window* _window);
	~Camera();

	void Update();

	glm::mat4 GetViewMatrix() const;
};
