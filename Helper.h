#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <map>
#include <vector>
#include <string>
#include <memory>
#include <cstdint>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

#define Log(message)\
std::clog << "Log: " << message << '\n';

#define Warning(message)\
std::cerr << "Warning: " << message << '\n';

#define Error(message)\
{\
	std::stringstream sStr;\
	sStr << "Error: " << message << '\n';\
	throw std::runtime_error(sStr.str());\
}

struct Vertex
{
	glm::vec2 aPos;
	glm::vec2 aUV;
};

static std::string LoadFileContents(const std::string& filename)
{
	std::ifstream file(filename);

	if (!file.is_open())
	{
		Warning("Failed to open file " << filename);
		return "NULL";
	}

	std::string content;
	std::stringstream sStr;

	sStr << file.rdbuf();

	content = sStr.str();

	file.close();

	return content;
}
