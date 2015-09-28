/*
file: physics.cpp
*/

#include "game_globals.h"
#include "entity.h"

#define DELTA_TIME 0.01f

void Entity::UpdateWorldPhysic(float secsPassed) {
	while(secsPassed > 0.0f) {
		for(entIt_t entIt(entities.begin());
			entIt != entities.end(); ++entIt) {
				entPtr_t entity = *entIt;
				entity->TestCollision(DELTA_TIME);
		}
		for(entIt_t entIt(entities.begin());
			entIt != entities.end(); ++entIt) {
				entPtr_t entity = *entIt;
				entity->Move(DELTA_TIME);
		}
		secsPassed -= DELTA_TIME;
	}
}

void Entity::TestCollision(float secsPassed) {
	_blocked = false;

	MATH::Vector2 predictedPosition = _position + _velocity * secsPassed;
	MATH::Vector2 predictedVelocity = _velocity * _acceleration;
	
	MATH::BBox2 transformed = _bbox;
	transformed.upperLeft += predictedPosition;
	transformed.lowerRight += predictedPosition;

	if(PHY_SOLID & _physicsModel) {

		// TEST COLLISION WITH BOARD

		if(BOARD_OFFSET_X > transformed.upperLeft.x) {
			_blocked = true;
			_velocity.x *= -1.0f;
			TouchBoard(LEFT);
		}

		if(BOARD_OFFSET_X + BOARD_WIDTH < transformed.lowerRight.x) {
			_blocked = true;
			_velocity.x *= -1.0f;
			TouchBoard(RIGHT);
		}

		if(BOARD_OFFSET_Y > transformed.upperLeft.y) {
			_blocked = true;
			_velocity.y *= -1.0f;
			TouchBoard(TOP);
		}

		if(BOARD_OFFSET_Y + BOARD_HEIGHT < transformed.lowerRight.y) {
			_blocked = true;
			_velocity.y *= -1.0f;
			TouchBoard(BOTTOM);
		}

	} // if bounded

	// TEST COLLISION WITH SOLID ENTITIES

	if(PHY_TOUCHING & _physicsModel) {
		bool touching = false;

		for(entIt_t entIt(entities.begin()); entities.end() != entIt; ++entIt) {
			entPtr_t entity = *entIt;
			if(GetID() == entity->GetID()) continue;
			if(PHY_GHOST & entity->_collisionModel) continue;
			if((_physicsMask & entity->_physicsMask) > 0) continue;

			MATH::BBox2 otherTransformed = entity->_bbox;
			otherTransformed.upperLeft += entity->_position;
			otherTransformed.lowerRight += entity->_position;

			/*
			to future me: in case you are asking yourself "WTF?":
			this is basically SAT with exploiting the fact that
			we only have axes aligned bounding boxes,
			so we dont have to deal with projecting shit.
			*/
			float cutX, cutY;
			if(MATH::Overlaps(transformed, otherTransformed, cutX, cutY)) {
				float m1 = _mass;
				float m2 = entity->_mass;

				touching = true;

				if(_spawned) { // && (PHY_SOLID & _physicsModel)) {
					TouchInfo info;
					
					if(PHY_SOLID & _physicsModel) {
						if(cutX > cutY) {
							float v1 = predictedVelocity.y;
							float v2 = entity->_velocity.y;
							
							float v1s = (m1 * v1 + m2 * (2.0f * v2 - v1)) / (m1 + m2);
							float v2s = (m2 * v2 + m1 * (2.0f * v1 - v2)) / (m1 + m2);

							if(PHY_BOUNCING & _physicsModel) _velocity.y = v1s;
							if(PHY_BOUNCING & entity->_physicsModel) entity->_velocity.y = v2s;
						} else {
							float v1 = predictedVelocity.x;
							float v2 = entity->_velocity.x;
							
							float v1s = (m1 * v1 + m2 * (2.0f * v2 - v1)) / (m1 + m2);
							float v2s = (m2 * v2 + m1 * (2.0f * v1 - v2)) / (m1 + m2);

							if(PHY_BOUNCING & _physicsModel) _velocity.x = v1s;
							if(PHY_BOUNCING & entity->_physicsModel) entity->_velocity.x = v2s;
						}
						_blocked = true;

						info.cutX = cutX;
						info.cutY = cutY;
					}

					Touch(*entity, info);
					entity->Touch(*this, info);
				}
			}
		}

		if(!_spawned) _spawned = !touching;
	} // if touching

	if((PHY_SOLID & _physicsModel || PHY_GHOST & _physicsModel) && !_blocked) {
		_position += _velocity * secsPassed;
		_velocity *= _acceleration;
	}
}

// TODO: remove me
void Entity::Move(float secsPassed) {
	for(std::list<ChildInfo>::iterator childIt(_childs.begin());
		childIt != _childs.end(); ++childIt) {
		childIt->entity->_position = _position + childIt->relativePos;
	}
}