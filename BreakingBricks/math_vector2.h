/*
file: math_vector2.h
*/

#pragma once

#include <math.h>
#include <sfml/graphics.hpp>

namespace MATH {

	class Vector2 {
	public:
		float x;
		float y;

		Vector2(void) : x(0.0f), y(0.0f) { }
		Vector2(float x, float y) : x(x), y(y) { }

		Vector2& operator=(const Vector2& other) {
			x = other.x;
			y = other.y;
			return *this;
		}

		Vector2& operator+=(const Vector2& other) {
			x += other.x;
			y += other.y;
			return *this;
		}

		Vector2& operator-=(const Vector2& other) {
			x -= other.x;
			y -= other.y;
			return *this;
		}

		Vector2& operator*=(float scalar) {
			x *= scalar;
			y *= scalar;
			return *this;
		}

		float Length(void) const {
			return sqrtf(x * x + y * y);
		}

		sf::Vector2f sfVec(void) const {
			return sf::Vector2f(x, y);
		}
	};

	inline Vector2 operator+(const Vector2& lhp, const Vector2& rhp) {
		return Vector2(lhp.x + rhp.x, lhp.y + rhp.y);
	}

	inline Vector2 operator-(const Vector2& lhp, const Vector2& rhp) {
		return Vector2(lhp.x - rhp.x, lhp.y - rhp.y);
	}

	inline Vector2 operator*(const Vector2& vector, float scalar) {
		return Vector2(vector.x * scalar, vector.y * scalar);
	}

	inline Vector2 operator*(float scalar, const Vector2& vector) {
		return Vector2(vector.x * scalar, vector.y * scalar);
	}

	inline Vector2 operator/(const Vector2& vector, float scalar) {
		return Vector2(vector.x / scalar, vector.y / scalar);
	}

	inline float Dot(const Vector2& lhp, const Vector2& rhp) {
		return lhp.x * rhp.x + lhp.y * rhp.y;
	}

	static Vector2 Normalize(const Vector2& vector) {
		return vector / vector.Length();
	}

	static Vector2 Project(const Vector2& lhp, const Vector2& rhp) {
		return MATH::Normalize(rhp) * Dot(lhp, rhp) / rhp.Length();
	}

	static Vector2 Rotate(const MATH::Vector2& vector, float angle) {
		float cos = cosf(angle);
		float sin = sinf(angle);
		return MATH::Vector2(cos * vector.x - sin * vector.y,
			sin * vector.x + cos * vector.y);
	}

} // namespace MATH