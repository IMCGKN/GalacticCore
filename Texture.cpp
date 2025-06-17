#include <Graphics/Texture.h>

#include "resource1.h"
#include <Windows.h>

static int currentTextureId = 0;
Texture::Texture(const std::string& filepath, int _textureType, unsigned int _textureFormat, int minFilter, int magFilter)
{
    textureType = _textureType;
    textureFormat = _textureFormat;
    glGenTextures(1, &ID);

    glBindTexture(textureType, ID);

    glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, magFilter);

    int w, h, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filepath.c_str(), &w, &h, &nrChannels, 0);
    width = w;
    height = h;
    if (data)
    {
        glTexImage2D(textureType, 0, textureFormat, width, height, 0, textureFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(textureType);
    }
    else
    {
        Warning("Failed to load texture " << filepath << "!");
    }
    stbi_image_free(data);

    textureId = currentTextureId;
    currentTextureId++;
}

Texture::Texture(int resource, int _textureType, unsigned int _textureFormat, int minFilter, int magFilter)
{
    textureType = _textureType;
    textureFormat = _textureFormat;
    glGenTextures(1, &ID);

    glBindTexture(textureType, ID);

    glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, magFilter);

    HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(resource), L"PNG");
    HGLOBAL hData = LoadResource(NULL, hRes);
    void* pData = LockResource(hData);
    DWORD dataSize = SizeofResource(NULL, hRes);

    int w, h, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load_from_memory((unsigned char*)pData, dataSize, &w, &h, &nrChannels, 0);
    if (!data)
    {
        Warning("Fasiled to load data from memory!");
    }
    width = w;
    height = h;
    if (data)
    {
        glTexImage2D(textureType, 0, textureFormat, width, height, 0, textureFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(textureType);
    }
    stbi_image_free(data);

    textureId = currentTextureId;
    currentTextureId++;
}

Texture::~Texture()
{
    glDeleteTextures(1, &ID);
}

void Texture::Use()
{
    if (!isUsed)
    {
        isUsed = true;
        glActiveTexture(GL_TEXTURE0 + textureId);
        glBindTexture(textureType, ID);
    }
}

void Texture::Unuse()
{
    if (isUsed)
    {
        isUsed = false;
        glBindTexture(textureType, 0);
    }
}

int Texture::GetWidth() const
{
    return width;
}

int Texture::GetHeight() const
{
    return height;
}

int Texture::GetTextureID() const
{
    return textureId;
}
