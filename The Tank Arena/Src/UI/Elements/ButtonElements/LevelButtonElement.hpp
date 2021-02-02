#pragma once

#include "ButtonElement.hpp"

class LevelButtonElement : public ButtonElement
{
private:

	uint8_t number;

	sf::Sprite idle_sprite[2];
	sf::Sprite clicked_sprite[2];
	sf::Sprite hover_sprite[2];
	sf::Sprite button_sprite;
	sf::Sprite button_clicked_sprite;

	void UpdateOrigin();
	void UpdateTriggerRect() override;

public:

	LevelButtonElement(const Scale& xscale, uint32_t active_state);

	void OnRelease() override;

	void SetNumber(uint8_t n);

	void SetPosition(const sf::Vector2f& pos) override;
	void SetTexture(const std::string& id = "numbers") override;
	void SetScale(const Scale& scale) override;
};