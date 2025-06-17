#include "AABB.h"

AABB::AABB(float _left, float _right, float _bottom, float _top)
	: left(_left), right(_right), bottom(_bottom), top(_top)
{
}

AABB::AABB(const glm::vec2& pos, const glm::vec2& size)
	: left(pos.x), right(pos.x + size.x), bottom(pos.y), top(pos.y + size.y)
{
}

AABB::~AABB()
{
}

bool AABB::Contains(const glm::vec2& pos)
{
	return pos.x >= left && pos.x <= right && pos.y >= bottom && pos.y <= top;
}

bool AABB::Contains(float x, float y)
{
	return x >= left && x <= right && y >= bottom && y <= top;
}

bool AABB::Intersects(const AABB& other) const
{
	return !(right < other.left ||
		left > other.right ||
		top < other.bottom ||
		bottom > other.top);
}


bool AABB::IsOffScreen(float _left, float _right, float _bottom, float _top) const
{
	return (right < _left ||
            left > _right ||
            top < _bottom ||
            bottom > _top);
}

bool AABB::IsOffScreenOnlyBottom(float _boundsTop) const
{
	return (bottom < _boundsTop);
}

float& AABB::GetLeft()
{
	return left;
}

float& AABB::GetRight()
{
	return right;
}

float& AABB::GetBottom()
{
	return bottom;
}

float& AABB::GetTop()
{
	return top;
}
