#include "LevelSpriteComponent.hpp"

LevelSpriteComponent::LevelSpriteComponent(const ProgramInfo& program_info, const lio::Matrixi& level, const std::string& tileset_id, int tile_size)
{
	for (auto y = 0u; y < level.height; ++y)
	{
		for (auto x = 0u; x < level.width; ++x)
		{
			sf::Sprite sprite;
			sprite.setPosition(x * tile_size * program_info.scale->Get(), y * tile_size * program_info.scale->Get());
			sprite.setScale(program_info.scale->sfVec2f());
			sprite.setTexture(*program_info.texture_manager->GetTexture(tileset_id));
			sprite.setTextureRect(sf::IntRect(level.At(x, y) % 10 * tile_size, level.At(x, y) / 10 * tile_size, tile_size, tile_size));
			tile_sprites.push_back(sprite);
		}
	}
}
