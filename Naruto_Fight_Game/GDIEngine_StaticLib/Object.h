#pragma once

#include "../Vector2_StaticLib/AABB.h"

class Object
{
public:
	Object() = default;
	virtual ~Object() = default;

	virtual void Update() = 0;
	virtual void Render() = 0;

	Vector2 position;
	
	void SetPosition(float x, float y) { position.x = x; position.y = y; }
	void SetPosition(const Vector2& pos) { position = pos; }
	Vector2 GetPosition() const { return position; }

};