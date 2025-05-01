#pragma once
#include "Object.h"

class Character : public Object
{
public:
	Character();
	virtual ~Character();

	virtual void Update() override;
	virtual void Render() override;

	void SetBitmap(Gdiplus::Bitmap* bmp);
	void UpdateCollider();
	AABB GetAABB() const;

protected:
	Gdiplus::Bitmap* pBitmap = nullptr;
	AABB collider;
};