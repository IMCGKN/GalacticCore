#include <App/MainGameState.h>

#include "resource1.h"

const std::string vShaderContent = "#version 450 core\n"
"layout (location = 0) in vec2 aPos;\n"
"layout (location = 1) in vec2 aUV;\n"
"out vec2 UV;\n"
"uniform mat4 Model;\n"
"uniform mat4 View;\n"
"uniform mat4 Projection;\n"
"void main()\n"
"{\n"
"	gl_Position = Projection * View * Model * vec4(aPos, 0.0, 1.0);\n"
"	UV = aUV;\n"
"}";

const std::string fShaderContent = "#version 450 core\n"
"layout(location = 0) out vec4 FragColor;\n"
"in vec2 UV;\n"
"in vec3 Normal;\n"
"uniform sampler2D tex0;\n"
"void main()\n"
"{\n"
"	FragColor = texture(tex0, UV);\n"
"}";

MainGameState::MainGameState(Window* _window)
	: State(_window)
{
	ConstructShader(vShaderContent, fShaderContent, false);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glCullFace(GL_BACK);

	glm::mat4 projection = GetProjectionMatrix();

	mainShader->Use();
	mainShader->SetMat4("Projection", projection);

	player = std::make_unique<Player>(-5.0f, -80.0f, 1.0f, 1.0f, 0.0f);
	player->ConstructRenderableAndTexture(PLAYER, GL_RGBA);
	camera = std::make_unique<Camera>(2.0f, window);

	quitButton = std::make_unique<Button>(window->GetWidth(), window->GetHeight(), "Quit", 0.0f, 150.0f, 2.0f);
	pauseText = std::make_unique<Text>(window->GetWidth(), window->GetHeight(), "PAUSED", 0.0f, -200.0f, 2.5f);
	healthText = std::make_unique<Text>(window->GetWidth(), window->GetHeight(), "5", 103.0f,  342.0f, 1.69f);
	scoreText = std::make_unique<Text>(window->GetWidth(), window->GetHeight(), "Score: 0", 0.0f,  342.0f, 1.69f);
	maxHealthText = std::make_unique<Text>(window->GetWidth(), window->GetHeight(), "/5 health", 170.0f,  342.0f, 1.5f);
	waveIndexText = std::make_unique<Text>(window->GetWidth(), window->GetHeight(), "Current Wave:", 140.0f,-342.0f, 1.2f);

	wave = std::make_unique<Wave>(1);
}

MainGameState::~MainGameState()
{
}

void MainGameState::Update(const std::map<std::string, Mix_Chunk*>& soundEffects)
{
	if (!paused)
	{
		window->GetMousePosInWorldPos(&mousePos.x, &mousePos.y, GetProjectionMatrix());
		if (window->CheckKeyUp(SDL_SCANCODE_ESCAPE))
			SwitchPaused();
		if (window->CheckKeyUp(SDL_SCANCODE_TAB))
			player->GetHealth() -= 1;
		camera->Update();
		player->Update(*window, -(targetWidth / 2.0f), (targetWidth / 2.0f), -(targetHeight / 2.0f), (targetHeight / 2.0f), soundEffects);
		wave->Update(*window, -(targetWidth / 2.0f), (targetWidth / 2.0f), -(targetHeight / 2.0f), (targetHeight / 2.0f), soundEffects, enemyBullets);

		auto& bullets = player->GetBullets();
		auto& enemies = wave->GetGameObjects();

		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i]->Update(*window, -(targetWidth / 2.0f), (targetWidth / 2.0f), -(targetHeight / 2.0f), (targetHeight / 2.0f), soundEffects);

			if (bullets[i]->GetAABB().IsOffScreen(-(targetWidth / 2.0f), (targetWidth / 2.0f), -(targetHeight / 2.0f), (targetHeight / 2.0f)))
			{
				bullets.erase(bullets.begin() + i);
				i--;
				continue;
			}

			for (int e = 0; e < enemies.size(); e++)
			{
				if (enemies[e]->GetAABB().Intersects(bullets[i]->GetAABB()) && (enemies[e]->GetType() == GameObjectType::Enemy || enemies[e]->GetType() == GameObjectType::EnemyShooter))
				{
					enemies.erase(enemies.begin() + e);
					bullets.erase(bullets.begin() + i);
					Mix_PlayChannel(-1, soundEffects.at("Death"), 0);
					i--;
					score++;
					break;
				}
			}
		}

		for (int e = 0; e < enemies.size(); e++)
		{
			if (enemies[e]->GetAABB().Intersects(player->GetAABB()))
			{
				if (enemies[e]->GetType() == GameObjectType::Enemy || enemies[e]->GetType() == GameObjectType::EnemyShooter)
				{
					enemies.erase(enemies.begin() + e);
					player->GetHealth()--;
					Mix_PlayChannel(-1, soundEffects.at("Death"), 0);
					break;
				}
				else if (enemies[e]->GetType() == GameObjectType::HealingObj)
				{
					enemies.erase(enemies.begin() + e);
					if (player->GetHealth() == 5)
					{
						score += 10;
					}
					player->GetHealth() += 3;
					Mix_PlayChannel(-1, soundEffects.at("PowerUp"), 0);
					break;
				}
			}
		}

		for (int eb = 0; eb < enemyBullets.size(); eb++)
		{
			enemyBullets[eb]->Update(*window, -(targetWidth / 2.0f), (targetWidth / 2.0f), -(targetHeight / 2.0f), (targetHeight / 2.0f), soundEffects);

			if (enemyBullets[eb]->GetAABB().Intersects(player->GetAABB()))
			{
				enemyBullets.erase(enemyBullets.begin() + eb);
				player->GetHealth()--;
				Mix_PlayChannel(-1, soundEffects.at("Death"), 0);
				break;
			}
		}

		std::string string = std::to_string((int)player->GetHealth());
		healthText->UpdateText(string);
		string = "Score: " + std::to_string((int)score);
		scoreText->UpdateText(string);
		string = "Current Wave: " + std::to_string((int)wave->GetWaveIndex());
		waveIndexText->UpdateText(string);

		if (player->GetHealth() <= 0)
		{
			gameOver = true;
		}
	}
	else
	{
		if (window->CheckKeyUp(SDL_SCANCODE_ESCAPE))
			SwitchPaused();
		quitButton->Update(*window, soundEffects.at("Click"));
	}
}

void MainGameState::Render()
{
	glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	mainShader->Use();
	mainShader->SetMat4("View", camera->GetViewMatrix());

	player->Render(*mainShader.get(), GL_TRIANGLES);
	wave->Render(*mainShader.get());

	for (int i = 0; i < player->GetBullets().size(); i++)
	{
		player->GetBullets()[i]->Render(*mainShader.get(), GL_TRIANGLES);
	}

	for (int i = 0; i < enemyBullets.size(); i++)
	{
		enemyBullets[i]->Render(*mainShader.get(), GL_TRIANGLES);
	}

	maxHealthText->Render(1.0f, 1.0f, 1.0f, 1.0f);
	healthText->Render(1.0f, 0.0f, 0.0f, 1.0f);
	scoreText->Render(1.0f, 1.0f, 1.0f, 1.0f);
	waveIndexText->Render(1.0f, 1.0f, 1.0f, 1.0f);

	if (paused)
	{
		pauseText->Render(1.0f, 0.0f, 0.0f, 1.0f);
		quitButton->Render();
	}

	window->SwapBuffers();
}

bool MainGameState::GetQuitButtonInteractedWith() const
{
	return quitButton->WasInteractedWith();
}

glm::mat4 MainGameState::GetProjectionMatrix()
{
	float aspect = (float)window->GetWidth() / window->GetHeight();
	targetHeight = 180.0f;
	targetWidth = targetHeight * aspect;

	glm::mat4 projection = glm::ortho(-(targetWidth / 2.0f), (targetWidth / 2.0f), -(targetHeight / 2.0f), (targetHeight / 2.0f), -1.0f, 1.0f);

	return projection;
}

void MainGameState::SwitchPaused()
{
	paused = !paused;
}

int& MainGameState::GetScore()
{
	return score;
}

bool MainGameState::GetGameOver()
{
	return gameOver;
}
