#pragma once

#include <glad/glad.h>

#include <Helper.h>

class VBO
{
private:
	unsigned int ID;

	int bufferUsage;

	int vertexCount = 0;

public:
	VBO(const std::vector<Vertex>& vertices, int _bufferUsage);
	~VBO();

	void Use();
	void Unuse();

	void ReconstructBuffer(const std::vector<Vertex>& vertices);

	int GetVertexCount() const;
};
