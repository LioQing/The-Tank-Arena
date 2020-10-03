#pragma once

#include <lev.hpp>
#include <LioGraphics.hpp>
#include <SFML/Graphics.hpp>

#include "../../Managers/InputManager.hpp"
#include "../Element.hpp"

class ButtonElement : public Element, public lev::Listener
{
private:

	friend class InputManager;

protected:

	lio::Rect<float> trigger_rect;
	bool is_down = false;
	bool is_hovering = false;

	sf::Sprite idle_sprite;
	sf::Sprite clicked_sprite;
	sf::Sprite hover_sprite;

	Scale xscale = 1.f;

	void UpdateTriggerRect();

public:
	
	ButtonElement() = default;
	ButtonElement(const Scale& xscale);

	virtual ~ButtonElement() = default;

	virtual void OnClick() {}
	virtual void OnRelease() {}
	virtual void OnHover() {}

	void SetPosition(const sf::Vector2f& pos);
	void SetTexture(const std::string& id);
	void SetScale(const Scale& scale);

	const sf::Sprite& GetSprite() const;

	void SetTrigger(const lio::Rect<float>& rect);
	const lio::Rect<float>& GetTrigger() const;

	void On(const lev::Event& event) override;
};