/*
file: boost_emitter.cpp
*/

#include "math2.h"
#include "image_manager.h"
#include "boost_emitter.h"

sf::Sprite spriteTable[4];

BoostEmitter::BoostEmitter(void) {
	_sprite = ImageManager::Instance().CreateSprite("res/smoke.png");
	_sprite.SetCenter(16.0f, 16.0f);
}

void BoostEmitter::SetDirection(const MATH::Vector2& direction) {
	_direction = direction;
}

void BoostEmitter::Emit(void) {
	for(int i = 0; i < 5; ++i) {
		Particle* particle = Spawn();

		particle->health = 1.0f;
		particle->decay = sf::Randomizer::Random(1.2f, 1.6f);

		particle->velocity = _direction * sf::Randomizer::Random(50.0f, 80.0f);
		particle->position = GetPosition();

		particle->rotation = 0.0f;
		particle->angularVelocity = sf::Randomizer::Random(20.0f, 40.0f);
	}
}

void BoostEmitter::DrawParticle(Particle* particle, sf::RenderTarget& renderTarget) {
	_sprite.SetPosition(particle->position.sfVec());
	float scale = particle->health;

	sf::Color color = sf::Color(255, 255, 255);
	sf::Color target = sf::Color(224, 221, 241);

	sf::Color interpol;
	interpol.r = (color.r - target.r) * particle->health + target.r;
	interpol.g = (color.g - target.g) * particle->health + target.g;
	interpol.b = (color.b - target.b) * particle->health + target.b;
	interpol.a = 255 * particle->health;
	
	_sprite.SetRotation(particle->rotation);
	_sprite.SetScale(scale, scale);
	_sprite.SetColor(interpol);
	renderTarget.Draw(_sprite);
}