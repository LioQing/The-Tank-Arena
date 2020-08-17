#pragma once

#include <SFML/Graphics.hpp>

#include "../../ProgramUtils.hpp"

class Element
{
private:

	friend class ElementManager;

protected:

	ProgramInfo* program_info;

public:

	virtual ~Element() = default;
};