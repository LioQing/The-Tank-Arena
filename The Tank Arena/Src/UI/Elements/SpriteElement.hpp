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

	void SetPosition(const sf::Vector2f& pos);
	void SetTexture(const std::string& id);
	void SetScale(const Scale& scale);

	const sf::Sprite& GetSprite() const;
	const Scale& GetExScale() const;

	void On(const lev::Event& event) override;
};