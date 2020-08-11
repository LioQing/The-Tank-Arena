#include "ProgramInfo.hpp"

ProgramInfo::ProgramInfo(Scale& scale, sf::RenderWindow& window, TextureManager& tex_man)
	: scale(&scale), window(&window), texture_manager(&tex_man)
{
}