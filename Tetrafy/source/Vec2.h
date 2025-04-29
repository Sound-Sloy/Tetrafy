#pragma once

template <typename T>
class Vec2
{
public:
	Vec2() = default;
	constexpr Vec2(T x, T y)
		:
		x(x),
		y(y)
	{}
	constexpr T GetX() const { return this->x; };
	constexpr T GetY() const { return this->y; };
	constexpr void SetX(T x) { this->x = x; };
	constexpr void SetY(T y) { this->y = y; };

	template <class C>
	constexpr Vec2<C> As() const {
		return Vec2<C>{(C)x, (C)y};
	}

	template <class C, typename U>
	constexpr C CastAs() const {
		return C{(U)x, (U)y};
	}

	constexpr float Length() const {
		return sqrt(x * x + y * y);
	}

	constexpr Vec2<T> Normalize() const {
		float len = Length();
		if (len == 0) return Vec2(0, 0);  // Avoid divide by zero
		return Vec2<T>(x / len, y / len);
	}


public:
	constexpr bool operator==(const Vec2& rhs) const
	{
		return (this->x == rhs.x && this->y == rhs.y);
	}
	constexpr bool operator!=(const Vec2& rhs) const
	{
		return !(*this == rhs);
	}
	constexpr Vec2 operator+(const Vec2& rhs) const
	{
		return { this->x + rhs.x, this->y + rhs.y };
	}
	constexpr Vec2 operator+(const int rhs) const
	{
		return { this->x + rhs, this->y + rhs };
	}
	constexpr Vec2& operator+=(const Vec2& rhs)
	{
		return *this = *this + rhs;
	}
	constexpr Vec2 operator-(const Vec2& rhs) const
	{
		return { this->x - rhs.x, this->y - rhs.y };
	}
	constexpr Vec2 operator-(const int rhs) const
	{
		return { this->x - rhs, this->y - rhs };
	}
	constexpr Vec2& operator-=(const Vec2& rhs)
	{
		return *this = *this - rhs;
	}
	constexpr Vec2 operator*(const Vec2& rhs) const
	{
		return { this->x * rhs.x, this->y * rhs.y };
	}
	//constexpr Vec2 operator*(const int rhs) const
	//{
	//	return { this->x * rhs, this->y * rhs };
	//}
	constexpr Vec2 operator*(const T rhs) const
	{
		return { this->x * rhs, this->y * rhs };
	}
	constexpr Vec2& operator*=(const Vec2& rhs)
	{
		return *this = *this * rhs;
	}
	constexpr Vec2 operator/(const int rhs) const
	{
		return { this->x / rhs, this->y / rhs };
	}

private:
	T x;
	T y;
};