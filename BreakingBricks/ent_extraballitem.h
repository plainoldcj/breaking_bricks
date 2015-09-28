/*
file: ent_extraballitem.h
*/

#pragma once

#include "entity.h"

#define ITEM_WIDTH 50
#define ITEM_HEIGHT 32

namespace ENT {

	class ExtraBallItem : public Entity {
	private:
		sf::Sprite _itemSprite;
	public:
		ExtraBallItem(Rules& rules);

		void Touch(Entity& entity, TouchInfo info) {
			entity.Touch(*this, info);
		}

		void Touch(ENT::Paddle& paddle, TouchInfo info);

		void Think(float secsPassed);
		void Draw(sf::RenderTarget& renderTarget);
	};

} // namespace ENT