#include "Program.hpp"

#include <lev.hpp>

#include "Events.hpp"

void Program::Init()
{
	// create window
	window.create(sf::VideoMode(1280, 720), "The Tank Arena");
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);

	// ui
	ui.Init(ProgramInfo(window, texture_manager));
}

void Program::MainMenu()
{
}

void Program::Gameplay()
{
	// game init
	game.Init(ProgramInfo(window, texture_manager));

	// config
	lev::Emit<GameSettingEvent>(
		sf::Color(0, 255, 0), // crosshair col
		sf::Color(64, 255, 64, 75), // crosshair line col
		1.f // crosshair line thickness
		);

	// init delta time
	delta_time = 0.f;
	delta_clock.restart();

	while (window.isOpen())
	{
		// sf event
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::Resized)
				lev::Emit<WindowResizedEvent>();
		}

		// update
		game.Update(delta_time);
		ui.Update();

		// draw
		window.clear();
		game.Draw();
		ui.Draw();
		window.display();

		delta_time = static_cast<float>(delta_clock.restart().asMicroseconds()) / 1000.0;
	}
}

TextureManager& Program::TextureManager()
{
	return texture_manager;
}

sf::RenderWindow& Program::Window()
{
	return window;
}
