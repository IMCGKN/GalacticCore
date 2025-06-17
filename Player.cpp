#include "Player.h"

#include "resource1.h"

Player::Player(float x, float y, float w, float h, float zRot)
	: GameObject(x, y, w, h, zRot)
{
    ConstructAABB();
    health = maxHealth;
}

Player::Player(const glm::vec2& pos, const glm::vec2& size, float zRot)
	: GameObject(pos, size, zRot)
{
    ConstructAABB();
    health = maxHealth;
}

Player::~Player()
{
}

void Player::Update(Window& window, float boundsLeft, float boundsRight, float boundsTop, float boundsBottom, const std::map<std::string, Mix_Chunk*>& soundEffects)
{
    shootTimer -= window.GetDeltaTime();

    glm::vec2 acceleration = glm::vec2(0.0f, 0.0f);

    if (window.CheckKeyDown(SDL_SCANCODE_W))
        acceleration.y += speed;
    if (window.CheckKeyDown(SDL_SCANCODE_S))
        acceleration.y -= speed;
    if (window.CheckKeyDown(SDL_SCANCODE_A))
        acceleration.x -= speed;
    if (window.CheckKeyDown(SDL_SCANCODE_D))
        acceleration.x += speed;

    if (glm::length(acceleration) > 0.0f)
        acceleration = glm::normalize(acceleration) * speed;

    movement += acceleration * window.GetDeltaTime();
   
    transform.Position += movement;

    movement = 0.99f * movement;

    transform.Position.x = glm::clamp(transform.Position.x, boundsLeft, boundsRight - transform.Size.x);
    transform.Position.y = glm::clamp(transform.Position.y, boundsTop, boundsBottom - transform.Size.x);

    aabb->GetLeft() = transform.Position.x;
    aabb->GetRight() = transform.Position.x + transform.Size.x;
    aabb->GetBottom() = transform.Position.y;
    aabb->GetTop() = transform.Position.y + transform.Size.y;

    if ((window.CheckMouseButtonUp(SDL_BUTTON_LEFT) || window.CheckKeyUp(SDL_SCANCODE_SPACE)) && shootTimer <= 0.0f)
    {
        Mix_PlayChannel(-1, soundEffects.at("Shoot"), 0);
        Shoot();
        shootTimer = shootColdown;
    }

    health = glm::clamp(health, 0, maxHealth);
}

void Player::Render(Shader& shader, unsigned int renderMode)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(transform.Position.x, transform.Position.y, 0.0f));
    model = glm::scale(model, glm::vec3(transform.Size.x, transform.Size.y, 0.0f));
    if (transform.zRotation != 0.0f)
        model = glm::rotate(model, glm::radians(transform.zRotation), glm::vec3(0.0f, 0.0f, 1.0f));

    renderable->Render(shader, renderMode, model);
}

int& Player::GetHealth()
{
    return health;
}

std::vector<std::unique_ptr<Bullet>>& Player::GetBullets()
{
    return bullets;
}

void Player::Shoot()
{
    glm::vec2 bulletPos;
    bulletPos.x = transform.Position.x + (transform.Size.x / 2.0f) - 0.5f;
    bulletPos.y = transform.Position.y + transform.Size.y;
    std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(bulletPos, glm::vec2(0.3f, 0.3f), 0.0f);
    bullet->ConstructRenderableAndTexture(BULLET, GL_RGBA);

    bullets.push_back(std::move(bullet));
}
