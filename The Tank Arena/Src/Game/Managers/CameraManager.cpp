#include "CameraManager.hpp"

#include <lev.hpp>

#include "../Events.hpp"
#include "../../ProgramUtils.hpp"

void CameraManager::Init(ProgramInfo& program_info, const lio::Vec2f& player_pos, const LevelComponent& level)
{
	this->program_info = &program_info;
	this->player_pos = &player_pos;
	this->level = &level;
	
	UpdateView();
}

void CameraManager::Update()
{
	if (width_shrinked)
	{
		if (player_pos->y < view.getSize().y / 2.f)
			view.setCenter(player_pos->x, view.getSize().y / 2.f);
		else if (player_pos->y > const_center_y)
			view.setCenter(player_pos->x, const_center_y);
		else
			view.setCenter(lio::ltosvec<float>(*player_pos));
	}
	else
	{
		view.setCenter(player_pos->x, const_center_y);
	}
}

void CameraManager::Draw()
{
	program_info->window->setView(view);
}

void CameraManager::UpdateView()
{
	auto pre_scale = *program_info->scale;

	*program_info->scale = static_cast<float>(program_info->window->getSize().y) / (level->level.height * level->tile_size);

	// resolve over wide view
	if (static_cast<float>(program_info->window->getSize().x) / program_info->window->getSize().y > 2.f)
	{
		*program_info->scale = static_cast<float>(program_info->window->getSize().x) / (20 * level->tile_size);
		width_shrinked = true;
	}
	else
	{
		width_shrinked = false;
	}

	view.setSize(sf::Vector2f(program_info->window->getSize()));

	lev::Emit<SpriteRescaleEvent>(pre_scale, *program_info->scale);

	// post update const
	if (width_shrinked)
		const_center_y = level->size.y * level->tile_size * program_info->scale->Get() - view.getSize().y / 2.f;
	else
		const_center_y = level->size.y * level->tile_size * program_info->scale->Get() / 2.f;
}
