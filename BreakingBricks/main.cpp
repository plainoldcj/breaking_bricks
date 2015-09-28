/*
file: main.cpp
*/

#define DEV

#define SFML_DYNAMIC

#pragma comment(lib, "fmodex_vc.lib")
#pragma comment(lib, "xinput.lib")
#ifdef _DEBUG
	#pragma comment(lib, "sfml-system-d.lib")
	#pragma comment(lib, "sfml-window-d.lib")
	#pragma comment(lib, "sfml-graphics-d.lib")
#else
	#pragma comment(lib, "sfml-system.lib")
	#pragma comment(lib, "sfml-window.lib")
	#pragma comment(lib, "sfml-graphics.lib")
#endif

#include <windows.h>
#include <sfml/graphics.hpp>
#include "log.h"
#include "settings.h"
#include "game_globals.h"
#include "game.h"

const TCHAR* logErrorMessage = 
TEXT("unable to create logfile. in case the program crashes,\n \
the logfile containes important information to find the\n \
reason for the crash. so make sure you have write access\n \
on the drive you are running this application from.");

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd) 
{
	Log& log = Log::Instance();
	if(!log.IsOpen()) {
		MessageBox(NULL, logErrorMessage, TEXT("Warning"), MB_OK);
	}

#ifndef DEV
	Settings settings;
	if(ShowSettingsDialog(settings)) {
		log.Info() << "user canceled settings dialog. exit";
		return 1;
	}

	log.Info() << "video settings: " << Log::endl
		<< settings.video.videoMode.Width << "x"
		<< settings.video.videoMode.Height << "@"
		<< settings.video.videoMode.BitsPerPixel << ", fullscreen: "
		<< settings.video.fullscreen;

	DWORD styleFlag = sf::Style::Close;
	if(settings.video.fullscreen) styleFlag |= sf::Style::Fullscreen;
	sf::RenderWindow window(settings.video.videoMode, "Breakin' Brix, Christian Jaeger", styleFlag);
	window.UseVerticalSync(true);
#else
	sf::RenderWindow window(sf::VideoMode(1280, 720, 32),
		"Breakin' Brix, Christian Jaeger, DEVMODE", sf::Style::Close);
	window.UseVerticalSync(true);
#endif

	static sf::View view = sf::View(sf::FloatRect(0, 0, VSCREEN_WIDTH, VSCREEN_HEIGHT));
	window.SetView(view);

	Game theGame(window);

	while(theGame.IsRunning() && window.IsOpened())
	{
		sf::Event event_;
		while(window.GetEvent(event_))
		{
			switch(event_.Type)
			{
			case sf::Event::KeyPressed:
				if(sf::Key::F4 == event_.Key.Code)
					window.Close();
				break;
			case sf::Event::Closed:
				window.Close();
				break;
			}
		}

		float frameTime = window.GetFrameTime();
		if(1.0f < frameTime) frameTime = 1.0f;

		const sf::Input& input = window.GetInput();

		window.Clear(sf::Color(255, 0, 255));
		theGame.Move(frameTime, input);
		theGame.Draw(window);
		window.Display();
	}
	
	return 0;
}