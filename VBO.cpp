#include <Graphics/VBO.h>

VBO::VBO(const std::vector<Vertex>& vertices, int _bufferUsage)
{
	bufferUsage = _bufferUsage;

	glGenBuffers(1, &ID);

	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), bufferUsage);

	vertexCount = vertices.size();
}

VBO::~VBO()
{
	glDeleteBuffers(1, &ID);
}

void VBO::Use()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unuse()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::ReconstructBuffer(const std::vector<Vertex>& vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), bufferUsage);

	vertexCount = vertices.size();
}

int VBO::GetVertexCount() const
{
	return vertexCount;
}
