/*
file: gamestate.cpp
*/

#include "game_globals.h"
#include "gamestate.h"

Gamestate::Gamestate(Game& game) : _game(game) {
	_state = GS_FADEIN;
	_view = sf::View(sf::FloatRect(0, 0, VSCREEN_WIDTH, VSCREEN_HEIGHT));
}

Game& Gamestate::GetGame(void) {
	return _game;
}

sf::View& Gamestate::GetView(void) {
	return _view;
}

void Gamestate::SetState(int state) {
	_state = state;
	StateChanged(state);
}

void Gamestate::StateChanged(int state) {
	if(GS_FADEOUT & _state) {
		_viewOffset = VSCREEN_HEIGHT;
	}
	if(GS_FADEIN & _state) {
		_viewOffset = VSCREEN_HEIGHT;
		_view = sf::View(sf::FloatRect(0, 0, VSCREEN_WIDTH, VSCREEN_HEIGHT));
		_view.Move(sf::Vector2f(0.0f, VSCREEN_HEIGHT));
	}
	/*
	if(GS_ACTIVE & _state) {
		_view = sf::View(sf::FloatRect(0, 0, VSCREEN_WIDTH, VSCREEN_HEIGHT));
	}
	*/
}

void Gamestate::Focus(void) {
	_state |= GS_FOCUS;
	StateChanged(_state);
}

void Gamestate::Unfocus(void) {
	_state &= ~GS_FOCUS;
	StateChanged(_state);
}

GS_Return Gamestate::Move(float secsPassed, const sf::Input& input) {
	if(GS_FADEOUT & _state) {
		float diff = -600.0f * secsPassed;
		_viewOffset += diff;
		_view.Move(sf::Vector2f(0.0f, diff));
		if(_viewOffset <= 0.0f) {
			_state = GS_DEAD;
		}
	}
	if(GS_FADEIN & _state) {
		float diff = -600.0f * secsPassed;
		_viewOffset += diff;
		_view.Move(sf::Vector2f(0.0f, diff));
		if(_viewOffset <= 0.0f) {
			_state = GS_ACTIVE;
		}
	}
	return GS_NOP;
}