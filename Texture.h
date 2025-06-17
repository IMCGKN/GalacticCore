#pragma once

#include <Helper.h>

#include <glad/glad.h>

#include <stb/stb_image.h>

class Texture
{
private:
	unsigned int ID;

	int width;
	int height;

	bool isUsed = false;

	int textureType;
	int textureFormat;

	int textureId = 0;

public:
	Texture(const std::string& filepath, int _textureType, unsigned int _textureFormat, int minFilter, int magFilter);
	Texture(int resource, int _textureType, unsigned int _textureFormat, int minFilter, int magFilter);
	~Texture();

	void Use();
	void Unuse();

	int GetWidth() const;
	int GetHeight() const;
	int GetTextureID() const;
};
