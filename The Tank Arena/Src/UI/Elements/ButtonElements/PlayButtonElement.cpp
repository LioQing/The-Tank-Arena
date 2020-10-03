#include "PlayButtonElement.hpp"

#include "../../Events.hpp"

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

	UpdateTriggerRect();
}

void PlayButtonElement::SetTexture(const std::string& id)
{
	idle_sprite.setTexture(*program_info->texture_manager->GetTexture(id + "_button"));
	idle_sprite.setOrigin(idle_sprite.getTextureRect().width / 2.f, idle_sprite.getTextureRect().height / 2.f);

	clicked_sprite.setTexture(*program_info->texture_manager->GetTexture(id + "_button_clicked"));
	clicked_sprite.setOrigin(clicked_sprite.getTextureRect().width / 2.f, clicked_sprite.getTextureRect().height / 2.f);

	UpdateTriggerRect();
}

void PlayButtonElement::SetScale(const Scale& scale)
{
	idle_sprite.setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());
	clicked_sprite.setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());

	UpdateTriggerRect();
}

const sf::Sprite& PlayButtonElement::GetSprite() const
{
	if (!is_down)
		return idle_sprite;
	else
		return clicked_sprite;
}

void PlayButtonElement::OnClick()
{
	std::cout << "Play button on click" << std::endl;
}

void PlayButtonElement::OnRelease()
{
	std::cout << "On mouse release" << std::endl;
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
