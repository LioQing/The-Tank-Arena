#include "Program.hpp"

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

	// init delta time
	delta_time = 0.f;
	delta_clock.restart();

	while (window.isOpen())
	{
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
