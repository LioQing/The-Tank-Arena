#include "Game.hpp"

#include <iostream>

#include "../Events.hpp"
#include "SpawnEntity.hpp"
#include "Systems.hpp"
#include "Components.hpp"

void Game::Init(ProgramInfo program_info)
{
	auto tile_size = 32u;

	// listen events
	Listen<WindowResizedEvent>();

	// store program var
	m_program_info = program_info;
	m_program_info.scale = &m_scale;

	// load textures
	m_program_info.texture_manager->LoadTexture("hull", R"(Assets\Player\hull.png)");
	m_program_info.texture_manager->LoadTexture("turret", R"(Assets\Player\turret.png)");
	m_program_info.texture_manager->LoadTexture("ehull", R"(Assets\Enemies\normal\hull.png)");
	m_program_info.texture_manager->LoadTexture("eturret", R"(Assets\Enemies\normal\turret.png)");
	m_program_info.texture_manager->LoadTexture("tileset", R"(Assets\TileMap\Chess.png)");
	m_program_info.texture_manager->LoadTexture("bullet", R"(Assets\Projectile\Default.png)");

	// level
	m_arena_man.Init(m_program_info);
	auto& arena_entity = m_arena_man.SetArena(m_ic_man.AddEntity());
	m_arena_man.LoadMap(R"(Assets\TileMap\DebugLevel.csv)", tile_size);

	// add system
	m_sys_man.Init(m_program_info, m_ic_man);
	m_sys_man.Add<SpriteSystem>();
	m_sys_man.Add<InputSystem>();
	m_sys_man.Add<MovementSystem>();
	m_sys_man.Add<TurretSystem>();
	m_sys_man.Add<ProjectileSystem>();
	m_sys_man.Add<CollisionSystem>(arena_entity);
	m_sys_man.Add<CrosshairSystem>(arena_entity);
	m_sys_man.Add<HUDSystem>(arena_entity);

	// spawn
	spawn::Init(m_program_info, m_ic_man);
	auto player = spawn::Player(
		{ 400, 300 },
		{ 20, 19 },
		.15f,
		.2,
		200.f,
		2.f,
		5
	);

	// ai manager
	m_ai_man.Init(m_program_info, player.GetID());
	m_ai_man.Spawn(R"(Assets\TileMap\DebugLevel.csv)", m_ic_man, tile_size);

	// camera manager
	m_cam_man.Init(
		m_program_info,
		player.GetComponent<TankTransformComponent>().position,
		m_arena_man.GetEntity().GetComponent<LevelComponent>());

	m_ai_man.StartProcess(m_ic_man);
	m_ai_man.ReadData(m_ic_man);
}

void Game::Update(float dt)
{
	// get the view working for systems
	m_cam_man.Draw();

	m_sys_man.SetDeltaTime(dt);

	// get input
	m_sys_man.Get<InputSystem>().Update();

	// systems update
	m_sys_man.Get<MovementSystem>().Update();
	m_sys_man.Get<ProjectileSystem>().Update();
	m_sys_man.Get<TurretSystem>().Update();
	m_sys_man.Get<CollisionSystem>().Update();
	m_sys_man.Get<SpriteSystem>().Update();

	// camera
	m_cam_man.Update();

	// ui
	m_sys_man.Get<CrosshairSystem>().Update();
	m_sys_man.Get<HUDSystem>().Update();
}

void Game::Draw()
{
	m_cam_man.Draw();
	m_sys_man.Get<SpriteSystem>().Draw();
	m_sys_man.Get<HUDSystem>().Draw();

	// debug use
	//m_sys_man.Get<CollisionSystem>().Draw();
}

void Game::CleanUp()
{
	m_ai_man.EndProcess();
}

void Game::On(const lev::Event& event)
{
	if (event.Is<WindowResizedEvent>())
	{
		m_cam_man.UpdateView();
	}
}
