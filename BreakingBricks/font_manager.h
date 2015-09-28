/*
file: font_manager.h
*/

#pragma once

#include <string>
#include <map>
#include <sfml/graphics.hpp>
#include "util_singleton.h"

class FontManager : public UTIL::Singleton<FontManager> {
private:
	typedef std::map<std::string, sf::Font> fontMap_t;
	typedef fontMap_t::iterator fontMapIt_t;

	fontMap_t _fonts;
	sf::Uint32 _charset[191];
public:
	FontManager(void);

	sf::Font& GetFont(const std::string& filename);
};