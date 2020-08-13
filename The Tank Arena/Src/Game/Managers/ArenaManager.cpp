#include "ArenaManager.hpp"

#include <string>
#include <CSVReader.hpp>

#include "../Components.hpp"

void ArenaManager::SetArena(lic::Entity entity)
{
	m_arena_entity = entity;
}

void ArenaManager::LoadMap(ProgramInfo& program_info, const std::string& path)
{
	lio::CSVReader csvr(path, true);
	auto& level = m_arena_entity.AddComponent<LevelComponent>(csvr.At(0).size(), csvr.Row());

	for (auto y = 0u; y < csvr.Row(); ++y)
	{
		for (auto x = 0u; x < csvr.At(0).size(); ++x)
		{
			level.level.At(x, y) = std::stoi(csvr.At(y, x));
		}
	}

	auto& sprite = m_arena_entity.AddComponent<LevelSpriteComponent>(program_info, level.level, "tileset", 32);
}
