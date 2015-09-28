/*
file: blur_emitter.h
*/

#pragma once

#include "particles.h"

class BlurEmitter : public Emitter {
private:
	sf::Sprite _sprite;
	float _scale;
public:
	BlurEmitter(void);

	void Emit(void);
	void DrawParticle(Particle* particle, sf::RenderTarget& renderTarget);
};