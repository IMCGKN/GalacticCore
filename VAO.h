#pragma once

#include <glad/glad.h>

#include <Helper.h>

class VAO
{
private:
	unsigned int ID;

public:
	VAO();
	~VAO();

	void LinkAttrib(unsigned int index, unsigned int size, int type, unsigned int stride, const void* pointer);

	void Use();
	void Unuse();
};
