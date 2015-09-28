/*
ent_paddle.cpp
*/

#include "image_manager.h"
#include "ent_ball.h"
#include "ent_paddle.h"

namespace ENT {

	void Paddle::Push(Direction direction) {
		MATH::Vector2 directionVector;
		if(LEFT == direction) directionVector = MATH::Vector2(-1.0f, 0.0f);
		else if(RIGHT == direction) directionVector = MATH::Vector2(1.0f, 0.0f);

		if(_boost) {
			_emitter.SetDirection(MATH::Vector2(directionVector.x * -1.0f, 0.0f));
		}

		if(!_boost || _pushDirection != direction) {
			SetAcceleration(0.98f);
			SetVelocity(directionVector * 200.0f);
			_pushDirection = direction;
		}
	}

	Paddle::Paddle(Rules& rules) : Entity(rules) {
		_size = 5;
		_pushDirection = NONE;
		_boost = _bounceLeft = _bounceRight = false;

		_bodySprite = ImageManager::Instance().CreateSprite("res/brick.png");
		_leftCapSprite = ImageManager::Instance().CreateSprite("res/cap2.png");
		_rightCapSprite = ImageManager::Instance().CreateSprite("res/cap2.png");

		_bodySprite.Resize(PADDLE_WIDTH, PADDLE_HEIGHT);
		_leftCapSprite.Resize(PADDLE_WIDTH, PADDLE_HEIGHT);
		_rightCapSprite.Resize(PADDLE_WIDTH, PADDLE_HEIGHT);
		_rightCapSprite.FlipX(true);

		sf::Color color(232, 243, 255);
		_bodySprite.SetColor(color);
		_leftCapSprite.SetColor(color);
		_rightCapSprite.SetColor(color);

		SetPhysicsModel(PHY_TOUCHING | PHY_SOLID);
		SetCollisionModel(PHY_SOLID);

		SetBBox(MATH::BBox2(MATH::Vector2(0.0f, 0.0f),
			MATH::Vector2(PADDLE_WIDTH * _size, PADDLE_HEIGHT)));

		SetVelocity(MATH::Vector2(0.001f, 0.0f));
		SetMass(10000.0f);
	}

	void Paddle::TouchBoard(BoardSide side) {
		if(_boost) {
			if(LEFT == side) {
				_bounceLeft = true;
				_bounceLeftTimer = PADDLE_BOUNCE_DELAY;
				Push(RIGHT);
			}

			if(RIGHT == side) {
				_bounceRight = true;
				_bounceRightTimer = PADDLE_BOUNCE_DELAY;
				Push(LEFT);
			}

			_boost = false;
		} else {
			SetVelocity(MATH::Vector2(0.0f, 0.0f));
		}
	}

	void Paddle::Touch(ENT::Ball& ball, TouchInfo info) {
		if(ball.GetPosition().y <= GetPosition().y) {
			MATH::Vector2 ref = GetPosition() + MATH::Vector2(GetBBox().lowerRight.x / 2, 50.0f);
			MATH::Vector2 direction = MATH::Normalize(ball.GetPosition() - ref);
			ball.SetVelocity(ball.GetVelocity().Length() * direction);
		}
	}

	void Paddle::Input(const sf::Input& input, bool focus) {
		if(focus && input.IsJoystickButtonDown(0, 0)) {
			_boost = true;
			SetAcceleration(1.05f);
		} else {
			_boost = false;
			SetAcceleration(0.98f);
		}

		if(!_bounceLeft && -30.0f > input.GetJoystickAxis(0, sf::Joy::AxisX)) {
			Push(LEFT);
		}
		
		if(!_bounceRight && 30.0f < input.GetJoystickAxis(0, sf::Joy::AxisX)) {
			Push(RIGHT);
		}
	}

	void Paddle::Think(float secsPassed) {
		_emitter.Move(secsPassed);

		if(800.0f < GetVelocity().Length()) {
			SetVelocity(800.0f * MATH::Normalize(GetVelocity()));
		}

		if(_bounceLeft) {
			_bounceLeftTimer -= secsPassed;
			if(0.0f > _bounceLeftTimer)
				_bounceLeft = false;
		}

		if(_bounceRight) {
			_bounceRightTimer -= secsPassed;
			if(0.0f > _bounceRightTimer)
				_bounceRight = false;
		}
	}

	void Paddle::Draw(sf::RenderTarget& renderTarget) {
		_emitter.Draw(renderTarget);

		if(_boost) {
			_emitter.SetPosition(GetPosition() + 
				MATH::Vector2(PADDLE_WIDTH * _size * 0.5f, 16.0f));
			_emitter.Emit();
		}

		for(int i = 0; i < _size; ++i) {
			MATH::Vector2 position = GetPosition() + MATH::Vector2(PADDLE_WIDTH * i, 0);
			if(0 == i) {
				_leftCapSprite.SetPosition(position.sfVec());
				renderTarget.Draw(_leftCapSprite);
			} else if(_size - 1 == i) {
				_rightCapSprite.SetPosition(position.sfVec());
				renderTarget.Draw(_rightCapSprite);
			} else {
				_bodySprite.SetPosition(position.sfVec());
				renderTarget.Draw(_bodySprite);
			}
		}
	}

} // namespace ENT