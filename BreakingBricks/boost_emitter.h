/*
file: boost_emitter.h
*/

#pragma once

#include "particles.h"

class BoostEmitter : public Emitter {
private:
	sf::Sprite _sprite;
	MATH::Vector2 _direction;
public:
	BoostEmitter(void);

	void SetDirection(const MATH::Vector2& direction);

	void Emit(void);
	void DrawParticle(Particle* particle, sf::RenderTarget& renderTarget);
};