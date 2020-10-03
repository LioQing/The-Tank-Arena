#pragma once

#include <lev.hpp>
#include <SFML/Graphics.hpp>

#include "ButtonElement.hpp"

class PlayButtonElement : public ButtonElement, public lev::Listener
{
private:

	sf::Sprite idle_sprite;
	sf::Sprite clicked_sprite;

	Scale xscale;

	uint32_t* program_state = nullptr;

	void UpdateTriggerRect();

public:

	PlayButtonElement(uint32_t* program_state, const Scale& xscale);

	void SetPosition(const sf::Vector2f& pos);
	void SetTexture(const std::string& id);
	void SetScale(const Scale& scale);

	const sf::Sprite& GetSprite() const;

	void OnClick() override;
	void OnRelease() override;

	void On(const lev::Event& event) override;
};