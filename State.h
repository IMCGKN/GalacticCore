#pragma once

#include <SDL/SDL_mixer.h>

#include <Window/Window.h>

#include <Graphics/Shader.h>

#include <Helper.h>

class State
{
protected:
	Window* window;

	std::unique_ptr<Shader> mainShader;

public:
	State(Window* _window);
	~State();

	void ConstructShader(const std::string& vFilePath, const std::string& fFilePath);
	void ConstructShader(const std::string& vShaderContent, const std::string& fShaderContent, bool v);

	virtual void Update(const std::map<std::string, Mix_Chunk*>& soundEffects) = 0;
	virtual void Render() = 0;
};
