/*
file: particles.cpp
*/

#include "particles.h"

Emitter::Emitter(void) : _particles(NULL) {
}

void Emitter::SetPosition(const MATH::Vector2& position) {
	_position = position;
}

const MATH::Vector2& Emitter::GetPosition(void) const {
	return _position;
}

void Emitter::Move(float secsPassed) {
	Particle* particle = _particles;
	while(NULL != particle) {
		Particle* next = particle->next;
		Particle* prev = particle->prev;
		if(0.0f >= particle->health) {
			if(NULL != prev) prev->next = next;
			else _particles = next;
			if(NULL != next) next->prev = prev;
			delete particle;
			particle = next;
			continue;
		}
		particle->position += particle->velocity * secsPassed;
		particle->health -= particle->decay * secsPassed;
		particle->rotation += particle->angularVelocity * secsPassed;
		particle = particle->next;
	}
}

void Emitter::Draw(sf::RenderTarget& renderTarget) {
	Particle* particle = _particles;
	while(NULL != particle) {
		if(0 < particle->health) {
			DrawParticle(particle, renderTarget);
		}
		particle = particle->next;
	}
}

Particle* Emitter::Spawn(void) {
	Particle* particle = new Particle;
	particle->prev = NULL;
	particle->next = _particles;
	if(NULL != _particles) {
		_particles->prev = particle;
	}
	_particles = particle;
	return particle;
}