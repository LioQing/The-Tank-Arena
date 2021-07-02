#include "LevelButtonElement.hpp"

#include "../../../Events.hpp"
#include "../../../Program.hpp"

void LevelButtonElement::UpdateOrigin()
{
	number_idle_sprite[1].setOrigin(4, number_idle_sprite[1].getTextureRect().height / 2.f + 1);
	number_clicked_sprite[1].setOrigin(4, number_clicked_sprite[1].getTextureRect().height / 2.f - 1);
	number_hover_sprite[1].setOrigin(4, number_hover_sprite[1].getTextureRect().height / 2.f + 1);
	number_idle_sprite[0].setOrigin(4, number_idle_sprite[0].getTextureRect().height / 2.f + 1);
	number_clicked_sprite[0].setOrigin(4, number_clicked_sprite[0].getTextureRect().height / 2.f - 1);
	number_hover_sprite[0].setOrigin(4, number_hover_sprite[0].getTextureRect().height / 2.f + 1);
	idle_sprite.setOrigin(idle_sprite.getTextureRect().width / 2.f, idle_sprite.getTextureRect().height / 2.f);
	clicked_sprite.setOrigin(clicked_sprite.getTextureRect().width / 2.f, clicked_sprite.getTextureRect().height / 2.f);
}

LevelButtonElement::LevelButtonElement(const Scale& xscale, uint32_t active_state)
	: ButtonElement(xscale, active_state)
{
}

void LevelButtonElement::OnRelease()
{
	if (number >= 1 && number <= 9) // level
		lev::Emit<LevelChangeEvent>(number);
	else
		lev::Emit<LevelChangeEvent>(0);
	lev::Emit<StateChangeEvent>(Program::State::IN_GAME);
}

void LevelButtonElement::SetNumber(uint8_t n)
{
	number = n;

	for (auto i = 0; i < 2; ++i)
	{
		if (i == 0)
		{
			number_idle_sprite[i].setTextureRect({ 8 * (n / 10), 0, 8, 16 });
			number_hover_sprite[i].setTextureRect({ 8 * (n / 10), 0, 8, 16 });
			number_clicked_sprite[i].setTextureRect({ 8 * (n / 10), 0, 8, 16 });
		}
		else
		{
			number_idle_sprite[i].setTextureRect({ 8 * (n % 10), 0, 8, 16 });
			number_hover_sprite[i].setTextureRect({ 8 * (n % 10), 0, 8, 16 });
			number_clicked_sprite[i].setTextureRect({ 8 * (n % 10), 0, 8, 16 });
		}
	}

	UpdateOrigin();
}

void LevelButtonElement::SetPosition(const sf::Vector2f& pos)
{
	number_idle_sprite[1].setPosition(pos.x + idle_sprite.getGlobalBounds().width * 1.f / 6, pos.y);
	number_clicked_sprite[1].setPosition(pos.x + idle_sprite.getGlobalBounds().width * 1.f / 6, pos.y);
	number_hover_sprite[1].setPosition(pos.x + idle_sprite.getGlobalBounds().width * 1.f / 6, pos.y);
	number_idle_sprite[0].setPosition(pos.x - idle_sprite.getGlobalBounds().width * 1.f / 6, pos.y);
	number_clicked_sprite[0].setPosition(pos.x - idle_sprite.getGlobalBounds().width * 1.f / 6, pos.y);
	number_hover_sprite[0].setPosition(pos.x - idle_sprite.getGlobalBounds().width * 1.f / 6, pos.y);
	idle_sprite.setPosition(pos);
	clicked_sprite.setPosition(pos);

	UpdateTriggerRect();
}

void LevelButtonElement::SetTexture(const std::string& id)
{
	number_idle_sprite[1].setTexture(*program_info->texture_manager->GetTexture(id + "_idle"));
	number_clicked_sprite[1].setTexture(*program_info->texture_manager->GetTexture(id + "_clicked"));
	number_hover_sprite[1].setTexture(*program_info->texture_manager->GetTexture(id + "_hover"));
	number_idle_sprite[0].setTexture(*program_info->texture_manager->GetTexture(id + "_idle"));
	number_clicked_sprite[0].setTexture(*program_info->texture_manager->GetTexture(id + "_clicked"));
	number_hover_sprite[0].setTexture(*program_info->texture_manager->GetTexture(id + "_hover"));
	idle_sprite.setTexture(*program_info->texture_manager->GetTexture("square_button"));
	clicked_sprite.setTexture(*program_info->texture_manager->GetTexture("square_button_clicked"));

	UpdateOrigin();
	UpdateTriggerRect();
}

void LevelButtonElement::SetScale(const Scale& scale)
{
	number_idle_sprite[1].setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());
	number_clicked_sprite[1].setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());
	number_hover_sprite[1].setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());
	number_idle_sprite[0].setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());
	number_clicked_sprite[0].setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());
	number_hover_sprite[0].setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());
	idle_sprite.setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());
	clicked_sprite.setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());

	UpdateTriggerRect();
}

const sf::Sprite& LevelButtonElement::GetButtonSprite() const
{
	if (is_down)
		return clicked_sprite;
	else
		return idle_sprite;
}

// digit: 0 = 2nd digit, 1 = 1st digit
const sf::Sprite& LevelButtonElement::GetNumberSprite(uint8_t digit) const
{
	if (is_down)
		return number_clicked_sprite[digit];
	else if (is_hovering)
		return number_hover_sprite[digit];
	else
		return number_idle_sprite[digit];
}
