#include "GameSettingEvent.hpp"

GameSettingEvent::GameSettingEvent(
	const sf::Color& tank_col,
	const sf::Color& crosshair_col,
	const sf::Color& crosshair_line_col,
	float crosshair_line_thickness)
	: 
	tank_col(tank_col),
	crosshair_col(crosshair_col),
	crosshair_line_col(crosshair_line_col),
	crosshair_line_thickness(crosshair_line_thickness)
{
}
