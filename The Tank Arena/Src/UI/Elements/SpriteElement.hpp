#pragma once

#include <lev.hpp>
#include <SFML/Graphics.hpp>

#include "Element.hpp"

class SpriteElement : public Element, lev::Listener
{
private:

	sf::Sprite sprite;
	const Scale xscale;

public:

	SpriteElement(const Scale& xscale);

	SpriteElement& SetPosition(const sf::Vector2f& pos);
	SpriteElement& SetTexture(const std::string& id);
	SpriteElement& SetScale(const Scale& scale);

	const sf::Sprite& GetSprite() const;
	const Scale& GetExScale() const;

	void On(const lev::Event& event) override;
};