#include <App/State.h>

State::State(Window* _window)
{
	window = _window;
}

State::~State()
{
}

void State::ConstructShader(const std::string& vFilePath, const std::string& fFilePath)
{
	mainShader = std::make_unique<Shader>(vFilePath, fFilePath);
}

void State::ConstructShader(const std::string& vShaderContent, const std::string& fShaderContent, bool v)
{
	mainShader = std::make_unique<Shader>(vShaderContent, fShaderContent, v);
}
