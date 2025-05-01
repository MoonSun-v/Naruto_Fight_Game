#include "pch.h"
#include "Character.h"
#include "RenderManager.h" // 이렇게 해도 되는거구나..?!

Character::Character() {}
Character::~Character() { delete pBitmap; }

void Character::SetBitmap(Gdiplus::Bitmap* bmp)
{
	pBitmap = bmp;
	UpdateCollider();
}

void Character::Update()
{
	UpdateCollider();
}

void Character::Render()
{
	if (pBitmap) RenderManager::Get().DrawImageCenter(pBitmap, position.x, position.y);
	RenderManager::Get().DrawAABB(GetAABB());
}

void Character::UpdateCollider()
{
	if (!pBitmap) return;
	collider = AABB(position + Vector2(pBitmap->GetWidth() / 2, pBitmap->GetHeight() / 2),
		Vector2(pBitmap->GetWidth() / 2, pBitmap->GetHeight() / 2));
}

AABB Character::GetAABB() const
{
	return collider;
}