#include "Game.hpp"

#include <iostream>

#include "SpawnEntity.hpp"
#include "Systems.hpp"
#include "Components.hpp"

void Game::Init(ProgramInfo program_info)
{
	// store program var
	m_program_info = program_info;
	m_program_info.scale = &m_scale;

	// load textures
	m_program_info.texture_manager->LoadTexture("hull", R"(Assets\Player\base_hull.png)");
	m_program_info.texture_manager->LoadTexture("turret", R"(Assets\Player\base_turret.png)");
	m_program_info.texture_manager->LoadTexture("tileset", R"(Assets\TileMap\Chess.png)");

	// add system
	m_sys_man.Init(m_program_info, m_ic_man);
	m_sys_man.Add<SpriteSystem>();
	m_sys_man.Add<InputSystem>();
	m_sys_man.Add<MovementSystem>();

	// level
	m_arena_man.Init(m_program_info);
	m_arena_man.SetArena(m_ic_man.AddEntity());
	m_arena_man.LoadMap(R"(Assets\TileMap\TestLevel.csv)");

	// spawn
	spawn::Init(m_program_info, m_ic_man);
	auto player = spawn::Player();

	// camera manager
	m_cam_man.Init(
		m_program_info, 
		player.GetComponent<TankTransformComponent>().position, 
		m_arena_man.GetEntity().GetComponent<LevelComponent>());
}

void Game::Update(float dt)
{
	// sf event
	sf::Event event;
	while (m_program_info.window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_program_info.window->close();
		else if (event.type == sf::Event::Resized) {}
			m_cam_man.UpdateView();
	}

	m_sys_man.SetDeltaTime(dt);

	// get input
	m_sys_man.Get<InputSystem>().Update();

	// systems update
	m_sys_man.Get<MovementSystem>().Update();
	m_sys_man.Get<SpriteSystem>().Update();

	// camera
	m_cam_man.Update();
}

void Game::Draw()
{
	m_sys_man.Get<SpriteSystem>().Draw();
	m_cam_man.Draw();
}

void Game::CleanUp()
{
}
