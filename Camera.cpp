#include "Camera.h"

Camera::Camera(float camSpeed, Window* _window)
{
    window = _window;
    cameraSpeed = camSpeed;
}

Camera::~Camera()
{
}

void Camera::Update()
{
    /*movement = glm::vec2(0.0f, 0.0f);
    if (window->CheckKeyDown(SDL_SCANCODE_W))
        movement.y += 1.0f;
    if (window->CheckKeyDown(SDL_SCANCODE_S))
        movement.y -= 1.0f;
    if (window->CheckKeyDown(SDL_SCANCODE_A))
        movement.x -= 1.0f;
    if (window->CheckKeyDown(SDL_SCANCODE_D))
        movement.x += 1.0f;

    if (glm::length(movement) > 0.0f)
        movement = glm::normalize(movement);

    cameraPos += movement * cameraSpeed * window->GetDeltaTime();*/
}

glm::mat4 Camera::GetViewMatrix() const
{
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, -glm::vec3(cameraPos.x, cameraPos.y, 0.0f));
    return view;
}