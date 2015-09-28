/*
file: gs_menu.h
*/

#pragma once

#include <vector>
#include "gamestate.h"

class GS_Menu : public Gamestate
{
private:
	enum MenuButtons {
		MB_PLAY = 0,
		MB_CONTROLS,
		MB_SCORES,
		MB_EXIT,
		MB_SIZE
	};

	static char* buttonCaptions[];

	float _timePassed;
	sf::Sprite _titleSprite;
	sf::String _button;
	int _selectedButton;
	bool _receivesInput;
	int _oldMouseY;
	float _delayInput;
public:
	GS_Menu(Game& game);
	
	statePtr_t GetNextState(void);

	void Draw(sf::RenderTarget& renderTarget);
	GS_Return Move(float secsPassed, const sf::Input& input);
};