#include "ProgramInfo.hpp"

ProgramInfo::ProgramInfo(sf::RenderWindow& window, TextureManager& tex_man)
	: window(&window), texture_manager(&tex_man)
{
}