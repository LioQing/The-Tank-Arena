#include "ProgramInfo.hpp"

ProgramInfo::ProgramInfo(sf::RenderWindow& window, TextureManager& tex_man, const uint32_t& level)
	: window(&window), texture_manager(&tex_man), current_level(&level)
{
}