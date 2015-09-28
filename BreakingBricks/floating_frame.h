/*
file: floating_frame.h
*/

#pragma once

#include "math_vector2.h"

class FloatingFrame {
private:
	enum {
		UPPER_LEFT = 0,
		UPPER_RIGHT,
		LOWER_RIGHT,
		LOWER_LEFT
	};

	struct FloatingVertex {
		MATH::Vector2 direction;
		float velocity;
		float distance;
	};

	FloatingVertex _floatingVertices[4];
	static const MATH::Vector2 innerVertices[4];
public:
	FloatingFrame(void);

	void Move(float secsPassed);
	void Draw(sf::RenderTarget& renderTarget);
};