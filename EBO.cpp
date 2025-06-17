#include <Graphics/EBO.h>

EBO::EBO(const std::vector<unsigned int>& indices, int _bufferUsage)
{
	bufferUsage = _bufferUsage;

	glGenBuffers(1, &ID);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), bufferUsage);

	indexCount = static_cast<int>(indices.size());
}

EBO::~EBO()
{
	glDeleteBuffers(1, &ID);
}

void EBO::Use()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unuse()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::ReconstructBuffer(const std::vector<unsigned int>& indices)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), bufferUsage);

	indexCount = static_cast<int>(indices.size());
}

int EBO::GetIndexCount() const
{
	return indexCount;
}
