/*
file: ent_block.h
*/

#pragma once

#include "entity.h"

#define BLOCK_WIDTH 100
#define BLOCK_HEIGHT 16

namespace ENT {

	class Block : public Entity {
	private:
		sf::Sprite _blockSprite;
		sf::Color _color;

		bool _highlight;
		float _highlightPhase;
			
		bool _drop;
		int _health;
		float _decay;
		float _angularVelocity;
		float _rotation;
	public:
		Block(Rules& rules, const sf::Color& color, int health);

		void Touch(Entity& entity, TouchInfo info) { 
			entity.Touch(*this, info); 
		}
		void Touch(ENT::Ball& ball, TouchInfo info);

		void Think(float secsPassed);
		void Draw(sf::RenderTarget& renderTarget);
	};

} // namespace ENT