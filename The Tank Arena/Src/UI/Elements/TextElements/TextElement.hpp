#pragma once

#include <lev.hpp>
#include <SFML/Graphics.hpp>

#include "../Element.hpp"

class TextElement : public Element
{
protected:

	sf::Text text;

public:

	virtual ~TextElement() = default;

	sf::Text GetText() const;
	void SetText(const std::string& text);

	void SetSize(int size);
	void SetColor(const sf::Color& col);
	void SetFont(const sf::Font& font);
	void SetPosition(const sf::Vector2f& pos);
};