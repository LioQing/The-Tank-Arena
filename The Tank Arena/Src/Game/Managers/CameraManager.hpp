#pragma once

#include <SFML/Graphics.hpp>
#include <LioGraphics.hpp>

#include "../../ProgramUtils.hpp"
#include "../Components.hpp"

class CameraManager
{
private:

	sf::View view;

	ProgramInfo* program_info;
	const lio::Vec2f* player_pos;
	const LevelComponent* level;

	bool width_shrinked;
	float const_center_y; // for whatever lengthy center calculation

public:

	void Init(ProgramInfo& program_info, const lio::Vec2f& player_pos, const LevelComponent& level);
	void Update();
	void Draw();

	void UpdateView();
};