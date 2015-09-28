/*
file: ent_ball.h
*/

#pragma once

#include "sound_manager.h"
#include "blur_emitter.h"
#include "bounce_emitter.h"
#include "entity.h"

#define BALL_SIZE 32.0f

namespace ENT {

	class Ball : public Entity {
	private:
		soundPtr_t _scoreSound;
		soundPtr_t _bounceSound;
		sf::Sprite _ballSprite;
		bool _ignited;
		BounceEmitter _emitter;
		BlurEmitter _blur;

		bool _dying;
		float _health;
		float _decayRate;

		void TouchEffects(void);
	public:
		Ball(Rules& rules);

		void Ignite(void);

		void Touch(Entity& entity, TouchInfo info) { 
			entity.Touch(*this, info); 
		}

		void Touch(ENT::Block& block, TouchInfo info);
		void Touch(ENT::Paddle& paddle, TouchInfo info);

		void TouchBoard(BoardSide side);
		void Think(float secsPassed);
		void Draw(sf::RenderTarget& renderTarget);
	};

} // namespace ENT