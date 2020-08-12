#include "Game.hpp"

#include <iostream>

#include "SpawnEntity.hpp"
#include "Systems.hpp"

void Game::Init(ProgramInfo program_info)
{
	// store program var
	m_program_info = program_info;

	// load textures
	m_program_info.texture_manager->LoadTexture("hull", R"(Assets\Player\base_hull.png)");
	m_program_info.texture_manager->LoadTexture("turret", R"(Assets\Player\base_turret.png)");

	// add system
	m_sys_man.Init(m_program_info, m_ic_man);
	m_sys_man.Add<SpriteSystem>();
	m_sys_man.Add<InputSystem>();
	m_sys_man.Add<MovementSystem>();

	// spawn
	spawn::Init(m_program_info, m_ic_man);
	spawn::Player();
}

void Game::Update(float dt)
{
	// sf event
	sf::Event event;
	while (m_program_info.window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_program_info.window->close();
	}

	m_sys_man.SetDeltaTime(dt);

	// get input
	m_sys_man.Get<InputSystem>().Update();

	// systems update
	m_sys_man.Get<MovementSystem>().Update();
	m_sys_man.Get<SpriteSystem>().Update();
}

void Game::Draw()
{
	m_sys_man.Get<SpriteSystem>().Draw();
}

void Game::CleanUp()
{
}
