/*
file: math2.h
*/

#pragma once

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265f
#endif

// TODO
#define M_2PI 2.0f * M_PI

//#define min(x, y) x < y ? x : y
//#define max(x, y) x > y ? x : y

namespace MATH {

	template<typename TYPE>
	inline TYPE Min(const TYPE& lhp, const TYPE& rhp) {
		return lhp < rhp ? lhp : rhp;
	}

	template<typename TYPE>
	inline TYPE Max(const TYPE& lhp, const TYPE& rhp) {
		return lhp > rhp ? lhp : rhp;
	}

	inline bool DoSegmentsOverlap(float fa, float ta, float fb, float tb, float& cut) {
		if(ta >= fb && fa <= tb) {
			cut = Min(ta, tb) - Max(fa, fb);
			return true;
		}
		return false;
	}

} // namespace MATH