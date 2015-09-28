/*
file: xbox_gamepad.h
*/

#pragma once

namespace XBOX {

	// side 0 = left, 1 = right
	void Rumble(int side, float duration, float amplitude);
	void Update(float secsPassed);

} // namespace XBOX