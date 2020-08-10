#include "Game.hpp"

#include <iostream>

Game::Game(sf::RenderWindow& window)
	: m_window(&window)
{
}

void Game::Init(sf::RenderWindow* window)
{
	m_window = window;
}

void Game::Update(float dt)
{
	// sf event
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window->close();
	}

	std::cout << 1000 / dt << std::endl;
}

void Game::Draw()
{
}

void Game::CleanUp()
{
}
