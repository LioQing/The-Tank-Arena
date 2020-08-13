#include "CameraManager.hpp"

#include "../Events.hpp"

void CameraManager::Init(ProgramInfo& program_info, const lio::Vec2f& player_pos, const LevelComponent& level)
{
	this->program_info = &program_info;
	this->player_pos = &player_pos;
	this->level = &level;
	
	UpdateView();
}

void CameraManager::Update()
{
	view.setCenter(player_pos->x, level->size.y * level->tile_size * program_info->scale->Get() / 2.f);
}

void CameraManager::Draw()
{
	program_info->window->setView(view);
}

void CameraManager::UpdateView()
{
	auto pre_scale = *program_info->scale;
	*program_info->scale = static_cast<float>(program_info->window->getSize().y) / (level->level.height * level->tile_size);
	view.setSize(sf::Vector2f(program_info->window->getSize()));
}
