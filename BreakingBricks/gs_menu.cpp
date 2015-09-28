/*
file: gs_menu.cpp
*/

#include "game_globals.h"
#include "image_manager.h"
#include "font_manager.h"
#include "gs_menu.h"

#include "gs_controls.h"
#include "gs_game.h"

char* GS_Menu::buttonCaptions[]  = {
	"play now!",
	"view Controls",
	"some motivation",
	"good bye"
};

GS_Menu::GS_Menu(Game& game) : Gamestate(game)
{
	_titleSprite = ImageManager::Instance().CreateSprite("res/title4.png");
	_titleSprite.SetCenter(_titleSprite.GetSize().x / 2,
				_titleSprite.GetSize().y / 2);
	_titleSprite.SetPosition(sf::Vector2f(VSCREEN_WIDTH / 2.0f, 200.0f));

	_button.SetFont(FontManager::Instance().GetFont("res/menu_font.ttf"));
	_button.SetSize(50);

	_selectedButton = 0;
	_timePassed = 0.0f;
	_receivesInput = true;
}

statePtr_t GS_Menu::GetNextState(void) {
	if(MB_CONTROLS == _selectedButton) {
		return statePtr_t(new GS_Controls(GetGame()));
	}
	return statePtr_t(new GS_Game(GetGame()));
}

void GS_Menu::Draw(sf::RenderTarget& renderTarget)
{
	renderTarget.Draw(_titleSprite);

	float tri = abs(sinf(_timePassed * 5.0f));
	for(int i = 0; i < MB_SIZE; ++i)
	{
		_button.SetText(buttonCaptions[i]);
		_button.SetCenter(_button.GetRect().GetWidth() / 2,
			_button.GetRect().GetHeight() / 2);
		_button.SetPosition(VSCREEN_WIDTH / 2.0f, 400.0f + i * 50.0f);
		if(_selectedButton == i)
		{
			_button.SetColor(sf::Color(0, 0, 0, 200));
			_button.SetScale(tri / 5.0f + 1.0f, tri / 10.0f + 1.0f);
		}
		renderTarget.Draw(_button);
		_button.SetScale(1.0f, 1.0f);
		_button.SetColor(sf::Color(255, 255, 255, 200));
	}
}

GS_Return GS_Menu::Move(float secsPassed, const sf::Input& input)
{
	Gamestate::Move(secsPassed, input);

	if((GS_FOCUS & GetState()) && 
		(input.IsKeyDown(sf::Key::Return) || 
		input.IsJoystickButtonDown(0, 0)))
	{
		if(MB_EXIT == _selectedButton) {
			return GS_POP;
		}
		if(MB_CONTROLS == _selectedButton) {
			return GS_PUSH;
		}
		return GS_REPLACE;
	}

	if(_receivesInput)
	{
		if(input.IsKeyDown(sf::Key::Up) || -50.0f > input.GetJoystickAxis(0, sf::Joy::AxisY)) 
		{
			_receivesInput = false;
			_selectedButton--;
		}
		if(input.IsKeyDown(sf::Key::Down) || 50.0f < input.GetJoystickAxis(0, sf::Joy::AxisY)) 
		{
			_receivesInput = false;
			_selectedButton++;
		}
		if(MB_SIZE <= _selectedButton) _selectedButton = MB_SIZE - 1;
		if(0 > _selectedButton) _selectedButton = 0;
		_delayInput = 0.0f;
	}
	else
	{
		_delayInput += secsPassed;
		if(0.2f < _delayInput)
			_receivesInput = true;
	}

	float tri = abs(sinf(_timePassed));
	_titleSprite.SetScale(tri / 5.0f + 0.7f, tri / 10.0f + 0.7f);
	unsigned char alpha = static_cast<unsigned char>(150.0f * tri) + 105;
	_titleSprite.SetColor(sf::Color(255, 255, 255, alpha));

	_timePassed += secsPassed;
	
	return GS_NOP;
}