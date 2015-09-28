/*
file: ent_paddle.h
*/

#pragma once

#include "boost_emitter.h"
#include "entity.h"

#define PADDLE_WIDTH 32
#define PADDLE_HEIGHT 32

#define PADDLE_BOUNCE_DELAY 0.2f

namespace ENT {

	class Paddle : public Entity {
	private:
		enum Direction { LEFT, RIGHT, NONE, BOOST };

		int _size;
		sf::Sprite _bodySprite;
		sf::Sprite _leftCapSprite;
		sf::Sprite _rightCapSprite;

		Direction _pushDirection;
		bool _boost;

		bool _bounceLeft;
		float _bounceLeftTimer;
		bool _bounceRight;
		float _bounceRightTimer;

		BoostEmitter _emitter;

		void Push(Direction direction);
	public:
		Paddle(Rules& rules);

		void AttachBall(void);

		void Touch(Entity& entity, TouchInfo info) { 
			entity.Touch(*this, info); 
		}
		void Touch(ENT::Ball& ball, TouchInfo info);

		void TouchBoard(BoardSide side);
		void Input(const sf::Input& input, bool focus);
		void Think(float secsPassed);
		void Draw(sf::RenderTarget& renderTarget);
	};

} // namespace ENT