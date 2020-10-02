#pragma once

#include <lev.hpp>
#include <LioGraphics.hpp>
#include <SFML/Graphics.hpp>

#include "../../Managers/InputManager.hpp"
#include "../Element.hpp"

class ButtonElement : public Element, public lev::Listener
{
protected:

	friend class InputManager;

	lio::Rect<float> trigger_rect;

public:

	virtual ~ButtonElement() = default;

	virtual void OnClick() {}
	virtual void OnRelease() {}
	virtual void OnPress() {}
	virtual void OnHover() {}

	void SetTrigger(const lio::Rect<float>& rect);
	const lio::Rect<float>& GetTrigger() const;
};