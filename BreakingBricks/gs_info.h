/*
file: gs_info.h
*/

#pragma once

#include <string>
#include "gamestate.h"

class GS_Info : public Gamestate {
private:
	sf::String _info;
	sf::Shape _frame;
	float _timePassed;
public:
	GS_Info(Game& game, const std::string& info);

	GS_Return Move(float secsPassed, const sf::Input& input);
	void Draw(sf::RenderTarget& renderTarget);
};