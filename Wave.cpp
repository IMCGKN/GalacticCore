#include "Wave.h"

#include "resource1.h"

Wave::Wave(int difficulty)
{
    startingDifficulty = difficulty;
    GenerateWave(startingDifficulty);
}

Wave::~Wave()
{
}

void Wave::GenerateWave(int difficulty)
{
    const int maxDifficulty = 10;
    startingDifficulty = glm::clamp(difficulty, 1, maxDifficulty);

    currentHorizontalSize = (maxHorizontalSize * difficulty) / maxDifficulty;
    if (currentHorizontalSize < 1) currentHorizontalSize = 1;

    currentVerticalSize = (maxVerticalSize * difficulty) / maxDifficulty;
    if (currentVerticalSize < 1) currentVerticalSize = 1;

    for (int y = 0; y < currentVerticalSize; y++)
    {
        for (int x = 0; x < currentHorizontalSize; x++)
        {
            float enemyX = x * 16 - ((currentHorizontalSize * 16) / 2.0f);
            float enemyY = (y * 16 - ((currentVerticalSize * 16) / 2.0f)) + 120;
            int enemyChance = rand() % 4;

            if (enemyChance < 3)
            {
                std::unique_ptr<BasicEnemy> basicEnemy = std::make_unique<BasicEnemy>(enemyX, enemyY, 1.0f, 1.0f, 0.0f);
                basicEnemy->ConstructRenderableAndTexture(ENEMY, GL_RGBA);

                gameObjects.push_back(std::move(basicEnemy));
            }
            else if (enemyChance == 3)
            {
                std::unique_ptr<ShootingEnemy> shootingEnemy = std::make_unique<ShootingEnemy>(enemyX, enemyY, 1.0f, 1.0f, 0.0f);
                shootingEnemy->ConstructRenderableAndTexture(ENEMYSHOOTER, GL_RGBA);
                float cooldown = ((float)rand() / (float)(RAND_MAX / 1.8f)) + 1.5f;
                shootingEnemy->GetShootColdown() = cooldown;

                gameObjects.push_back(std::move(shootingEnemy));
            }
        }
    }

    startingDifficulty++;
    currentWaveIndex++;

    waveDone = false;
}

void Wave::GenerateHealingWave()
{
    for (int y = 0; y < 1; y++)
    {
        currentHorizontalSize = 1;
        currentVerticalSize = 1;
        float healingX = ((rand() % 12) - 6) * 4 - 4;
        Log(healingX);
        float healingY = (y * 16 - ((currentVerticalSize * 16) / 2.0f)) + 120;
        std::unique_ptr<Healing> healing = std::make_unique<Healing>(healingX, healingY, 1.0f, 1.0f, 0.0f);
        healing->ConstructRenderableAndTexture(HEALING, GL_RGBA);

        gameObjects.push_back(std::move(healing));
    }

    startingDifficulty++;
    currentWaveIndex++;

    waveDone = false;
}

void Wave::Update(Window& window, float boundsLeft, float boundsRight, float boundsTop, float boundsBottom, const std::map<std::string, Mix_Chunk*>& soundEffects, std::vector<std::unique_ptr<Bullet>>& enemyBullets)
{
    for (auto it = gameObjects.begin(); it != gameObjects.end(); )
    {
        (*it)->Update(window, boundsLeft, boundsRight, boundsTop, boundsBottom, soundEffects);

        if ((*it)->GetType() == GameObjectType::EnemyShooter && (*it)->CanShoot())
        {
            glm::vec2 bulletPos;
            bulletPos.x = (*it)->GetTransform().Position.x + ((*it)->GetTransform().Size.x / 2.0f) - 0.5f;
            bulletPos.y = (*it)->GetTransform().Position.y;
            std::unique_ptr<Bullet> enemyBullet = std::make_unique<Bullet>(bulletPos, glm::vec2(0.3f, 0.3f), 0.0f);
            enemyBullet->ConstructRenderableAndTexture(BULLET, GL_RGBA);
            enemyBullet->SetMovementY(1.0f);

            (*it)->ResetShootTimer();

            enemyBullets.push_back(std::move(enemyBullet));
        }

        if ((*it)->GetAABB().IsOffScreenOnlyBottom(boundsTop))
        {
            it = gameObjects.erase(it);
        }
        else
        {
            it++;
        }
    }

    if (gameObjects.size() == 0)
    {
        waveDone = true;

        if (currentWaveIndex % 5 == 0)
            GenerateHealingWave();
        else
            GenerateWave(startingDifficulty);
    }
}

void Wave::Render(Shader& shader)
{
    for (const auto& enemy : gameObjects)
    {
        enemy->Render(shader, GL_TRIANGLES);
    }
}

std::vector<std::unique_ptr<GameObject>>& Wave::GetGameObjects()
{
    return gameObjects;
}

bool Wave::IsDone() const
{
    return waveDone;
}

int Wave::GetWaveIndex() const
{
    return currentWaveIndex;
}
