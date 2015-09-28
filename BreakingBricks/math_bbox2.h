/*
file: math_bbox2.h
*/

#pragma once

#include "math2.h"
#include "math_vector2.h"

namespace MATH {

	class BBox2 {
	public:
		MATH::Vector2 upperLeft;
		MATH::Vector2 lowerRight;

		BBox2(void) /* defaults vectors to zero */ { }

		BBox2(const MATH::Vector2& upperLeft, const MATH::Vector2& lowerRight)
			: upperLeft(upperLeft), lowerRight(lowerRight) { }

		BBox2& operator=(const BBox2& other) {
			upperLeft = other.upperLeft;
			lowerRight = other.lowerRight;
			return *this;
		}
	};

	static bool Overlaps(const MATH::BBox2& lhp, const MATH::BBox2& rhp, float& cutX, float& cutY) {
		float fa, ta, fb, tb;
		bool overlapX, overlapY;

		fa = lhp.upperLeft.x;
		ta = lhp.lowerRight.x;
		fb = rhp.upperLeft.x;
		tb = rhp.lowerRight.x;

		overlapX = DoSegmentsOverlap(fa, ta, fb, tb, cutX);

		fa = lhp.upperLeft.y;
		ta = lhp.lowerRight.y;
		fb = rhp.upperLeft.y;
		tb = rhp.lowerRight.y;

		overlapY = DoSegmentsOverlap(fa, ta, fb, tb, cutY);

		return overlapX && overlapY;
	}

} // namespace MATH