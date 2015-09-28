/*
file: gamestate.h
*/

#pragma once

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <sfml/graphics.hpp>

enum GS_State {
	GS_FOCUS	= 1,
	GS_ACTIVE	= 2,
	GS_FADEIN	= 4,
	GS_FADEOUT	= 8,
	GS_DEAD		= 16
};

enum GS_Return {
	GS_PUSH = 0,
	GS_POP,
	GS_REPLACE,
	GS_NOP
};

class Game;
class Gamestate;

typedef boost::shared_ptr<Gamestate> statePtr_t;

class Gamestate : private boost::noncopyable {
private:
	int _state;
	float _viewOffset;
	sf::View _view;
protected:
	Game& _game;
public:
	Gamestate(Game& game);
	virtual ~Gamestate(void) { }

	Game& GetGame(void);

	sf::View& GetView(void);

	void SetState(int state);
	int GetState(void) const { return _state; }

	// convenient methods
	void Focus(void);
	void Unfocus(void);

	virtual void StateChanged(int state);
	virtual statePtr_t GetNextState(void) { return statePtr_t(); }

	virtual GS_Return Move(float secsPassed, const sf::Input& input) = 0;
	virtual void Draw(sf::RenderTarget& renderTarget) = 0;
};