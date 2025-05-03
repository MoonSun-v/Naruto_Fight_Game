#include "pch.h"
#include "Vector2.h"

// ������
Vector2::Vector2(float x, float y) : x(x), y(y) {}

// + ���ϱ�
Vector2 Vector2::operator+(const Vector2& rhs) const {

    return Vector2(x + rhs.x, y + rhs.y);
}

// - ����
Vector2 Vector2::operator-(const Vector2& rhs) const {

    return Vector2(x - rhs.x, y - rhs.y);
}

// * ��Į�� ��
Vector2 Vector2::operator*(float scalar) const {

    return Vector2(x * scalar, y * scalar);
}

// / ��Į�� ������
Vector2 Vector2::operator/(float scalar) const {

    if (fabs(scalar) > EPSILON) {
        return Vector2(x / scalar, y / scalar);
    }
    return Vector2(0.0f, 0.0f); // 0�� ����� ������ ������ ��� 0 ���� ��ȯ
}

// += ���ϱ� ����
Vector2& Vector2::operator+=(const Vector2& rhs) {

    x += rhs.x;
    y += rhs.y;
    return *this;
}

// -= ���� ����
Vector2& Vector2::operator-=(const Vector2& rhs) {

    x -= rhs.x;
    y -= rhs.y;
    return *this;
}


// ������ ���̰� 0���� Ȯ��
bool Vector2::IsZero() const {

    return fabs(x) < EPSILON && fabs(y) < EPSILON; // �ε��Ҽ��� ���� ���
}

// ���� ���� (Dot Product)
float Vector2::Dot(const Vector2& other) const {

    float dot = x * other.x + y * other.y;

    if (fabs(dot) < EPSILON) return 0.0f;           // ���� 0�̸� 0���� ����
    if (fabs(dot - 1.0f) < EPSILON) return 1.0f;    // ���� 1�̸� 1�� ����
    if (fabs(dot + 1.0f) < EPSILON) return -1.0f;   // ���� -1�̸� -1�� ����

    return dot;
}

// ���� ����ȭ : ���� ���� 1 , ���� ���� 
void Vector2::Normalize() {

    float length = Length();

    if (length > EPSILON) { // �ε��Ҽ��� ���� ��� : ���̰� 0�� ����� ��� ����ȭ X
        x /= length;
        y /= length;
    }
}

// ����ȭ�� ���纻 ��ȯ
Vector2 Vector2::Normalized() const
{
    float length = Length();

    if (length > EPSILON)
        return Vector2(x / length, y / length);

    return Vector2(0.0f, 0.0f);
}


// ���� ����
float Vector2::Length() const {

    return sqrt(x * x + y * y);
}

// ���� ������ ���� 
float Vector2::LengthSQ() const {

    return x * x + y * y;
}


// �� ���� ���� �Ÿ�
float Vector2::Distance(const Vector2& other) const {

    float dx = x - other.x;
    float dy = y - other.y;
    float dist = dx * dx + dy * dy;

    if (dist < EPSILON) return 0.0f; // �ε��Ҽ��� ���� ��� : ���� 0�� ��� 0���� ��ȯ

    return sqrt(dist);
}


// ��� ������ (Ŭ���� �ܺο��� ����) : ���� �Լ� 
ostream& operator<<(ostream& os, const Vector2& v) {

    os << "(" << v.x << ", " << v.y << ")";
    return os;
}