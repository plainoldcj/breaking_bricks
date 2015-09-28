/*
file: entity.h
*/

#pragma once

#include <list>
#include <boost/shared_ptr.hpp>
#include "math_vector2.h"
#include "math_bbox2.h"

#define PHY_SOLID		1
#define PHY_GHOST		2
#define PHY_TOUCHING	4
#define PHY_BOUNCING	8

#define PHY_MASK(x) (1 << x)

struct Rules;
class Entity;

namespace ENT {
	class Paddle;
	class Block;
	class Ball;
	class ExtraBallItem;
}

typedef boost::shared_ptr<Entity> entPtr_t;

enum BoardSide {
	LEFT = 0,
	RIGHT,
	TOP,
	BOTTOM
};

class Entity {
protected:
	typedef std::list<entPtr_t>::iterator entIt_t;
private:
	int _id;

	bool _isDead;

	bool _spawned;

	int _physicsMask;
	int _physicsModel;
	int _collisionModel;
	MATH::BBox2 _bbox;
	MATH::Vector2 _position;
	MATH::Vector2 _velocity;
	float _acceleration;
	float _mass;
	bool _blocked;

	struct ChildInfo {
		entPtr_t entity;
		MATH::Vector2 relativePos;
		int physicsModel;
		int collisionModel;

		ChildInfo(entPtr_t entity, const MATH::Vector2& relativePos)
			: entity(entity), relativePos(relativePos) { }
	};
	std::list<ChildInfo> _childs;

	Rules& _rules;

	static int idCount;
	static std::list<entPtr_t> entities;
public:
	Entity(Rules& rules);
	virtual ~Entity(void) { }

	static void Apocalypse(void);
	static void LinkToWorld(entPtr_t entity);
	static void UpdateWorldPhysic(float secsPassed);
	static void UpdateWorldLogic(float secsPassed, const sf::Input& input, bool focus);
	static void DrawWorld(sf::RenderTarget& renderTarget);

	void AttachEntity(entPtr_t entity);
	void DetachEntity(entPtr_t entity);
	void DetachAll(void);

	Rules& GetRules(void);

	void Die(void);
	bool IsDead(void) const;

	int GetID(void) const;

	// TODO: merge these two methods
	void TestCollision(float secsPassed);
	void Move(float secsPassed);

	void SetPhysicsMask(int mask);
	void SetPhysicsModel(int model);
	void SetCollisionModel(int model);

	void SetBBox(const MATH::BBox2& bbox);
	void SetPosition(const MATH::Vector2& position);
	void SetAcceleration(float acceleration);
	void SetVelocity(const MATH::Vector2& velocity);
	void SetMass(float mass);

	const MATH::Vector2& GetPosition(void) const;
	const MATH::Vector2& GetVelocity(void) const;
	const MATH::BBox2& GetBBox(void) const;

	// SUBCLASSES OVERLOAD THIS

	struct TouchInfo {
		float cutX;
		float cutY;
	};

	virtual void Touch(Entity& entity, TouchInfo info) = 0;
	virtual void Touch(ENT::Paddle& paddle, TouchInfo info) { }
	virtual void Touch(ENT::Ball& ball, TouchInfo info) { }
	virtual void Touch(ENT::Block& block, TouchInfo info) { }
	virtual void Touch(ENT::ExtraBallItem& item, TouchInfo info) { }

	virtual void TouchBoard(BoardSide side) { }
	virtual void Input(const sf::Input& input, bool focus) { }
	virtual void Think(float secsPassed) { }
	virtual void Draw(sf::RenderTarget& renderTarget) { }
};