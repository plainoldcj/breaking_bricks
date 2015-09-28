/*
file: ent_extraballitem.cpp
*/

#include "image_manager.h"
#include "ent_ball.h"
#include "ent_paddle.h"
#include "ent_extraballitem.h"

namespace ENT {

	ExtraBallItem::ExtraBallItem(Rules& rules) : Entity(rules) {
		_itemSprite = ImageManager::Instance().CreateSprite("res/item_extraball.png");
		_itemSprite.Resize(ITEM_WIDTH, ITEM_HEIGHT);

		SetBBox(MATH::BBox2(MATH::Vector2(0.0f, 0.0f),
			MATH::Vector2(ITEM_WIDTH, ITEM_HEIGHT)));

		SetAcceleration(1.0f);
		SetVelocity(MATH::Vector2(0.0f, 1.0f) * 100.0f);
		SetMass(1.0f);

		SetPhysicsModel(PHY_TOUCHING | PHY_GHOST);
		SetCollisionModel(PHY_GHOST);
	}

	void ExtraBallItem::Touch(Paddle& paddle, TouchInfo info) {
		SetPhysicsModel(PHY_GHOST);
		SetCollisionModel(PHY_GHOST);
		Die();

		entPtr_t ball = entPtr_t(new ENT::Ball(GetRules()));
		ball->SetPosition(paddle.GetPosition() + 
				MATH::Vector2((paddle.GetBBox().lowerRight.x / 2.0f) - (BALL_SIZE / 2.0f), 
				-(BALL_SIZE + 1.0f)));
		Entity::LinkToWorld(ball);

		paddle.AttachEntity(ball);
	}

	void ExtraBallItem::Think(float secsPassed) {
	}

	void ExtraBallItem::Draw(sf::RenderTarget& renderTarget) {
		_itemSprite.SetPosition(GetPosition().sfVec());
		renderTarget.Draw(_itemSprite);
	}

} // namespace ENT