#include "Program.hpp"

void Program::Init()
{
	// create window
	window.create(sf::VideoMode(800, 600), "The Tank Arena");
	window.setFramerateLimit(60);

	// game init
	game = Game(window);
}

void Program::MainMenu()
{
}

void Program::Gameplay()
{
	// init delta time
	delta_time = 0.f;
	delta_clock.restart();

	while (window.isOpen())
	{
		// update
		game.Update(delta_time);

		// draw
		window.clear();
		game.Draw();
		window.display();

		delta_time = static_cast<float>(delta_clock.restart().asMicroseconds()) / 1000.0;
	}
}
