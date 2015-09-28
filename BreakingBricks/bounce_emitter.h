/*
file: bounce_emitter.h
*/

#pragma once

#include "particles.h"

class BounceEmitter : public Emitter {
public:
	BounceEmitter(void);

	void Emit(void);
	void DrawParticle(Particle* particle, sf::RenderTarget& renderTarget);
};