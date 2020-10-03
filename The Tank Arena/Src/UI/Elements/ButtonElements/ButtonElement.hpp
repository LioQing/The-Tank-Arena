#pragma once

#include <LioGraphics.hpp>
#include <SFML/Graphics.hpp>

#include "../../Managers/InputManager.hpp"
#include "../Element.hpp"

class ButtonElement : public Element
{
private:

	friend class InputManager;

protected:

	lio::Rect<float> trigger_rect;
	bool is_down = false;
	bool is_hovering = false;

public:

	virtual ~ButtonElement() = default;

	virtual void OnClick() {}
	virtual void OnRelease() {}
	virtual void OnHover() {}

	void SetTrigger(const lio::Rect<float>& rect);
	const lio::Rect<float>& GetTrigger() const;
};