/*
file: game.h
*/

#pragma once

#include <vector>
#include <string>
#include <list>
#include <boost/shared_ptr.hpp>
#include "gamestate.h"
#include "background.h"

typedef std::vector<std::string>::iterator levelNameIt_t;

class Game {
private:
	sf::View _view;
	Background _background;
	std::list<statePtr_t> _states;
	bool _running;

	std::vector<std::string> _levelList;
public:
	Game(sf::RenderTarget& renderTarget);

	bool IsRunning(void) const { return _running; }

	void ReadLevelList(void);
	levelNameIt_t GetLevelIterator(void);
	levelNameIt_t GetNextLevelIterator(levelNameIt_t currentLevel);

	void Move(float secsPassed, const sf::Input& input);
	void Draw(sf::RenderTarget& renderTarget);
};