/*
file: blur_emitter.cpp
*/

#include "ent_ball.h"
#include "image_manager.h"
#include "blur_emitter.h"

BlurEmitter::BlurEmitter(void) {
	_sprite = ImageManager::Instance().CreateSprite("res/ball3.png");
	_scale = BALL_SIZE / _sprite.GetSize().x;
	_sprite.SetCenter(0.5f * _sprite.GetSize());
	_sprite.Resize(_scale, _scale);
}

void BlurEmitter::Emit(void) {
	Particle* particle = Spawn();
	particle->health = 1.0f;
	particle->decay = 1.0f;

	particle->position = GetPosition();
	particle->velocity = MATH::Vector2(0.0f, 0.0f);
}

void BlurEmitter::DrawParticle(Particle* particle, sf::RenderTarget& renderTarget) {
	_sprite.SetPosition(particle->position.sfVec());
	_sprite.SetScale(_scale * particle->health, _scale * particle->health);
	_sprite.SetColor(sf::Color(255, 255, 255, 70 * particle->health * particle->health));
	renderTarget.Draw(_sprite);
}