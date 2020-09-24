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
	ui = std::shared_ptr<UI>(new UI());
	ui->Init(ProgramInfo(window, texture_manager));
}

void Program::MainMenu()
{
	while (state == State::IN_MAIN_MENU)
	{
		// sf event
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				state = State::CLOSED;
				window.close();
			}
			else if (event.type == sf::Event::Resized)
				lev::Emit<WindowResizedEvent>();
		}
	}
}

void Program::Gameplay()
{
	// game init
	game = std::shared_ptr<Game>(new Game());
	game->Init(ProgramInfo(window, texture_manager), ui->GetView());

	game->CleanUp();
	game.reset();


	// game init
	game = std::shared_ptr<Game>(new Game());
	game->Init(ProgramInfo(window, texture_manager), ui->GetView());

	// config
	lev::Emit<GameSettingEvent>(
		sf::Color(0x96FF7FFF), // tank col
		sf::Color(0x00FF00FF), // crosshair col
		sf::Color(0x40FF403F), // crosshair line col
		1.f // crosshair line thickness
		);

	// init delta time
	delta_time = 0.f;
	delta_clock.restart();

	while (state == State::IN_GAME)
	{
		// sf event
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				state = State::CLOSED;
				window.close();
			}
			else if (event.type == sf::Event::Resized)
				lev::Emit<WindowResizedEvent>();
		}

		// tmp quick exit
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			break;

		// update
		game->Update(delta_time);
		ui->Update();

		// draw
		window.clear();
		game->Draw();
		ui->Draw();
		window.display();

		delta_time = static_cast<float>(delta_clock.restart().asMicroseconds()) / 1000.0;
	}

	game->CleanUp();
	game.reset();
}

TextureManager& Program::TextureManager()
{
	return texture_manager;
}

sf::RenderWindow& Program::Window()
{
	return window;
}

Program::State Program::GetState() const
{
	return state;
}
