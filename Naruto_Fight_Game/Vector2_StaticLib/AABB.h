#pragma once
#include "Vector2.h"

class AABB
{
public:
    Vector2 m_Center;
    Vector2 m_Extent;

    AABB() = default;
    AABB(const Vector2& center, const Vector2& extent) : m_Center(center), m_Extent(extent) {}

    float GetMinX() const { return m_Center.x - m_Extent.x; }
    float GetMaxX() const { return m_Center.x + m_Extent.x; }
    float GetMinY() const { return m_Center.y - m_Extent.y; }
    float GetMaxY() const { return m_Center.y + m_Extent.y; }

    bool CheckIntersect(const AABB& other);

};