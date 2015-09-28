/*
file: gs_game.cpp
*/

#include "util_tostring.h"
#include "game_globals.h"
#include "gs_game.h"
#include "ent_ball.h"
#include "gs_info.h"
#include "gs_menu.h"

GS_Game::GS_Game(Game& game) : Gamestate(game) {
	_levelCount = 0;

	_levelNameIt = game.GetLevelIterator();

	Entity::Apocalypse();
	LoadLevel();
	StartLevel();
}

statePtr_t GS_Game::GetNextState(void) {
	if(!_showInfo) {
		_showInfo = true;
		std::string info("Level " + UTIL::ToString<int>::Type(_levelCount));
		return statePtr_t(new GS_Info(GetGame(), info));
	}

	if(_gameLost) {
		// TODO
		return statePtr_t(new GS_Menu(GetGame()));
	}

	return statePtr_t(new GS_Menu(GetGame()));
}

GS_Return GS_Game::Move(float secsPassed, const sf::Input& input) {
	Gamestate::Move(secsPassed, input);

	if(!_showInfo) {
		return GS_PUSH;
	}

	if((GS_FOCUS & GetState()) && input.IsJoystickButtonDown(0, 3)) {
		return GS_REPLACE;
	}

	_floatingFrame.Move(secsPassed);

	Entity::UpdateWorldPhysic(secsPassed);
	Entity::UpdateWorldLogic(secsPassed, input, GS_FOCUS & GetState());

	if(GS_FOCUS & GetState() && input.IsJoystickButtonDown(0, 0)) {
		_paddle->DetachAll();
	}

	if(0 == _rules.numBlocks) {
		Entity::Apocalypse();
		_levelNameIt = GetGame().GetNextLevelIterator(_levelNameIt);
		LoadLevel();
		StartLevel();
	}

	if(!_gameLost && 0 >= _rules.numBalls) {
		_gameLost = true;
		return GS_REPLACE;
	}

	return GS_NOP;
}

void GS_Game::Draw(sf::RenderTarget& renderTarget) {
	_floatingFrame.Draw(renderTarget);

	Entity::DrawWorld(renderTarget);
}