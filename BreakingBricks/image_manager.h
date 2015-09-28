/*
file: image_manager.h
*/

#pragma once

#include <string>
#include <map>
#include <sfml/graphics.hpp>
#include "util_singleton.h"

class ImageManager : public UTIL::Singleton<ImageManager> {
private:
	typedef std::map<std::string, sf::Image> imageMap_t;
	typedef imageMap_t::iterator imageMapIt_t;

	imageMap_t _images;
public:
	sf::Sprite CreateSprite(const std::string& filename,
		const sf::Vector2f& position = sf::Vector2f(0.0f, 0.0f),
		const sf::Vector2f& scale = sf::Vector2f(1.0f, 1.0f),
		float rotation = 0.0f,
		const sf::Color& color = sf::Color(255, 255, 255, 255));
};