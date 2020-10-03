#include "PlayButtonElement.hpp"

#include "../../Events.hpp"
#include "../../../Program.hpp"

void PlayButtonElement::UpdateTriggerRect()
{
	trigger_rect =
	{
		{ idle_sprite.getGlobalBounds().left, idle_sprite.getGlobalBounds().top },
		{ idle_sprite.getGlobalBounds().width, idle_sprite.getGlobalBounds().height }
	};
}

PlayButtonElement::PlayButtonElement(uint32_t* program_state, const Scale& xscale)
	: program_state(program_state), xscale(xscale)
{
	Listen<UIRescaleEvent>();
}

void PlayButtonElement::SetPosition(const sf::Vector2f& pos)
{
	idle_sprite.setPosition(pos);
	clicked_sprite.setPosition(pos);
	hover_sprite.setPosition(pos);

	UpdateTriggerRect();
}

void PlayButtonElement::SetTexture(const std::string& id)
{
	idle_sprite.setTexture(*program_info->texture_manager->GetTexture(id + "_button"));
	idle_sprite.setOrigin(idle_sprite.getTextureRect().width / 2.f, idle_sprite.getTextureRect().height / 2.f);

	clicked_sprite.setTexture(*program_info->texture_manager->GetTexture(id + "_button_clicked"));
	clicked_sprite.setOrigin(clicked_sprite.getTextureRect().width / 2.f, clicked_sprite.getTextureRect().height / 2.f);

	hover_sprite.setTexture(*program_info->texture_manager->GetTexture(id + "_button_hover"));
	hover_sprite.setOrigin(hover_sprite.getTextureRect().width / 2.f, hover_sprite.getTextureRect().height / 2.f);

	UpdateTriggerRect();
}

void PlayButtonElement::SetScale(const Scale& scale)
{
	idle_sprite.setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());
	clicked_sprite.setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());
	hover_sprite.setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());

	UpdateTriggerRect();
}

const sf::Sprite& PlayButtonElement::GetSprite() const
{
	if (is_down)
		return clicked_sprite;
	else if (is_hovering)
		return hover_sprite;
	else
		return idle_sprite;
}

void PlayButtonElement::OnClick()
{
}

void PlayButtonElement::OnRelease()
{
	*program_state = Program::State::IN_GAME;
}

void PlayButtonElement::On(const lev::Event& event)
{
	if (event.Is<UIRescaleEvent>())
	{
		const auto& rescale_event = static_cast<const UIRescaleEvent&>(event);
		SetScale(rescale_event.scale);
		SetPosition(rescale_event.view.getCenter());
	}
}
