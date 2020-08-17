#include "CursorElement.hpp"

CursorElement& CursorElement::SetPosition(const sf::Vector2f& pos)
{
	cursor_color.setPosition(pos);
	cursor_outline.setPosition(pos);

	return *this;
}

CursorElement& CursorElement::SetTextures(const std::string& color_id, const std::string& outline_id)
{
	cursor_color.setTexture(*program_info->texture_manager->GetTexture(color_id));
	cursor_outline.setTexture(*program_info->texture_manager->GetTexture(outline_id));

	cursor_color.setOrigin(cursor_color.getTextureRect().width / 2.f, cursor_color.getTextureRect().height / 2.f);
	cursor_outline.setOrigin(cursor_outline.getTextureRect().width / 2.f, cursor_outline.getTextureRect().height / 2.f);

	return *this;
}

CursorElement& CursorElement::SetColor(const sf::Color& color)
{
	cursor_color.setColor(color);

	return *this;
}

CursorElement& CursorElement::SetScale(const Scale& scale)
{
	cursor_color.setScale(scale.sfVec2f());
	cursor_outline.setScale(scale.sfVec2f());

	return *this;
}

const sf::Sprite& CursorElement::GetColorSprite() const
{
	return cursor_color;
}

const sf::Sprite& CursorElement::GetOutlineSprite() const
{
	return cursor_outline;
}
