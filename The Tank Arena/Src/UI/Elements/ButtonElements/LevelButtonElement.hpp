#pragma once

#include "ButtonElement.hpp"

class LevelButtonElement : public ButtonElement
{
private:

	uint8_t number = 0;

	sf::Sprite number_idle_sprite[2];
	sf::Sprite number_clicked_sprite[2];
	sf::Sprite number_hover_sprite[2];

	void UpdateOrigin();

public:

	LevelButtonElement(const Scale& xscale, uint32_t active_state);

	void OnRelease() override;

	void SetNumber(uint8_t n);

	void SetPosition(const sf::Vector2f& pos) override;
	void SetTexture(const std::string& id = "numbers") override;
	void SetScale(const Scale& scale) override;

	const sf::Sprite& GetButtonSprite() const;
	const sf::Sprite& GetNumberSprite(uint8_t digit) const;
};