/*
file: gs_game.h
*/

#pragma once

#include <string>
#include "game.h"
#include "entity.h"
#include "floating_frame.h"
#include "gamestate.h"

struct Rules {
	int numBlocks;
	int numBalls;
};

class GS_Game : public Gamestate {
private:
	FloatingFrame _floatingFrame;
	entPtr_t _ball;
	entPtr_t _paddle;

	Rules _rules;

	bool _showInfo;
	bool _gameLost;

	int _levelCount;
	levelNameIt_t _levelNameIt;
public:
	GS_Game(Game& game);

	void LoadLevel(void);
	void StartLevel(void);

	statePtr_t GetNextState(void);

	GS_Return Move(float secsPassed, const sf::Input& input);
	void Draw(sf::RenderTarget& renderTarget);
};