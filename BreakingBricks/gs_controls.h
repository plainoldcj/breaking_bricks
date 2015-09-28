/*
file: gs_controls.h
*/

#pragma once

#include "gamestate.h"

class GS_Controls : public Gamestate {
private:
	sf::Sprite _sprite;
public:
	GS_Controls(Game& game);

	GS_Return Move(float secsPassed, const sf::Input& input);
	void Draw(sf::RenderTarget& renderTarget);
};