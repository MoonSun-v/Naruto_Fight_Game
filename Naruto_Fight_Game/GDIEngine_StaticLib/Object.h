#pragma once

#include "../Vector2_StaticLib/AABB.h"

class Object
{
protected:
	bool m_bPendingDelete = false; // 삭제 예약 여부를 나타내는 플래그

public:
	Object() = default;
	virtual ~Object() = default;

	virtual void Update() = 0;
	virtual void Render() = 0;

	Vector2 position;
	
	void SetPosition(float x, float y) { position.x = x; position.y = y; }
	void SetPosition(const Vector2& pos) { position = pos; }
	Vector2 GetPosition() const { return position; }

	// 객체를 삭제 대상으로 표시
	void MarkForDelete() { m_bPendingDelete = true; }

	// 객체가 삭제 예약되었는지 여부 반환
	bool IsPendingDelete() const { return m_bPendingDelete; }
};