/*
file: ent_ball.cpp
*/

#include "image_manager.h"
#include "xbox_gamepad.h"
#include "gs_game.h"
#include "ent_ball.h"

namespace ENT {

	Ball::Ball(Rules& rules) : Entity(rules) {
		rules.numBalls++;

		_ignited = false;
		_dying = false;

		_scoreSound = SoundManager::Instance().GetSound("res/ding.wav", false);
		_bounceSound = SoundManager::Instance().GetSound("res/bounce.wav", false);

		_ballSprite = ImageManager::Instance().CreateSprite("res/ball3.png");
		_ballSprite.SetColor(sf::Color(232, 243, 255));
		_ballSprite.Resize(BALL_SIZE, BALL_SIZE);

		MATH::Vector2 randomVector(0, -1.0f);
		randomVector = MATH::Rotate(randomVector, sf::Randomizer::Random(-0.1f, 0.1f));
		randomVector = MATH::Normalize(randomVector);

		SetAcceleration(1.0f);
		SetVelocity(randomVector * 300.0f);
		SetMass(1.0f);

		SetPhysicsModel(PHY_TOUCHING | PHY_SOLID | PHY_BOUNCING);
		SetCollisionModel(PHY_SOLID);

		SetBBox(MATH::BBox2(MATH::Vector2(0.0f, 0.0f),
			MATH::Vector2(BALL_SIZE, BALL_SIZE)));
	}

	void Ball::Ignite(void) {
		_ignited = true;
	}

	void Ball::TouchEffects(void) {
		if(!_dying) {
			_emitter.SetPosition(GetPosition());
			_emitter.Emit();
		}
	}

	void Ball::Touch(ENT::Block& block, TouchInfo info) {
		TouchEffects();
		XBOX::Rumble(1, 0.2f, 4000.0f);
		_scoreSound->Play(sf::Randomizer::Random(30000.0f, 40000.0f), 0.3f);

		if(_ignited) {
			MATH::Vector2 velocity = GetVelocity();
			if(info.cutX > info.cutY) velocity.y *= -1.0f;
			else velocity.x *= -1.0f;
			SetVelocity(velocity);
		}
	}

	void Ball::Touch(ENT::Paddle& paddle, TouchInfo info) {
		TouchEffects();
		XBOX::Rumble(0, 0.2f, 4000.0f);
		_bounceSound->Play();
	}

	void Ball::TouchBoard(BoardSide side) {
		TouchEffects();
		XBOX::Rumble(1, 0.2f, 4000.0f);
		_bounceSound->Play();

		if(!_dying && BOTTOM == side) {
			_dying = true;
			_health = 1.0f;
			_decayRate = 2.0f;
		}

		/*
		this makes the game a little less predictable and prevents the
		ball from bouncing horizontally all the time
		*/
		if(TOP == side || BOTTOM == side) SetVelocity(MATH::Rotate(GetVelocity(), sf::Randomizer::Random(-0.1f, 0.1f)));
		else SetVelocity(MATH::Rotate(GetVelocity(), sf::Randomizer::Random(-0.2f, 0.2f)));
	}

	void Ball::Think(float secsPassed) {
		_emitter.Move(secsPassed);
		_blur.Move(secsPassed);

		if(!_dying) {
			MATH::Vector2 position(GetPosition());
			sf::Vector2f offset = 0.5f * _ballSprite.GetSize();
			position.x += offset.x;
			position.y += offset.y;
			_blur.SetPosition(position);
			_blur.Emit();
		}

		/*
		okay, this is of course super non-realistic, but we need
		a (not too) fast ball to keep the game going
		*/
		float vel = GetVelocity().Length();
		
		if(900.0f < vel) {
			SetVelocity(900.0f * MATH::Normalize(GetVelocity()));
		}
		
		if(300.0f < vel) {
			SetAcceleration(0.98f);
		} else if(300.0f > vel)  {
			SetAcceleration(1.02f);
		} else {
			SetAcceleration(1.0f);
		}

		if(_dying) {
			_health -= _decayRate * secsPassed;
			if(0.0f >= _health) {
				GetRules().numBalls--;
				Die();
			}
		}
	}

	void Ball::Draw(sf::RenderTarget& renderTarget) {
		sf::Color color(255, 255, 255);
		if(_dying) {
			float scale = std::max(_health, 0.0f);
			color.a = static_cast<int>(255 * scale);
			_ballSprite.SetColor(color);
		}

		_emitter.Draw(renderTarget);
		_blur.Draw(renderTarget);
		_ballSprite.SetPosition(GetPosition().sfVec());
		renderTarget.Draw(_ballSprite);
	}

} // namespace ENT