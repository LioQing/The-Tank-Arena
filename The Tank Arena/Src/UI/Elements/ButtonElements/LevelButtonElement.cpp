#include "LevelButtonElement.hpp"

void LevelButtonElement::UpdateOrigin()
{
	idle_sprite[1].setOrigin(4 + 8 * (number - 1), idle_sprite[1].getTextureRect().height / 2.f - 1);
	clicked_sprite[1].setOrigin(4 + 8 * (number - 1), clicked_sprite[1].getTextureRect().height / 2.f + 1);
	hover_sprite[1].setOrigin(4 + 8 * (number - 1), hover_sprite[1].getTextureRect().height / 2.f - 1);
	idle_sprite[0].setOrigin(4 + 8 * (number - 1), idle_sprite[0].getTextureRect().height / 2.f - 1);
	clicked_sprite[0].setOrigin(4 + 8 * (number - 1), clicked_sprite[0].getTextureRect().height / 2.f + 1);
	hover_sprite[0].setOrigin(4 + 8 * (number - 1), hover_sprite[0].getTextureRect().height / 2.f - 1);
	button_sprite.setOrigin(button_sprite.getTextureRect().width / 2.f, button_sprite.getTextureRect().height / 2.f);
	button_clicked_sprite.setOrigin(button_clicked_sprite.getTextureRect().width / 2.f, button_clicked_sprite.getTextureRect().height / 2.f);
}

void LevelButtonElement::UpdateTriggerRect()
{
	trigger_rect =
	{
		{ button_sprite.getGlobalBounds().left, button_sprite.getGlobalBounds().top },
		{ button_sprite.getGlobalBounds().width, button_sprite.getGlobalBounds().height }
	};
}

LevelButtonElement::LevelButtonElement(const Scale& xscale, uint32_t active_state)
	: ButtonElement(xscale, active_state)
{
}

void LevelButtonElement::OnRelease()
{
}

void LevelButtonElement::SetNumber(uint8_t n)
{
	number = n;

	for (auto i = 0; i < 2; ++i)
	{
		if (i == 0)
			idle_sprite[i].setTextureRect({ 8 * n / 10, 0, 8 * n / 10 + 8, 16 });
		else
			idle_sprite[i].setTextureRect({ 8 * n % 10, 0, 8 * n % 10 + 8, 16 });
	}

	UpdateOrigin();
}

void LevelButtonElement::SetPosition(const sf::Vector2f& pos)
{
	idle_sprite[1].setPosition(pos);
	clicked_sprite[1].setPosition(pos);
	hover_sprite[1].setPosition(pos);
	idle_sprite[0].setPosition(pos);
	clicked_sprite[0].setPosition(pos);
	hover_sprite[0].setPosition(pos);
	button_sprite.setPosition(pos);
	button_clicked_sprite.setPosition(pos);

	UpdateTriggerRect();
}

void LevelButtonElement::SetTexture(const std::string& id)
{
	idle_sprite[1].setTexture(*program_info->texture_manager->GetTexture(id + "_idle"));
	clicked_sprite[1].setTexture(*program_info->texture_manager->GetTexture(id + "_clicked"));
	hover_sprite[1].setTexture(*program_info->texture_manager->GetTexture(id + "_hover"));
	idle_sprite[0].setTexture(*program_info->texture_manager->GetTexture(id + "_idle"));
	clicked_sprite[0].setTexture(*program_info->texture_manager->GetTexture(id + "_clicked"));
	hover_sprite[0].setTexture(*program_info->texture_manager->GetTexture(id + "_hover"));
	button_sprite.setTexture(*program_info->texture_manager->GetTexture("square_button"));
	button_clicked_sprite.setTexture(*program_info->texture_manager->GetTexture("square_button_clicked"));

	UpdateOrigin();
	UpdateTriggerRect();
}

void LevelButtonElement::SetScale(const Scale& scale)
{
	idle_sprite[1].setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());
	clicked_sprite[1].setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());
	hover_sprite[1].setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());
	idle_sprite[0].setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());
	clicked_sprite[0].setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());
	hover_sprite[0].setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());
	button_sprite.setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());
	button_clicked_sprite.setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());

	UpdateTriggerRect();
}
