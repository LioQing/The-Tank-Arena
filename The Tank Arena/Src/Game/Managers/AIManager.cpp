#include "AIManager.hpp"

#include "../SpawnEntity.hpp"

#include <CSVReader.hpp>

void AIManager::Init(const ProgramInfo& program_info)
{
	is_processing = false;
	m_program_info = &program_info;
}

void AIManager::Spawn(const std::string& path, lic::Manager& manager, size_t tile_size)
{
	lio::CSVReader csvr(path, true);

	for (auto y = 0u; y < csvr.Row(); ++y)
	{
		for (auto x = 0u; x < csvr.At(0).size(); ++x)
		{
			if (std::stoi(csvr.At(y, x)) < 0)
				spawn::Enemy(lio::Vec2f(x + .5f, y + .5f) * tile_size * m_program_info->scale->Get(), { 20, 19 });
		}
	}
}

void AIManager::ReadData(lic::Manager& manager)
{
}

void AIManager::AIThreadProcess()
{
	while (is_processing)
	{
		//std::cout << "Hi from AI thread" << std::endl;
	}
}

void AIManager::StartProcess()
{
	process_thread = std::thread(&AIManager::AIThreadProcess, this);
	is_processing = true;
}

void AIManager::EndProcess()
{
	is_processing = false;
	process_thread.join();
}