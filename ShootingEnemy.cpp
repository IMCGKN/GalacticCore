#include "ShootingEnemy.h"

ShootingEnemy::ShootingEnemy(float x, float y, float w, float h, float zRot)
    : GameObject(x, y, w, h, zRot)
{
    ConstructAABB();
    movement.y = 1.0f;
    gameObjectType = EnemyShooter;
}

ShootingEnemy::ShootingEnemy(const glm::vec2& pos, const glm::vec2& size, float zRot)
    : GameObject(pos, size, zRot)
{
    ConstructAABB();
    movement.y = 1.0f;
    gameObjectType = EnemyShooter;
}

ShootingEnemy::~ShootingEnemy()
{
}

void ShootingEnemy::Update(Window& window, float boundsLeft, float boundsRight, float boundsTop, float boundsBottom, const std::map<std::string, Mix_Chunk*>& soundEffects)
{
    shootTimer -= window.GetDeltaTime();

    transform.Position -= movement * speed * window.GetDeltaTime();

    aabb->GetLeft() = transform.Position.x;
    aabb->GetRight() = transform.Position.x + transform.Size.x;
    aabb->GetBottom() = transform.Position.y;
    aabb->GetTop() = transform.Position.y + transform.Size.y;
}

void ShootingEnemy::Render(Shader& shader, unsigned int renderMode)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(transform.Position.x, transform.Position.y, 0.0f));
    model = glm::scale(model, glm::vec3(transform.Size.x, transform.Size.y, 0.0f));
    if (transform.zRotation != 0.0f)
        model = glm::rotate(model, glm::radians(transform.zRotation), glm::vec3(0.0f, 0.0f, 1.0f));

    renderable->Render(shader, renderMode, model);
}