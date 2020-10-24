#include "TextElement.hpp"

#include "../../Events.hpp"

sf::Text TextElement::GetText() const
{
	return text;
}

void TextElement::SetText(const std::string& text)
{
	this->text.setString(text);
}

void TextElement::SetSize(int size)
{
	text.setCharacterSize(size);
}

void TextElement::SetColor(const sf::Color& col)
{
	text.setFillColor(col);
}

void TextElement::SetFont(const sf::Font& font)
{
	text.setFont(font);
}

void TextElement::SetPosition(const sf::Vector2f& pos)
{
	text.setPosition(pos);
}