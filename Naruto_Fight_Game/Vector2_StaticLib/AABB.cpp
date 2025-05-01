#include "pch.h"
#include "AABB.h"

bool AABB::CheckIntersect(const AABB& other)
{
    // self min,max
    float BoxA_min_x = m_Center.x - m_Extent.x;
    float BoxA_max_x = m_Center.x + m_Extent.x;
    float BoxA_min_y = m_Center.y - m_Extent.y;
    float BoxA_max_y = m_Center.y + m_Extent.y;

    // other min,max
    float BoxB_min_x = other.m_Center.x - other.m_Extent.x;
    float BoxB_max_x = other.m_Center.x + other.m_Extent.x;
    float BoxB_min_y = other.m_Center.y - other.m_Extent.y;
    float BoxB_max_y = other.m_Center.y + other.m_Extent.y;

    // Check for no overlap conditions
    if ((BoxA_max_x < BoxB_min_x) || // 오른쪽 모서리가 왼쪽 모서리보다 왼쪽
        BoxA_min_x > BoxB_max_x ||   // 왼쪽 모서리가 오른쪽 모서리보다 오른쪽
        BoxA_min_y > BoxB_max_y ||   // 위쪽 모서리가 아래쪽 모서리보다 아래쪽
        BoxA_max_y < BoxB_min_y)     // 아래쪽 모서리가 위쪽 모서리보다 위쪽
    {
        return false;
    }

    return true;
}