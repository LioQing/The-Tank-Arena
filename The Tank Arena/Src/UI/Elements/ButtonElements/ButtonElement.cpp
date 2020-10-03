#include "ButtonElement.hpp"

#include "../../Events.hpp"

void ButtonElement::UpdateTriggerRect()
{
	trigger_rect =
	{
		{ idle_sprite.getGlobalBounds().left, idle_sprite.getGlobalBounds().top },
		{ idle_sprite.getGlobalBounds().width, idle_sprite.getGlobalBounds().height }
	};
}

ButtonElement::ButtonElement(const Scale& xscale)
	: xscale(xscale)
{
	Listen<UIRescaleEvent>();
}

void ButtonElement::SetPosition(const sf::Vector2f& pos)
{
	idle_sprite.setPosition(pos);
	clicked_sprite.setPosition(pos);
	hover_sprite.setPosition(pos);

	UpdateTriggerRect();
}

void ButtonElement::SetTexture(const std::string& id)
{
	idle_sprite.setTexture(*program_info->texture_manager->GetTexture(id + "_button"));
	idle_sprite.setOrigin(idle_sprite.getTextureRect().width / 2.f, idle_sprite.getTextureRect().height / 2.f);

	clicked_sprite.setTexture(*program_info->texture_manager->GetTexture(id + "_button_clicked"));
	clicked_sprite.setOrigin(clicked_sprite.getTextureRect().width / 2.f, clicked_sprite.getTextureRect().height / 2.f);

	hover_sprite.setTexture(*program_info->texture_manager->GetTexture(id + "_button_hover"));
	hover_sprite.setOrigin(hover_sprite.getTextureRect().width / 2.f, hover_sprite.getTextureRect().height / 2.f);

	UpdateTriggerRect();
}

void ButtonElement::SetScale(const Scale& scale)
{
	idle_sprite.setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());
	clicked_sprite.setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());
	hover_sprite.setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());

	UpdateTriggerRect();
}


const sf::Sprite& ButtonElement::GetSprite() const
{
	if (is_down)
		return clicked_sprite;
	else if (is_hovering)
		return hover_sprite;
	else
		return idle_sprite;
}

void ButtonElement::SetTrigger(const lio::Rect<float>& rect)
{
	trigger_rect = rect;
}

const lio::Rect<float>& ButtonElement::GetTrigger() const
{
	return trigger_rect;
}

void ButtonElement::On(const lev::Event& event)
{
	if (event.Is<UIRescaleEvent>())
	{
		const auto& rescale_event = static_cast<const UIRescaleEvent&>(event);
		auto factor = rescale_event.scale / (lio::stolvec<float>(idle_sprite.getScale()) / xscale.Get());
		auto center = lio::stolvec<float>(rescale_event.view.getCenter());

		SetScale(rescale_event.scale);
		SetPosition(lio::ltosvec<float>(center + (lio::stolvec<float>(idle_sprite.getPosition()) - center) * factor));
	}
}
