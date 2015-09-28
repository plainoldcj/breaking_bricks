/*
file: gs_controls.cpp
*/

#include "image_manager.h"
#include "gs_controls.h"

GS_Controls::GS_Controls(Game& game) : Gamestate(game) {
	_sprite = ImageManager::Instance().CreateSprite("res/controls.png");
}

GS_Return GS_Controls::Move(float secsPassed, const sf::Input& input) {
	Gamestate::Move(secsPassed, input);

	if((GS_FOCUS & GetState()) && input.IsJoystickButtonDown(0, 3)) {
		return GS_POP;
	}

	return GS_NOP;
}

void GS_Controls::Draw(sf::RenderTarget& renderTarget) {
	renderTarget.Draw(_sprite);
}