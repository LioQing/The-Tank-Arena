#include "ArenaManager.hpp"

#include <string>
#include <CSVReader.hpp>

#include "../Components.hpp"

void ArenaManager::Init(ProgramInfo& program_info)
{
	this->program_info = &program_info;
}

lic::Entity& ArenaManager::SetArena(lic::Entity entity)
{
	return m_arena_entity = entity;
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
			level.level.At(x, y).id = std::stoi(csvr.At(y, x));

			if (csvr.At(y, x) == "1")
				level.walls.emplace_back(x, y);
		}
	}

	// process edges
	for (auto y = 0u; y < level.level.height; ++y)
	{
		for (auto x = 0u; x < level.level.width; ++x)
		{
			auto cell = level.level.At(x, y);

			if (cell.id != 0)
				continue;

			for (int8_t dir = Cell::Dir::UP; dir != Cell::Dir::SIZE; ++dir)
			{
				auto cell_to_be_check = lio::Vec2i(x, y) + Cell::DirToVec(static_cast<Cell::Dir>(dir));

				if ((cell_to_be_check.x < 0 ||
					cell_to_be_check.x >= level.level.width ||
					cell_to_be_check.y < 0 ||
					cell_to_be_check.y >= level.level.height) ||
					level.level.At(cell_to_be_check.x, cell_to_be_check.y) != 1)
				{
					cell.edge_exist.at(dir) = false;
					continue;
				}

				cell.edge_exist.at(dir) = true;

				auto adjacent_cell = lio::Vec2i(x, y) + Cell::DirToVec(Cell::Dir::LEFT);
				if (dir == Cell::Dir::LEFT || dir == Cell::Dir::RIGHT)
					adjacent_cell = lio::Vec2i(x, y) + Cell::DirToVec(Cell::Dir::UP);

				if ((adjacent_cell.x >= 0 && adjacent_cell.y >= 0) &&
					level.level.At(adjacent_cell.x, adjacent_cell.y) == 1 &&
					level.level.At(adjacent_cell.x, adjacent_cell.y).edge_exist.at(dir))
				{
					if (dir == Cell::Dir::LEFT || dir == Cell::Dir::RIGHT)
						++level.edge_pool.at(level.level.At(adjacent_cell.x, adjacent_cell.y).edge_id.at(dir)).edge.p2.y;
					else
						++level.edge_pool.at(level.level.At(adjacent_cell.x, adjacent_cell.y).edge_id.at(dir)).edge.p2.x;
				}
				else
				{
					cell.edge_id.at(dir) = level.edge_pool.size();
					level.edge_pool.push_back(Edge());
					level.edge_pool.at(cell.edge_id.at(dir)).dir = static_cast<Edge::Dir>(dir);

					if (dir == Cell::Dir::UP)
						level.edge_pool.at(cell.edge_id.at(dir)).edge = lio::LineSegi(x, y, x + 1, y);
					else if (dir == Cell::Dir::DOWN)
						level.edge_pool.at(cell.edge_id.at(dir)).edge = lio::LineSegi(x, y + 1, x + 1, y + 1);
					else if (dir == Cell::Dir::LEFT)
						level.edge_pool.at(cell.edge_id.at(dir)).edge = lio::LineSegi(x, y, x, y + 1);
					else if (dir == Cell::Dir::RIGHT)
						level.edge_pool.at(cell.edge_id.at(dir)).edge = lio::LineSegi(x + 1, y, x + 1, y + 1);
				}
			}
		}
	}

	*program_info->scale = static_cast<float>(program_info->window->getSize().y) / (level.level.height * tile_size);

	auto& sprite = m_arena_entity.AddComponent<LevelSpriteComponent>(*program_info, level.level, "tileset", tile_size);
}

const lic::Entity& ArenaManager::GetEntity() const
{
	return m_arena_entity;
}
