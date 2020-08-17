#pragma once

#include <SFML/Graphics.hpp>

#include "Element.hpp"

class CursorElement : public Element
{
private:

	sf::Sprite cursor_color;
	sf::Sprite cursor_outline;

public:

	CursorElement& SetPosition(const sf::Vector2f& pos);
	CursorElement& SetTextures(const std::string& color_id, const std::string& outline_id);
	CursorElement& SetColor(const sf::Color& color);
	CursorElement& SetScale(const Scale& scale);

	const sf::Sprite& GetColorSprite() const;
	const sf::Sprite& GetOutlineSprite() const;
};