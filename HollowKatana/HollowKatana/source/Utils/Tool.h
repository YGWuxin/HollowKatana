#pragma once
#include "../Game/Vector2.h"

class Tool
{
public:
	Tool() = default;
	~Tool() = default;

	static float lerp_float(float start, float end, float t)
	{
		return (1 - t) * start + t * end;
	}

	static Vector2 lerp_vector2(Vector2 start, Vector2 end, float t)
	{
		return Vector2(lerp_float(start.x, end.x, t), lerp_float(start.y, end.y, t));
	}

};

