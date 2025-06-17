#pragma once

#include <glad/glad.h>

#include <Helper.h>

class EBO
{
private:
	unsigned int ID;

	int bufferUsage;

	int indexCount = 0;

public:
	EBO(const std::vector<unsigned int>& indices, int _bufferUsage);
	~EBO();

	void Use();
	void Unuse();

	void ReconstructBuffer(const std::vector<unsigned int>& indices);

	int GetIndexCount() const;
};
