#include "Game.hpp"

#include <iostream>

void Game::Init(sf::RenderWindow* window, Scale* scale)
{
	// store program var
	m_window = window;
	m_scale = scale;

	m_tex_man.LoadTexture("hull", R"(Assets\Player\base_hull.png)");
	m_tex_man.LoadTexture("turret", R"(Assets\Player\base_turret.png)");
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
}

void Game::Draw()
{
	sf::Sprite spr;

	spr.setScale(m_scale->sfVec2f());

	spr.setTexture(*m_tex_man.GetTexture("hull"));
	m_window->draw(spr);
	spr.setTexture(*m_tex_man.GetTexture("turret"));
	m_window->draw(spr);
}

void Game::CleanUp()
{
}
