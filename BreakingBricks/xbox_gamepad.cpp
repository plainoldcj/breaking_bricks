/*
file: xbox_gamepad.h
*/

#include <windows.h>
#include <xinput.h>
#include "math2.h"
#include "xbox_gamepad.h"

namespace XBOX {

	struct Vibration {
		int rumble;
		float timePassed;
		float angle;
		float duration;
		float amplitude;
	};
	static Vibration s_vibration[2];

	void Rumble(int side, float duration, float amplitude) {
		s_vibration[side].rumble = 1;
		s_vibration[side].timePassed = 0.0f;
		s_vibration[side].angle = 0.0f;
		s_vibration[side].duration = duration;
		s_vibration[side].amplitude = amplitude;
	}

	void Update(float secsPassed) {
		for(int side = 0; side < 2; ++side) {
			if(s_vibration[side].rumble) {
				s_vibration[side].timePassed += secsPassed;

				s_vibration[side].angle += M_2PI * secsPassed / s_vibration[side].duration;
				float val = s_vibration[side].amplitude * sinf(s_vibration[side].angle);

				XINPUT_VIBRATION state;
				ZeroMemory(&state, sizeof(XINPUT_VIBRATION));

				if(s_vibration[side].timePassed >= s_vibration[side].duration) {
					s_vibration[side].rumble = 0;
				} else {
					switch(side) {
						case 0: state.wLeftMotorSpeed = val; break;
						case 1: state.wRightMotorSpeed = val; break;
					}
				}

				XInputSetState(0, &state);
			}
		}
	}

} // namespace XBOX