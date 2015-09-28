/*
file: particles.h
*/

#pragma once

#include <list>
#include <boost/shared_ptr.hpp>
#include "math_vector2.h"
#include "util_memory.h"

class Emitter;

typedef boost::shared_ptr<Emitter> emitPtr_t;

struct Particle : public UTIL::Memory<Particle> {
	Particle *prev, *next;

	int sprite;
	int color;

	MATH::Vector2 position;
	MATH::Vector2 velocity;

	float rotation;
	float angularVelocity;

	float health;
	float decay;
};

class Emitter {
private:
	Particle* _particles;
	MATH::Vector2 _position;

	static std::list<emitPtr_t> emitters;
public:
	Emitter(void);
	virtual ~Emitter(void) { }

	void SetPosition(const MATH::Vector2& position);
	const MATH::Vector2& GetPosition(void) const;

	Particle* Spawn(void);

	void Move(float secsPassed);
	void Draw(sf::RenderTarget& renderTarget);

	virtual void Emit(void) = 0;
	virtual void DrawParticle(Particle* particle, sf::RenderTarget& renderTarget) = 0;
};