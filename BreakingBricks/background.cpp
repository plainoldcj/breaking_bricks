/*
file: background.cpp
*/

#include "game_globals.h"
#include "image_manager.h"
#include "background.h"

Background::Background(void) {
	_sprite = ImageManager::Instance().CreateSprite("res/background2.png");
	_width = _sprite.GetImage()->GetWidth();
	_height = _sprite.GetImage()->GetHeight();
	_offset = -1.0f * _height;
	_repeatX = (VSCREEN_WIDTH / _width) + (VSCREEN_WIDTH % _width);
	_repeatY = (VSCREEN_HEIGHT / _height) + (VSCREEN_HEIGHT % _height) + 1;
}

void Background::Move(float secsPassed) {
	_offset += 20.0f * secsPassed;
	if(_offset > _height)
		_offset = 0.0f;
}

void Background::Draw(sf::RenderTarget& renderTarget) {
	for(int x = 0; x < _repeatX; ++x) {
		for(int y = -_height; y < _repeatY; ++y) {
			sf::Vector2f position(0.0f + x * _width, y * _height + _offset);
			_sprite.SetPosition(position);
			renderTarget.Draw(_sprite);
		}
	}
}