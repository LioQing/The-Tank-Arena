#include "ArenaManager.hpp"

#include <string>
#include <CSVReader.hpp>

#include "../Components.hpp"

void ArenaManager::Init(ProgramInfo& program_info)
{
	this->program_info = &program_info;
}

void ArenaManager::SetArena(lic::Entity entity)
{
	m_arena_entity = entity;
}

void ArenaManager::LoadMap(const std::string& path)
{
	lio::CSVReader csvr(path, true);
	auto tile_size = 32;
	auto& level = m_arena_entity.AddComponent<LevelComponent>(csvr.At(0).size(), csvr.Row(), tile_size);

	for (auto y = 0u; y < csvr.Row(); ++y)
	{
		for (auto x = 0u; x < csvr.At(0).size(); ++x)
		{
			level.level.At(x, y) = std::stoi(csvr.At(y, x));

			if (csvr.At(y, x) == "1")
				level.walls.emplace_back(x, y);
		}
	}

	*program_info->scale = static_cast<float>(program_info->window->getSize().y) / (level.level.height * tile_size);

	auto& sprite = m_arena_entity.AddComponent<LevelSpriteComponent>(*program_info, level.level, "tileset", tile_size);
}

const lic::Entity& ArenaManager::GetEntity() const
{
	return m_arena_entity;
}
