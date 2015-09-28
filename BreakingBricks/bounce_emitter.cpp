/*
file: bounce_emitter.h
*/

#include "math2.h"
#include "image_manager.h"
#include "bounce_emitter.h"

static sf::Color colorTable[] = {
	sf::Color(199, 243, 239),
	sf::Color(245, 246, 163),
	sf::Color(224, 221, 241)
};

static sf::Sprite spriteTable[6];

BounceEmitter::BounceEmitter(void) {
	spriteTable[0] = ImageManager::Instance().CreateSprite("res/circle.png");
	spriteTable[1] = ImageManager::Instance().CreateSprite("res/star.png");
	spriteTable[2] = ImageManager::Instance().CreateSprite("res/note.png");
	spriteTable[3] = ImageManager::Instance().CreateSprite("res/spring.png");
	spriteTable[4] = ImageManager::Instance().CreateSprite("res/question.png");
	spriteTable[5] = ImageManager::Instance().CreateSprite("res/sharp.png");

	for(int i = 0; i < 6; ++i) spriteTable[i].Resize(10.0f, 10.0f);
}

void BounceEmitter::Emit(void) {
	float angle = 0.0f;
	while(M_2PI > angle) {
		Particle* particle = Spawn();
		particle->health = 100.0f;
		particle->decay = sf::Randomizer::Random(40.0f, 70.0f);

		particle->sprite = sf::Randomizer::Random(0, 5);
		particle->color = sf::Randomizer::Random(0, 2);

		particle->rotation = 0.0f;
		particle->angularVelocity = sf::Randomizer::Random(100.0f, 200.0f);

		MATH::Vector2 direction(cosf(angle), sinf(angle));
		particle->position = GetPosition();
		particle->velocity = direction * sf::Randomizer::Random(50.0f, 100.0f);

		angle += sf::Randomizer::Random(0.5f, 1.0f);
	}
}

void BounceEmitter::DrawParticle(Particle* particle, sf::RenderTarget& renderTarget) {
	sf::Sprite& sprite = spriteTable[particle->sprite];
	sprite.SetPosition(particle->position.sfVec());
	float fac = particle->health / 120.0f;
	sf::Color color = colorTable[particle->color];
	color.a = 255 * fac;
	sprite.SetRotation(particle->rotation);
	sprite.SetColor(color);
	sprite.SetScale(fac, fac);
	renderTarget.Draw(sprite);
}