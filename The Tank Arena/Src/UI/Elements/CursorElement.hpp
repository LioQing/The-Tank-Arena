#pragma once

#include <lev.hpp>
#include <SFML/Graphics.hpp>

#include "Element.hpp"

class CursorElement : public Element, public lev::Listener
{
private:

	sf::Sprite cursor_color;
	sf::Sprite cursor_outline;

public:

	CursorElement();

	void SetPosition(const sf::Vector2f& pos);
	void SetTextures(const std::string& color_id, const std::string& outline_id);
	void SetColor(const sf::Color& color);
	void SetScale(const Scale& scale);

	const sf::Sprite& GetColorSprite() const;
	const sf::Sprite& GetOutlineSprite() const;

	void On(const lev::Event& event) override;
};