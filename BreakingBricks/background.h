/*
file: background.h
*/

#pragma once

#include <boost/noncopyable.hpp>
#include <sfml/graphics.hpp>

class Background : private boost::noncopyable {
private:
	sf::Sprite _sprite;
	int _repeatX, _repeatY;
	int _width, _height;
	float _offset;
public:
	Background(void);

	void Move(float secsPassed);
	void Draw(sf::RenderTarget& renderTarget);
};