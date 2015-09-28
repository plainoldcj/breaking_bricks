/*
file: entity.cpp
*/

#include "entity.h"

int Entity::idCount = 0;
std::list<entPtr_t> Entity::entities;

void Entity::Apocalypse(void) {
	entities.clear();
}

void Entity::UpdateWorldLogic(float secsPassed, const sf::Input& input, bool focus) {
	for(entIt_t entIt(entities.begin());
		entIt != entities.end(); ++entIt) {
			entPtr_t entity = *entIt;
			if(entity->IsDead()) {
				entIt = entities.erase(entIt);
				if(entIt == entities.end()) break;
			} else {
				entity->Input(input, focus);
				entity->Think(secsPassed);
			}
	}
}

void Entity::DrawWorld(sf::RenderTarget& renderTarget) {
	for(entIt_t entIt(entities.begin());
		entIt != entities.end(); ++entIt) {
			(*entIt)->Draw(renderTarget);
	}
}

void Entity::LinkToWorld(entPtr_t entity) {
	entities.push_back(entity);
}

Entity::Entity(Rules& rules) : _rules(rules) {
	_spawned = false;
	_physicsMask = 0;
	_isDead = false;
	_id = idCount++;
}

Rules& Entity::GetRules(void) {
	return _rules;
}

void Entity::AttachEntity(entPtr_t entity) {
	ChildInfo info(entity, entity->_position - _position);
	info.collisionModel = entity->_collisionModel;
	info.physicsModel = entity->_physicsModel;
	entity->_physicsModel = entity->_collisionModel = PHY_GHOST;
	entity->_spawned = false;
	_childs.push_back(info);
}

void Entity::DetachEntity(entPtr_t entity) {
	for(std::list<ChildInfo>::iterator childIt(_childs.begin());
		childIt != _childs.end(); ++childIt) {
			if(entity->GetID() == childIt->entity->GetID()) {
				childIt->entity->_collisionModel =
					childIt->collisionModel;
				childIt->entity->_physicsModel =
					childIt->physicsModel;
				_childs.erase(childIt);
				return;
			}
	}
}

void Entity::DetachAll(void) {
	for(std::list<ChildInfo>::iterator childIt(_childs.begin());
		childIt != _childs.end(); ++childIt) {
			childIt->entity->_collisionModel =
				childIt->collisionModel;
			childIt->entity->_physicsModel =
				childIt->physicsModel;
	}
	_childs.clear();
}

void Entity::Die(void) {
	_isDead = true;
}

bool Entity::IsDead(void) const {
	return _isDead;
}

int Entity::GetID(void) const {
	return _id;
}

void Entity::SetBBox(const MATH::BBox2& bbox) {
	_bbox = bbox;
}

void Entity::SetPhysicsMask(int mask) {
	_physicsMask = mask;
}

void Entity::SetPhysicsModel(int model) {
	_physicsModel = model;
}

void Entity::SetCollisionModel(int model) {
	_collisionModel = model;
}

void Entity::SetPosition(const MATH::Vector2& position) {
	_position = position;
}

void Entity::SetAcceleration(float acceleration) {
	_acceleration = acceleration;
}

void Entity::SetVelocity(const MATH::Vector2& velocity) {
	_velocity = velocity;
}

void Entity::SetMass(float mass) {
	_mass = mass;
}

const MATH::Vector2& Entity::GetPosition(void) const {
	return _position;
}

const MATH::Vector2& Entity::GetVelocity(void) const {
	return _velocity;
}

const MATH::BBox2& Entity::GetBBox(void) const {
	return _bbox;
}