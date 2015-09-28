/*
file: gs_info.cpp
*/

#include "game_globals.h"
#include "math_vector2.h"
#include "font_manager.h"
#include "gs_info.h"

GS_Info::GS_Info(Game& game, const std::string& info) : Gamestate(game), _info(info) {
	MATH::Vector2 framePoints[] = {
		MATH::Vector2(-20, 10),
		MATH::Vector2(20, 10),
		MATH::Vector2(20, -10),
		MATH::Vector2(-20, -10)
	};

	_timePassed = 0.0f;

	sf::Font& font = FontManager::Instance().GetFont("res/menu_font.ttf");
	_info.SetFont(font);
	_info.SetSize(150.0f);
	_info.SetText(info.c_str());

	sf::FloatRect rect = _info.GetRect();
	MATH::Vector2 handle = 0.5f * MATH::Vector2(rect.GetWidth(), rect.GetHeight());
	_info.SetCenter(handle.sfVec());
	MATH::Vector2 position =
		0.5f * MATH::Vector2(VSCREEN_WIDTH, VSCREEN_HEIGHT);
	_info.SetPosition(position.sfVec());

	MATH::Vector2 center(0.0f, 0.0f);

	for(int i = 0; i < 4; ++i) {
		framePoints[i] = (framePoints[i] - center) * sf::Randomizer::Random(10.0f, 20.0f);
		_frame.AddPoint(framePoints[i].sfVec(), sf::Color(0, 0, 0, 150));
	}

	_frame.SetPosition(VSCREEN_WIDTH / 2.0f, VSCREEN_HEIGHT / 2.0f);
}

GS_Return GS_Info::Move(float secsPassed, const sf::Input& input) {
	Gamestate::Move(secsPassed, input);

	if((GS_FOCUS & GetState()) && input.IsJoystickButtonDown(0, 3)) {
		return GS_POP;
	}

	_timePassed += secsPassed;

	return GS_NOP;
}

void GS_Info::Draw(sf::RenderTarget& renderTarget) {
	renderTarget.Draw(_frame);
	float tri = abs(sinf(_timePassed * 5.0f));
	_info.SetScale(tri / 5.0f + 1.0f, tri / 10.0f + 1.0f);
	renderTarget.Draw(_info);
}