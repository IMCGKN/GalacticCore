#pragma once

#include <Helper.h>
#include <Graphics/Shader.h>
#include <Graphics/Renderable.h>

class AABB
{
private:
	float left;
	float right;
	float bottom;
	float top;

public:
	AABB(float _left, float _right, float _bottom, float _top);
	AABB(const glm::vec2& pos, const glm::vec2& size);
	~AABB();

	bool Contains(const glm::vec2& pos);
	bool Contains(float x, float y);

	bool Intersects(const AABB& other) const;

	bool IsOffScreen(float _left, float _right, float _bottom, float _top) const;
	bool IsOffScreenOnlyBottom(float _bottom) const;

	float& GetLeft();
	float& GetRight();
	float& GetBottom();
	float& GetTop();
};
