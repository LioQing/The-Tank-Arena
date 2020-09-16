#include "AIManager.hpp"

#include <CSVReader.hpp>

#include "../Components.hpp"
#include "../AI/AIProcessor.hpp"
#include "../SpawnEntity.hpp"

void AIManager::Init(const ProgramInfo& program_info, lic::EntityID player)
{
	is_processing = false;
	m_program_info = &program_info;
	player_id = player;
	ais.clear();
}

void AIManager::Spawn(const std::string& path, lic::Manager& manager, size_t tile_size)
{
	lio::CSVReader csvr(path, true);

	for (auto y = 0u; y < csvr.Row(); ++y)
	{
		for (auto x = 0u; x < csvr.At(0).size(); ++x)
		{
			auto id = std::stoi(csvr.At(y, x));
			if (id < 0)
			{
				auto ai = spawn::Enemy(lio::Vec2f(x + .5f, y + .5f) * tile_size * m_program_info->scale->Get(), "enemy_normal");
				ais.emplace_back(AIHandle(ai.GetID(), ai.GetComponent<AIControlComponent>()), ai::IDToProcess(-id));
				process_data.ai_data.emplace(ai.GetID(), AIProcessData::AISpecificData());
			}
		}
	}
}

void AIManager::ReadData(lic::Manager& manager)
{
	// program info
	process_data.scale = *m_program_info->scale;

	// player position
	process_data.player_pos = manager.GetEntity(player_id).GetComponent<TankTransformComponent>().position;

	// ai data
	for (auto [control, transform, health] : manager.Filter<AIControlComponent, TankTransformComponent, HealthComponent>().Each())
	{
		process_data.ai_data.at(transform.GetEntityID()).position = transform.position;
		process_data.ai_data.at(transform.GetEntityID()).is_dead = health.is_dead;
	}
}

void AIManager::AIThreadProcess()
{
	srand(time(NULL));

	float delta_time = 0.f;
	sf::Clock delta_clock;

	delta_clock.restart();
	while (is_processing)
	{
		process_data.dt = delta_time;

		for (auto& [control, process] : ais)
		{
			process(control, process_data);
		}

		delta_time = static_cast<float>(delta_clock.restart().asMicroseconds()) / 1000.0;
	}
}

void AIManager::StartProcess(lic::Manager& manager, const lic::Entity& arena_entity)
{
	ReadData(manager);

	process_data.level = arena_entity.GetComponent<LevelComponent>();

	process_thread = std::thread(&AIManager::AIThreadProcess, this);
	is_processing = true;
}

void AIManager::EndProcess()
{
	is_processing = false;
	process_thread.join();
}
