#pragma once

#include <lev.hpp>

#include "TextElement.hpp"

class TimerElement : public TextElement, public lev::Listener
{
private:

	uint32_t min = 0;
	float sec = 0.f;

public:

	TimerElement();

	void On(const lev::Event& event) override;
};