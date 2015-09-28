/*
file: ent_block.cpp
*/

#include "math2.h"
#include "gs_game.h"
#include "image_manager.h"
#include "ent_extraballitem.h"
#include "ent_ball.h"
#include "ent_block.h"

namespace ENT {

	Block::Block(Rules& rules, const sf::Color& color, int health) : Entity(rules) {
		_highlight = false;
		_highlightPhase = 0.0f;

		_drop = false;
		_health = health;
		_decay = 1.0f;
		_rotation = 0.0f;
		_angularVelocity = 0.0f;

		_color = color;

		_blockSprite = ImageManager::Instance().CreateSprite("res/brick.png");
		_blockSprite.Resize(BLOCK_WIDTH, BLOCK_HEIGHT);
		_blockSprite.SetColor(_color);

		SetBBox(MATH::BBox2(MATH::Vector2(0.0f, 0.0f),
			MATH::Vector2(BLOCK_WIDTH, BLOCK_HEIGHT)));

		SetPhysicsModel(PHY_GHOST);
		SetCollisionModel(PHY_SOLID);

		SetAcceleration(1.0f);
		SetVelocity(MATH::Vector2(0.0f, 0.0f));
		SetMass(100000.0f);
	}

	void Block::Touch(ENT::Ball& ball, TouchInfo info) {
		_health--;
		if(0 >= _health) {
			SetCollisionModel(PHY_GHOST);
			SetVelocity(MATH::Vector2(0.0f, 100.0f));
			_angularVelocity = sf::Randomizer::Random(5.0f, 10.0f);
			_drop = true;

			GetRules().numBlocks--;

			// TODO
			int r = rand() % 50;
			if(r <= 3) {
				entPtr_t item = entPtr_t(new ENT::ExtraBallItem(GetRules()));
				item->SetPosition(GetPosition());
				Entity::LinkToWorld(item);
			}
		} 

		_highlight = true;
		_highlightPhase = 0.0f;
	}

	void Block::Think(float secsPassed) {
		if(_drop) {
			_rotation = _angularVelocity * secsPassed;
			_blockSprite.Rotate(_rotation);

			_color.a = 255 * _decay;
			_blockSprite.SetColor(_color);
			_decay -= 1.0f * secsPassed;

			if(0.0f > _decay) {
				Die();
			}
		}

		if(_highlight) {
			_highlightPhase += 10.0f * secsPassed;
			if(M_PI < _highlightPhase) {
				_highlight = false;
				_blockSprite.SetColor(_color);
			}
		}
	}

	void Block::Draw(sf::RenderTarget& renderTarget) {
		MATH::Vector2 position = GetPosition();

		if(_highlight) {
			_blockSprite.SetColor(_color + sf::Color(255, 255, 255, 255 * sinf(_highlightPhase)));
			position -= MATH::Vector2(0.0f, 5.0f * sinf(_highlightPhase));
		}

		_blockSprite.SetPosition(position.sfVec());
		renderTarget.Draw(_blockSprite);
	}

} // namespace ENT