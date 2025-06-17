#include "Bullet.h"

Bullet::Bullet(float x, float y, float w, float h, float zRot)
	: GameObject(x, y, w, h, zRot)
{
    ConstructAABB();
    movement.y = -1.0f;
    lifeTime = maxLifeTime;
}

Bullet::Bullet(const glm::vec2& pos, const glm::vec2& size, float zRot)
	: GameObject(pos, size, zRot)
{
    ConstructAABB();
    movement.y = -1.0f;
    lifeTime = maxLifeTime;
}

Bullet::~Bullet()
{
}

void Bullet::Update(Window& window, float boundsLeft, float boundsRight, float boundsTop, float boundsBottom, const std::map<std::string, Mix_Chunk*>& soundEffects)
{
    transform.Position -= movement * speed * window.GetDeltaTime();

    aabb->GetLeft() = transform.Position.x;
    aabb->GetRight() = transform.Position.x + transform.Size.x;
    aabb->GetBottom() = transform.Position.y;
    aabb->GetTop() = transform.Position.y + transform.Size.y;

    lifeTime -= window.GetDeltaTime();
}

void Bullet::Render(Shader& shader, unsigned int renderMode)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(transform.Position.x, transform.Position.y, 0.0f));
    model = glm::scale(model, glm::vec3(transform.Size.x, transform.Size.y, 0.0f));
    if (transform.zRotation != 0.0f)
        model = glm::rotate(model, glm::radians(transform.zRotation), glm::vec3(0.0f, 0.0f, 1.0f));

    renderable->Render(shader, renderMode, model);
}

void Bullet::SetMovementX(float x)
{
    movement.x = x;
}

void Bullet::SetMovementY(float y)
{
    movement.y = y;
}

float& Bullet::GetLifeTime()
{
    return lifeTime;
}
