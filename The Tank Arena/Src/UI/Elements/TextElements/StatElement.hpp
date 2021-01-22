#pragma once

#include <lev.hpp>

#include "TextElement.hpp"

class StatElement : public TextElement, public lev::Listener
{
public:

	enum Type : uint8_t
	{
		TANK_DESTROYED,
		BULLET_SHOT
	};

private:

	const Type type;

public:

	StatElement(Type type);

	void On(const lev::Event& event) override;
};