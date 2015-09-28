/*
file: settings.h
*/

#pragma once

#include <sfml/graphics.hpp>

struct Settings {
	struct {
		sf::VideoMode videoMode;
		bool fullscreen;
	} video;
};

// return value 0 means client accepted, 1 client closed the dialog
int ShowSettingsDialog(Settings& settings);