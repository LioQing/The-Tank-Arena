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
	ai_data.map = lio::Matrix<int8_t>(csvr.At(0).size(), csvr.Row(), false);

	for (auto y = 0u; y < csvr.Row(); ++y)
	{
		for (auto x = 0u; x < csvr.At(0).size(); ++x)
		{
			auto id = std::stoi(csvr.At(y, x));
			if (id < 0)
			{
				auto ai = spawn::Enemy( // config
					lio::Vec2f(x + .5f, y + .5f) * tile_size * m_program_info->scale->Get(),
					{ 20, 19 },
					.15f,
					.2f,
					200.f,
					2.f,
					5,
					.0005f
				);
				ais.emplace_back(ai.GetComponent<AIControlComponent>(), ai::IDToProcess(-id));
			}
			else if (id > 0)
			{
				ai_data.map.At(x, y) = true;
			}
		}
	}
}

void AIManager::ReadData(lic::Manager& manager)
{
	ai_data.player_pos = &manager.GetEntity(player_id).GetComponent<TankTransformComponent>().position;

	ai_data.ai_pos.clear();
	for (auto [control, transform] : manager.Filter<AIControlComponent, TankTransformComponent>().Each())
	{
		ai_data.ai_pos.emplace(transform.GetEntityID(), &transform.position);
	}
}

void AIManager::AIThreadProcess()
{
	while (is_processing)
	{
		for (auto& [control, process] : ais)
		{
			process(control, ai_data);
		}
	}
}

void AIManager::StartProcess(lic::Manager& manager)
{
	ReadData(manager);
	process_thread = std::thread(&AIManager::AIThreadProcess, this);
	is_processing = true;
}

void AIManager::EndProcess()
{
	is_processing = false;
	process_thread.join();
}