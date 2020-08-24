#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <lic.hpp>
#include <Matrix.hpp>

#include "../Arena/LevelComponent.hpp"
#include "../../../ProgramUtils.hpp"

struct LevelSpriteComponent : lic::Component
{
	std::vector<sf::Sprite> tile_sprites;

	LevelSpriteComponent(const ProgramInfo& program_info, const lio::Matrix<Cell>& level, const std::string& tileset_id, int tile_size);
};