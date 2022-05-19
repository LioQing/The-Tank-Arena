#include "Game.hpp"

#include <iostream>
#include <CSVReader.hpp>

#include "../UI/Events.hpp"
#include "../Events.hpp"
#include "SpawnEntity.hpp"
#include "Systems.hpp"
#include "Components.hpp"

Game::Game()
{
	// listen events
	Listen<WindowResizedEvent>();
}

void Game::Init(ProgramInfo program_info, const sf::View& ui_view, uint32_t* program_state, uint32_t level)
{
	auto path = std::string(R"(Data\Levels\1.csv)");
	if (level != 0)
	{
		path = std::string(R"(Data\Levels\)" + std::to_string(level) + ".csv");
	}

	auto tile_size = 32u;

	// yo this a temp fix for multithread race condition
	m_ic_man.GetComponentID<LevelComponent>();
	m_ic_man.GetComponentID<LevelSpriteComponent>();
	m_ic_man.GetComponentID<ProjectileComponent>();
	m_ic_man.GetComponentID<ProjectileSpriteComponent>();

	// store program var
	m_program_state = program_state;
	m_program_info = program_info;
	m_program_info.scale = &m_scale;

	// load textures
	m_program_info.texture_manager->LoadTankTexture("player_default", R"(Data\Player)");
	m_program_info.texture_manager->LoadTankTexture("enemy_normal", R"(Data\Enemies)");
	m_program_info.texture_manager->LoadTankTexture("enemy_speed", R"(Data\Enemies)");

	m_program_info.texture_manager->LoadTexture("tileset", R"(Data\TileMap\Metal.png)");
	m_program_info.texture_manager->LoadTexture("bullet", R"(Data\Projectile\Default.png)");
	m_program_info.texture_manager->LoadTexture("explode", R"(Data\Projectile\Explode.png)");
	m_program_info.texture_manager->LoadTexture("gunfire", R"(Data\Projectile\Gunfire.png)");

	// level
	m_arena_man.Init(m_program_info);
	auto& arena_entity = m_arena_man.SetArena(m_ic_man.AddEntity());
	m_arena_man.LoadMap(path, tile_size);

	// add system
	m_sys_man.Init(m_program_info, m_ic_man);
	m_sys_man.Add<SpriteSystem>();
	m_sys_man.Add<InputSystem>();
	m_sys_man.Add<MovementSystem>();
	m_sys_man.Add<TurretSystem>(arena_entity);
	m_sys_man.Add<ProjectileSystem>();
	m_sys_man.Add<CollisionSystem>(arena_entity);
	m_sys_man.Add<CrosshairSystem>(arena_entity, ui_view);
	m_sys_man.Add<HUDSystem>(arena_entity);
	m_sys_man.Add<EndGameSystem>(arena_entity);

	// spawn
	spawn::Init(m_program_info, m_ic_man);

	// player
	auto player = lic::Entity();
	lio::CSVReader csvr(path, true);
	for (auto y = 0u; y < csvr.Row(); ++y)
	{
		for (auto x = 0u; x < csvr.At(0).size(); ++x)
		{
			auto id = std::stoi(csvr.At(y, x));
			if (id == -1)
			{
				player = spawn::Player(
					lio::Vec2f(x + .5f, y + .5f) * tile_size * m_program_info.scale->Get(),
					"player_default",
					R"(Data\Player\player_default\info.json)");
				break;
			}
		}
	}

	// ai manager
	m_ai_man.Init(m_program_info, player.GetID());
	m_ai_man.Spawn(path, m_ic_man, tile_size);

	// camera manager
	m_cam_man.Init(
		m_program_info,
		player.GetComponent<TankTransformComponent>().position,
		m_arena_man.GetEntity().GetComponent<LevelComponent>()
	);

	m_ai_man.StartProcess(m_ic_man, arena_entity);
}

void Game::Update(float dt)
{
	// get the view working for systems
	m_cam_man.Draw();

	m_sys_man.SetDeltaTime(dt);

	// get input
	m_ai_man.ReadData(m_ic_man);
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

	// game
	m_sys_man.Get<EndGameSystem>().Update();
}

void Game::Draw()
{
	m_cam_man.Draw();
	m_sys_man.Get<SpriteSystem>().Draw();
	m_sys_man.Get<HUDSystem>().Draw();

	// debug use
	// m_sys_man.Get<CollisionSystem>().Draw();
}

void Game::CleanUp()
{
	m_ai_man.EndProcess();

	// unload textures
	m_program_info.texture_manager->UnloadTankTexture("player_default");
	m_program_info.texture_manager->UnloadTankTexture("enemy_normal");
	m_program_info.texture_manager->UnloadTankTexture("enemy_speed");

	m_program_info.texture_manager->UnloadTexture("tileset");
	m_program_info.texture_manager->UnloadTexture("bullet");
}

void Game::On(const lev::Event& event)
{
	if (event.Is<WindowResizedEvent>())
	{
		m_cam_man.UpdateView();
	}
}
