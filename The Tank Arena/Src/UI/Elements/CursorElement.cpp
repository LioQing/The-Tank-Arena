#include "CursorElement.hpp"

#include "../Events.hpp"
#include "../../Events.hpp"

CursorElement::CursorElement()
{
	Listen<InGameCursorEvent>();
	Listen<UIRescaleEvent>();
}
void CursorElement::SetPosition(const sf::Vector2f& pos)
{
	cursor_color.setPosition(pos);
	cursor_outline.setPosition(pos);
}

void CursorElement::SetTextures(const std::string& color_id, const std::string& outline_id)
{
	cursor_color.setTexture(*program_info->texture_manager->GetTexture(color_id));
	cursor_outline.setTexture(*program_info->texture_manager->GetTexture(outline_id));

	cursor_color.setOrigin(cursor_color.getTextureRect().width / 2.f, cursor_color.getTextureRect().height / 2.f);
	cursor_outline.setOrigin(cursor_outline.getTextureRect().width / 2.f, cursor_outline.getTextureRect().height / 2.f);
}

void CursorElement::SetColor(const sf::Color& color)
{
	cursor_color.setColor(color);
}

void CursorElement::SetScale(const Scale& scale)
{
	cursor_color.setScale(scale.sfVec2f());
	cursor_outline.setScale(scale.sfVec2f());
}

const sf::Sprite& CursorElement::GetColorSprite() const
{
	return cursor_color;
}

const sf::Sprite& CursorElement::GetOutlineSprite() const
{
	return cursor_outline;
}

void CursorElement::On(const lev::Event& event)
{
	if (event.Is<InGameCursorEvent>())
	{
		const auto& pos = static_cast<const InGameCursorEvent&>(event).pos;
		SetPosition(pos);
	}
	else if (event.Is<UIRescaleEvent>())
	{
		const auto& scale = static_cast<const UIRescaleEvent&>(event).scale;
		SetScale(scale);
	}
}
