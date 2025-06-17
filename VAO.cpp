#include <Graphics/VAO.h>

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &ID);
}

void VAO::LinkAttrib(unsigned int index, unsigned int size, int type, unsigned int stride, const void* pointer)
{
	glVertexAttribPointer(index, size, type, GL_FALSE, stride, pointer);
	glEnableVertexAttribArray(index);
}

void VAO::Use()
{
	glBindVertexArray(ID);
}

void VAO::Unuse()
{
	glBindVertexArray(0);
}
